#!/bin/bash
# run_c_benchmarks.sh — Compile and benchmark generated C code for all options
# Runs each option's generated C code standalone (no MATLAB) with timing
#
# Usage: bash benchmark/run_c_benchmarks.sh
#
# Requires: gcc (Apple Clang or GCC), libomp (brew install libomp)

set -e
PROJ_DIR="$(cd "$(dirname "$0")/.." && pwd)"
OMP_FLAGS="-I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -Xpreprocessor -fopenmp -lomp"
CFLAGS="-O3 -w $OMP_FLAGS"
NRUNS=7
NINFER=100

echo "============================================================="
echo " ShuffleNet V2 — Standalone C Code Benchmark"
echo " Compiler: $(gcc --version | head -1)"
echo " Runs: ${NRUNS} x ${NINFER} inferences per option"
echo "============================================================="
echo ""

# ─── Helper: create a benchmark main.c wrapper ───
create_benchmark_main() {
    local func_name=$1
    local input_size=$2
    local output_size=$3
    local outfile=$4

    cat > "$outfile" << 'MAINEOF'
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
MAINEOF

    echo "#include \"${func_name}.h\"" >> "$outfile"
    echo "#include \"${func_name}_initialize.h\"" >> "$outfile"
    echo "#include \"${func_name}_terminate.h\"" >> "$outfile"

    cat >> "$outfile" << MAINEOF2

int main(int argc, char **argv) {
    int nruns = ${NRUNS}, ninfer = ${NINFER};
    static float input[${input_size}];
    float output[${output_size}];

    // Fill input with deterministic pseudo-random data
    for (int i = 0; i < ${input_size}; i++)
        input[i] = (float)(i % 1000) / 1000.0f - 0.5f;

    ${func_name}_initialize();

    // Warmup
    ${func_name}(input, output);

    printf("Option benchmark: %d runs x %d inferences\\n", nruns, ninfer);
    double times[${NRUNS}];
    double total = 0.0;

    for (int r = 0; r < nruns; r++) {
        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        for (int i = 0; i < ninfer; i++) {
            ${func_name}(input, output);
        }
        clock_gettime(CLOCK_MONOTONIC, &t1);
        double elapsed = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
        times[r] = elapsed / ninfer * 1000.0;  // ms per inference
        total += times[r];
        printf("  Run %d: %.3f ms/inference\\n", r+1, times[r]);
    }

    double mean = total / nruns;
    double var = 0.0;
    for (int r = 0; r < nruns; r++) var += (times[r] - mean) * (times[r] - mean);
    double std = (nruns > 1) ? sqrt(var / (nruns - 1)) : 0.0;

    printf("  Mean: %.3f ms  Std: %.3f ms\\n", mean, std);

    // Print top-5
    int top5[5] = {0,1,2,3,4};
    for (int i = 0; i < ${output_size}; i++) {
        for (int j = 0; j < 5; j++) {
            if (output[i] > output[top5[j]]) {
                for (int k = 4; k > j; k--) top5[k] = top5[k-1];
                top5[j] = i;
                break;
            }
        }
    }
    printf("  Top-5: ");
    for (int j = 0; j < 5; j++) printf("%d(%.4f) ", top5[j], output[top5[j]]);
    printf("\\n");

    ${func_name}_terminate();
    return 0;
}
MAINEOF2
}

# ─── Option 1: Hand-crafted C ───
echo "━━━ Option 1: Hand-Crafted C ━━━"
cd "$PROJ_DIR/option1_handcrafted_c"
if [ -f shufflenet_v2.c ]; then
    # Create a host-compatible benchmark wrapper (main.c uses ARM DWT cycle counter)
    cat > bench_main_opt1.c << 'OPT1EOF'
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "shufflenet_v2.h"

int main() {
    int nruns = 7, ninfer = 100;
    static float input[3*224*224];
    static float output[1000];

    for (int i = 0; i < 3*224*224; i++)
        input[i] = (float)(i % 1000) / 1000.0f - 0.5f;

    // Warmup
    shufflenet_forward(input, output);

    printf("Option 1 benchmark: %d runs x %d inferences\n", nruns, ninfer);
    double times[7];
    double total = 0.0;

    for (int r = 0; r < nruns; r++) {
        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        for (int i = 0; i < ninfer; i++)
            shufflenet_forward(input, output);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        double elapsed = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
        times[r] = elapsed / ninfer * 1000.0;
        total += times[r];
        printf("  Run %d: %.3f ms/inference\n", r+1, times[r]);
    }

    double mean = total / nruns;
    double var = 0.0;
    for (int r = 0; r < nruns; r++) var += (times[r] - mean) * (times[r] - mean);
    double std = (nruns > 1) ? sqrt(var / (nruns - 1)) : 0.0;
    printf("  Mean: %.3f ms  Std: %.3f ms\n", mean, std);
    return 0;
}
OPT1EOF
    gcc $CFLAGS -o bench_opt1 shufflenet_v2.c bench_main_opt1.c -lm 2>&1 || echo "  Compile failed"
    if [ -f bench_opt1 ]; then
        ./bench_opt1 2>&1
        rm -f bench_opt1 bench_main_opt1.c
    fi
