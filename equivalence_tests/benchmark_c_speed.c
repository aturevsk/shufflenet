/*
 * benchmark_c_speed.c — Rigorous C code inference speed benchmark
 *
 * Protocol: 7 independent trials, 1000 iterations each, 50 warmup.
 * Reports mean, std, min, max per trial plus overall statistics.
 *
 * This benchmarks the ACTUAL GENERATED C code (compiled natively),
 * which is what would run on the embedded target.
 *
 * Build & run for each option:
 *
 *   Option 1 (hand-crafted):
 *     gcc -O3 -std=c99 -ffast-math -o bench1 benchmark_c_speed.c \
 *         ../option1_handcrafted_c/shufflenet_v2.c -lm \
 *         -I../option1_handcrafted_c -DOPTION=1
 *     ./bench1
 *
 *   Option 2 (PyTorch Coder):
 *     gcc -O3 -std=c99 -ffast-math -o bench2 benchmark_c_speed.c \
 *         ../option2_pytorch_coder/embeddedOutputDir/mInvoke_shufflenet.c \
 *         ../option2_pytorch_coder/embeddedOutputDir/mInvoke_shufflenet_initialize.c \
 *         ../option2_pytorch_coder/embeddedOutputDir/mInvoke_shufflenet_terminate.c \
 *         ../option2_pytorch_coder/embeddedOutputDir/mInvoke_shufflenet_data.c \
 *         -lm -I../option2_pytorch_coder/embeddedOutputDir -DOPTION=2
 *     ./bench2
 *
 *   Option 4 (ONNX import):
 *     gcc -O3 -std=c99 -ffast-math -o bench4 benchmark_c_speed.c \
 *         ../option4_onnx_import/embeddedDir/predict_shufflenet_onnx.c \
 *         ../option4_onnx_import/embeddedDir/callPredict.c \
 *         ../option4_onnx_import/embeddedDir/conv2dDirectOptimizedColMajor.c \
 *         ../option4_onnx_import/embeddedDir/mean.c \
 *         ../option4_onnx_import/embeddedDir/permute.c \
 *         ../option4_onnx_import/embeddedDir/predict_shufflenet_onnx_initialize.c \
 *         ../option4_onnx_import/embeddedDir/predict_shufflenet_onnx_terminate.c \
 *         ../option4_onnx_import/embeddedDir/predict_shufflenet_onnx_rtwutil.c \
 *         ../option4_onnx_import/embeddedDir/Shape_To_SliceLayer1000.c \
 *         ../option4_onnx_import/embeddedDir/Shape_To_SliceLayer1004.c \
 *         ../option4_onnx_import/embeddedDir/Shape_To_SliceLayer1012.c \
 *         -lm -I../option4_onnx_import/embeddedDir -DOPTION=4
 *     ./bench4
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/* ── Configuration ─────────────────────────────────────────────────── */
#define NUM_TRIALS   7
#define NUM_ITERS    1000
#define NUM_WARMUP   50
#define INPUT_SIZE   (1 * 3 * 224 * 224)
#define OUTPUT_SIZE  1000

/* ── Platform-specific high-res timer ──────────────────────────────── */
#ifdef __APPLE__
#include <mach/mach_time.h>
static double timer_scale = 0;
static inline double get_time_ms(void) {
    if (timer_scale == 0) {
        mach_timebase_info_data_t info;
        mach_timebase_info(&info);
        timer_scale = (double)info.numer / info.denom / 1e6;
    }
    return mach_absolute_time() * timer_scale;
}
#else
static inline double get_time_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}
#endif

/* ── Include the appropriate header ────────────────────────────────── */
#if OPTION == 1
#include "shufflenet_v2.h"
#elif OPTION == 2
#include "mInvoke_shufflenet.h"
#include "mInvoke_shufflenet_initialize.h"
#include "mInvoke_shufflenet_terminate.h"
#elif OPTION == 4
#include "predict_shufflenet_onnx.h"
#include "predict_shufflenet_onnx_initialize.h"
#include "predict_shufflenet_onnx_terminate.h"
#endif

/* Forward declarations for Option 1 API (uses sn2_ prefix) */
#if OPTION == 1
/* Wrapper macros to match generic benchmark interface */
static ShuffleNetV2 *g_model = NULL;
static SN2Workspace g_ws;
#define INIT_MODEL() do { \
    g_model = sn2_create_model(); \
    static float ext_mem[16*1024*1024]; \
    sn2_workspace_init(&g_ws, ext_mem, sizeof(ext_mem)); \
} while(0)
#define RUN_FORWARD(in, out) sn2_forward(g_model, &g_ws, in, out)
#define CLEANUP() do { sn2_workspace_free(&g_ws); sn2_destroy_model(g_model); } while(0)
#elif OPTION == 2
#define INIT_MODEL() mInvoke_shufflenet_initialize()
#define RUN_FORWARD(in, out) mInvoke_shufflenet(in, out)
#define CLEANUP() mInvoke_shufflenet_terminate()
#elif OPTION == 4
#define INIT_MODEL() predict_shufflenet_onnx_initialize()
#define RUN_FORWARD(in, out) predict_shufflenet_onnx(in, out)
#define CLEANUP() predict_shufflenet_onnx_terminate()
#endif

