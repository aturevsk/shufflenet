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