else
    echo "  SKIP: shufflenet_v2.c not found"
fi
echo ""

# ─── Option 2: PyTorch Coder ───
echo "━━━ Option 2: PyTorch Coder (with OpenMP + NEON config) ━━━"
cd "$PROJ_DIR/option2_pytorch_coder"
EDIR="embeddedOutputDir"
if [ -f "$EDIR/mInvoke_shufflenet.c" ]; then
    create_benchmark_main "mInvoke_shufflenet" 150528 1000 "$EDIR/bench_main.c"

    # Compile all C files
    SRC_FILES=$(find "$EDIR" -maxdepth 1 -name "*.c" ! -name "bench_main.c" | tr '\n' ' ')
    gcc $CFLAGS -I"$EDIR" -I"$EDIR/interface" -I"$EDIR/examples" \
        $SRC_FILES "$EDIR/bench_main.c" \
        -o "$EDIR/bench_opt2" -lm 2>&1 || echo "  Compile failed"

    if [ -f "$EDIR/bench_opt2" ]; then
        cd "$PROJ_DIR/option2_pytorch_coder"
        "$EDIR/bench_opt2" 2>&1
        rm -f "$EDIR/bench_opt2" "$EDIR/bench_main.c"
    fi
else
    echo "  SKIP: mInvoke_shufflenet.c not found"
fi
echo ""

# ─── Option 4: ONNX Import ───
echo "━━━ Option 4: ONNX Import (with OpenMP + NEON config) ━━━"
cd "$PROJ_DIR/option4_onnx_import"
EDIR="embeddedDir"
if [ -f "$EDIR/callPredict.c" ]; then
    create_benchmark_main "predict_shufflenet_onnx" 150528 1000 "$EDIR/bench_main.c"

    SRC_FILES=$(find "$EDIR" -maxdepth 1 -name "*.c" ! -name "bench_main.c" | tr '\n' ' ')
    gcc $CFLAGS -I"$EDIR" -I"$EDIR/interface" -I"$EDIR/examples" \
        $SRC_FILES "$EDIR/bench_main.c" \
        -o "$EDIR/bench_opt4" -lm 2>&1 || echo "  Compile failed"

    if [ -f "$EDIR/bench_opt4" ]; then
        cd "$PROJ_DIR/option4_onnx_import"
        "$EDIR/bench_opt4" 2>&1
        rm -f "$EDIR/bench_opt4" "$EDIR/bench_main.c"
    fi
else
    echo "  SKIP: callPredict.c not found"
fi
echo ""

# ─── Option 5: Rebuilt dlnetwork ───
echo "━━━ Option 5: Rebuilt dlnetwork (with OpenMP + NEON config) ━━━"
cd "$PROJ_DIR/option5_rebuilt_network"
EDIR="embeddedDir"
if [ -f "$EDIR/predict_shufflenet_v5.c" ] || [ -f "$EDIR/callPredict.c" ]; then
    # Determine entry point name
    if [ -f "$EDIR/predict_shufflenet_v5.c" ]; then
        ENTRY="predict_shufflenet_v5"
    else
        ENTRY="callPredict"
    fi

    create_benchmark_main "$ENTRY" 150528 1000 "$EDIR/bench_main.c"

    SRC_FILES=$(find "$EDIR" -maxdepth 1 -name "*.c" ! -name "bench_main.c" | tr '\n' ' ')
    gcc $CFLAGS -I"$EDIR" -I"$EDIR/interface" -I"$EDIR/examples" \
        $SRC_FILES "$EDIR/bench_main.c" \
        -o "$EDIR/bench_opt5" -lm 2>&1 || echo "  Compile failed"

    if [ -f "$EDIR/bench_opt5" ]; then
        cd "$PROJ_DIR/option5_rebuilt_network"
        "$EDIR/bench_opt5" 2>&1
        rm -f "$EDIR/bench_opt5" "$EDIR/bench_main.c"
    fi
else
    echo "  SKIP: No generated C code found yet"
fi
echo ""

echo "============================================================="
echo " Benchmark complete"
echo "============================================================="