/* ── Statistics ────────────────────────────────────────────────────── */
typedef struct {
    double mean, std, min, max, median;
} Stats;

static int compare_doubles(const void *a, const void *b) {
    double da = *(const double*)a, db = *(const double*)b;
    return (da > db) - (da < db);
}

static Stats compute_stats(double *data, int n) {
    Stats s;
    qsort(data, n, sizeof(double), compare_doubles);
    s.min = data[0];
    s.max = data[n-1];
    s.median = (n % 2) ? data[n/2] : (data[n/2-1] + data[n/2]) / 2.0;

    double sum = 0;
    for (int i = 0; i < n; i++) sum += data[i];
    s.mean = sum / n;

    double sum_sq = 0;
    for (int i = 0; i < n; i++) sum_sq += (data[i] - s.mean) * (data[i] - s.mean);
    s.std = sqrt(sum_sq / n);
    return s;
}

/* ── Main ──────────────────────────────────────────────────────────── */
int main(void) {
    printf("\n====================================================\n");
#if OPTION == 1
    printf(" Option 1: Hand-Crafted C — Speed Benchmark\n");
#elif OPTION == 2
    printf(" Option 2: PyTorch Coder — Speed Benchmark\n");
#elif OPTION == 4
    printf(" Option 4: ONNX Import — Speed Benchmark\n");
#else
    printf(" Unknown option — Speed Benchmark\n");
#endif
    printf(" %d trials x %d iters (+ %d warmup)\n", NUM_TRIALS, NUM_ITERS, NUM_WARMUP);
    printf(" Compiled with: -O3 -ffast-math\n");
    printf("====================================================\n\n");

    /* Allocate buffers */
    float *input  = (float*)calloc(INPUT_SIZE, sizeof(float));
    float *output = (float*)malloc(OUTPUT_SIZE * sizeof(float));
    if (!input || !output) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    /* Fill with random-ish data */
    srand(42);
    for (int i = 0; i < INPUT_SIZE; i++)
        input[i] = ((float)rand() / RAND_MAX - 0.5f) * 2.0f;

    /* Initialize model */
    INIT_MODEL();

    /* Warmup */
    printf("Warming up (%d iterations)...\n", NUM_WARMUP);
    for (int w = 0; w < NUM_WARMUP; w++) {
        RUN_FORWARD(input, output);
    }

    /* Timed trials */
    double trial_means[NUM_TRIALS];
    double all_times[NUM_TRIALS * NUM_ITERS];
    int total_idx = 0;

    for (int t = 0; t < NUM_TRIALS; t++) {
        double times[NUM_ITERS];
        for (int i = 0; i < NUM_ITERS; i++) {
            double t0 = get_time_ms();
            RUN_FORWARD(input, output);
            times[i] = get_time_ms() - t0;
            all_times[total_idx++] = times[i];
        }

        Stats ts = compute_stats(times, NUM_ITERS);
        trial_means[t] = ts.mean;
        printf("  Trial %d/%d: mean=%.3f ms, std=%.3f ms, min=%.3f ms, max=%.3f ms\n",
               t+1, NUM_TRIALS, ts.mean, ts.std, ts.min, ts.max);
    }

    /* Overall statistics */
    Stats overall = compute_stats(all_times, NUM_TRIALS * NUM_ITERS);
    Stats trial_s = compute_stats(trial_means, NUM_TRIALS);

    printf("\n====================================================\n");
    printf(" RESULTS (%d total measurements)\n", NUM_TRIALS * NUM_ITERS);
    printf("====================================================\n");
    printf("  Mean:    %.3f ms\n", overall.mean);
    printf("  Std:     %.3f ms\n", overall.std);
    printf("  Median:  %.3f ms\n", overall.median);
    printf("  Min:     %.3f ms\n", overall.min);
    printf("  Max:     %.3f ms\n", overall.max);
    printf("  Trial-level mean: %.3f +/- %.3f ms\n", trial_s.mean, trial_s.std);
    printf("  Throughput: %.1f inferences/sec\n", 1000.0 / overall.mean);
    printf("====================================================\n");

    /* Verify output is reasonable */
    int top1 = 0;
    for (int i = 1; i < OUTPUT_SIZE; i++)
        if (output[i] > output[top1]) top1 = i;
    printf("  Sanity check — top-1 class: %d (logit=%.3f)\n", top1, output[top1]);

    /* Cleanup */
    CLEANUP();
    free(input);
    free(output);

    return 0;
}
