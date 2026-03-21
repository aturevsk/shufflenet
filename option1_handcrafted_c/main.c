/**
 * @file main.c
 * @brief ShuffleNet V2 1.0x — Test harness
 *
 * This file provides:
 *   1. Dummy input generation (gradient pattern for visual debugging)
 *   2. Inference timing via ARM DWT cycle counter (or clock() on host)
 *   3. Memory usage reporting
 *   4. Top-5 prediction output
 *
 * It compiles on both the target (arm-none-eabi-gcc) and a host (gcc/clang)
 * for development and testing.  ARM-specific features are guarded behind
 * #ifdef __ARM_ARCH.
 *
 * Usage:
 *   Host:    ./shufflenet_v2_host [weights.bin]
 *   Target:  loaded via debugger / flash
 *
 * Copyright (c) 2026 — MIT License
 */

#include "shufflenet_v2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* ================================================================== */
/*  Platform abstraction                                              */
/* ================================================================== */

#if defined(STM32F746xx)
  /* ---- ARM Cortex-M target ---- */
  #include "stm32f7xx.h"    /* CMSIS device header */

  #define SN2_TARGET_ARM     1

  /*
   * Data Watch and Trace (DWT) cycle counter for precise timing.
   * Available on Cortex-M3/M4/M7.
   */
  static inline void dwt_init(void)
  {
      CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
      DWT->CYCCNT = 0;
      DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  }

  static inline uint32_t dwt_get_cycles(void)
  {
      return DWT->CYCCNT;
  }

  /** SDRAM base address on STM32F746G-Discovery (FMC Bank 1, SDRAM Bank 2) */
  #define SDRAM_BASE   0xC0000000U
  #define SDRAM_SIZE   (8 * 1024 * 1024)  /* 8 MB */

  /** Place large buffers in SDRAM via linker section attribute */
  #define SN2_SDRAM    __attribute__((section(".sdram")))

#else
  /* ---- Host (x86/x64/Apple Silicon) ---- */
  #include <time.h>

  #define SN2_TARGET_ARM     0

  static inline void dwt_init(void) { /* no-op */ }

  static inline uint32_t dwt_get_cycles(void)
  {
      struct timespec ts;
      clock_gettime(CLOCK_MONOTONIC, &ts);
      return (uint32_t)(ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
  }

  #define SN2_SDRAM   /* nothing */

#endif

/* ================================================================== */
/*  Dummy input generation                                            */
/* ================================================================== */

/**
 * Generate a synthetic test image: a diagonal gradient pattern in each
 * channel, normalised to ImageNet range [-2.1, 2.6] approximately.
 *
 * This is useful for smoke-testing the forward pass without loading
 * a real image.  Consistent across runs for reproducibility.
 */
static void generate_dummy_input(float *input)
{
    const int C = SN2_INPUT_C;
    const int H = SN2_INPUT_H;
    const int W = SN2_INPUT_W;

    /* ImageNet normalisation constants (mean / std per channel) */
    const float mean[3] = { 0.485f, 0.456f, 0.406f };
    const float std[3]  = { 0.229f, 0.224f, 0.225f };

    int c, h, w;
    for (c = 0; c < C; c++) {
        for (h = 0; h < H; h++) {
            for (w = 0; w < W; w++) {
                /* Raw pixel in [0, 1] with a gentle gradient */
                float raw = (float)(h + w + c * 50) / (float)(H + W + C * 50);
                /* Apply ImageNet normalisation */
                float normalised = (raw - mean[c]) / std[c];
                input[c * H * W + h * W + w] = normalised;
            }
        }
    }
}

/* ================================================================== */
/*  Top-K extraction                                                  */
/* ================================================================== */

/**
 * Find the top-K class indices and their logit values.
 *
 * @param logits  Array of SN2_NUM_CLASSES floats.
 * @param k       Number of top predictions to return.
 * @param indices Output: top-K class indices (descending by score).
 * @param scores  Output: corresponding logit values.
 */
static void top_k(const float *logits, int k, int *indices, float *scores)
{
    int i, j;

    /* Initialise with -inf */
    for (i = 0; i < k; i++) {
        indices[i] = -1;
        scores[i]  = -1e30f;
    }

    for (i = 0; i < SN2_NUM_CLASSES; i++) {
        float val = logits[i];

        /* Check if this value belongs in the top-K */
        if (val > scores[k - 1]) {
            /* Insert in sorted position */
            scores[k - 1]  = val;
            indices[k - 1] = i;

            /* Bubble up */
            for (j = k - 2; j >= 0; j--) {
                if (scores[j + 1] > scores[j]) {
                    float  ts = scores[j];
                    int    ti = indices[j];
                    scores[j]     = scores[j + 1];
                    indices[j]    = indices[j + 1];
                    scores[j + 1] = ts;
                    indices[j + 1] = ti;
                } else {
                    break;
                }
            }
        }
    }
}

/* ================================================================== */
/*  Softmax (for display only)                                        */
/* ================================================================== */

static void softmax(const float *input, float *output, int n)
{
    float max_val = input[0];
    int i;
    for (i = 1; i < n; i++)
        if (input[i] > max_val) max_val = input[i];

    float sum = 0.0f;
    for (i = 0; i < n; i++) {
        output[i] = expf(input[i] - max_val);
        sum += output[i];
    }
    float inv_sum = 1.0f / sum;
    for (i = 0; i < n; i++)
        output[i] *= inv_sum;
}

/* ================================================================== */
/*  Memory reporting                                                  */
/* ================================================================== */

static void print_memory_report(const ShuffleNetV2 *model)
{
    size_t param_count = sn2_param_count(model);
    size_t weight_bytes = param_count * sizeof(float);
    size_t workspace_bytes = SN2_BUF_FLOATS * 3 * sizeof(float);

    printf("\n=== Memory Report ===\n");
    printf("Model parameters : %zu (%.2f M)\n",
           param_count, param_count / 1e6f);
    printf("Weight storage   : %.2f MB (float32)\n",
           weight_bytes / (1024.0f * 1024.0f));
    printf("Weight storage   : %.2f MB (int8, quantised)\n",
           param_count / (1024.0f * 1024.0f));
    printf("Workspace buffers: %.2f MB (3 x %d floats)\n",
           workspace_bytes / (1024.0f * 1024.0f), SN2_BUF_FLOATS);
    printf("Input tensor     : %.2f KB\n",
           SN2_INPUT_C * SN2_INPUT_H * SN2_INPUT_W * sizeof(float) / 1024.0f);
    printf("Output tensor    : %.2f KB\n",
           SN2_NUM_CLASSES * sizeof(float) / 1024.0f);
    printf("\n");

#if SN2_TARGET_ARM
    printf("Target memory map:\n");
    printf("  SRAM (340 KB) : Stack, small scratch buffers\n");
    printf("  SDRAM (8 MB)  : Weights (%.2f MB) + Workspace (%.2f MB)\n",
           weight_bytes / (1024.0f * 1024.0f),
           workspace_bytes / (1024.0f * 1024.0f));
    printf("  Flash (1 MB)  : Code + read-only data\n");
    float total_sdram = (weight_bytes + workspace_bytes) / (1024.0f * 1024.0f);
    printf("  SDRAM usage   : %.2f / 8.00 MB (%.1f%%)\n",
           total_sdram, total_sdram / 8.0f * 100.0f);
#endif
    printf("=====================\n\n");
}

/* ================================================================== */
/*  Main entry point                                                  */
/* ================================================================== */

#if SN2_TARGET_ARM
/* On the target, main is called from the startup code (Reset_Handler). */
int main(void)
#else
int main(int argc, char *argv[])
#endif
{
    printf("\n");
    printf("====================================\n");
    printf(" ShuffleNet V2 1.0x — Inference Test\n");
    printf("====================================\n\n");

#if SN2_TARGET_ARM
    printf("Platform: STM32F746G-Discovery (Cortex-M7 @ 216 MHz)\n");
#else
    printf("Platform: Host simulation\n");
#endif

    /* ---- 1. Create model ---- */
    printf("\n[1] Creating model...\n");
    ShuffleNetV2 *model = sn2_create_model();
    if (!model) {
        fprintf(stderr, "ERROR: Failed to create model\n");
        return 1;
    }
    sn2_print_summary(model);

    /* ---- 2. Load weights (optional) ---- */
    int weights_loaded = 0;

#if !SN2_TARGET_ARM
    const char *weight_path = (argc > 1) ? argv[1] : NULL;
    if (weight_path) {
        printf("\n[2] Loading weights from: %s\n", weight_path);
        if (sn2_load_weights(model, weight_path) == 0) {
            weights_loaded = 1;
            printf("    Weights loaded successfully.\n");
        } else {
            printf("    WARNING: Failed to load weights. Using uninitialised.\n");
        }
    } else {
        printf("\n[2] No weight file specified. Running with zero/uninitialised weights.\n");
        printf("    Usage: %s <weights.bin>\n", argv[0]);
    }
#else
    /* On target, weights are expected at a known SDRAM address or
     * loaded via the debugger before starting main(). */
    printf("\n[2] Weights: expecting pre-loaded in SDRAM.\n");
#endif

    if (!weights_loaded) {
        printf("    NOTE: Output will be meaningless without real weights.\n");
    }

    /* ---- 3. Memory report ---- */
    print_memory_report(model);

    /* ---- 4. Allocate workspace ---- */
    printf("[3] Allocating workspace...\n");
    SN2Workspace ws;

#if SN2_TARGET_ARM
    /* Use SDRAM for workspace — place after weights */
    void *sdram_workspace = (void *)(SDRAM_BASE + 6 * 1024 * 1024);
    size_t sdram_avail = 2 * 1024 * 1024;  /* Reserve 2 MB */
    if (sn2_workspace_init(&ws, sdram_workspace, sdram_avail) != 0) {
        fprintf(stderr, "ERROR: Workspace init failed\n");
        return 1;
    }
#else
    if (sn2_workspace_init(&ws, NULL, 0) != 0) {
        fprintf(stderr, "ERROR: Workspace init failed (out of memory?)\n");
        return 1;
    }
#endif
    printf("    Workspace ready. Each buffer: %d floats (%.1f KB)\n",
           SN2_BUF_FLOATS, SN2_BUF_FLOATS * sizeof(float) / 1024.0f);

    /* ---- 5. Generate dummy input ---- */
    printf("\n[4] Generating dummy input (3x224x224, normalised)...\n");
    const int input_size = SN2_INPUT_C * SN2_INPUT_H * SN2_INPUT_W;
    float *input = (float *)malloc(input_size * sizeof(float));
    if (!input) {
        fprintf(stderr, "ERROR: Failed to allocate input buffer\n");
        return 1;
    }
    generate_dummy_input(input);
    printf("    Input range: [%.3f, %.3f] (sample values)\n",
           input[0], input[input_size - 1]);

    /* ---- 6. Run inference with timing ---- */
    float *output = (float *)malloc(SN2_NUM_CLASSES * sizeof(float));
    if (!output) {
        fprintf(stderr, "ERROR: Failed to allocate output buffer\n");
        return 1;
    }

    printf("\n[5] Running forward pass...\n");

    dwt_init();

    /* Warm-up run (important on Cortex-M7 for I-cache / D-cache) */
    sn2_forward(model, input, output, &ws);

    /* Timed run */
    uint32_t t_start = dwt_get_cycles();
    int ret = sn2_forward(model, input, output, &ws);
    uint32_t t_end = dwt_get_cycles();

    if (ret != 0) {
        fprintf(stderr, "ERROR: Forward pass failed with code %d\n", ret);
        return 1;
    }

    uint32_t elapsed = t_end - t_start;

#if SN2_TARGET_ARM
    /* DWT counts CPU cycles; convert to milliseconds at 216 MHz */
    float ms = (float)elapsed / 216000.0f;
    printf("    Inference time: %lu cycles = %.2f ms @ 216 MHz\n",
           (unsigned long)elapsed, ms);
    printf("    Throughput: %.1f FPS\n", 1000.0f / ms);
#else
    /* On host, dwt_get_cycles returns microseconds */
    float ms = (float)elapsed / 1000.0f;
    printf("    Inference time: %.2f ms (host, not representative of target)\n", ms);
#endif

    /* ---- 7. Top-5 predictions ---- */
    printf("\n[6] Top-5 predictions (raw logits and softmax probabilities):\n");

    int top_indices[5];
    float top_scores[5];
    top_k(output, 5, top_indices, top_scores);

    /* Compute softmax for display */
    float *probs = (float *)malloc(SN2_NUM_CLASSES * sizeof(float));
    if (probs) {
        softmax(output, probs, SN2_NUM_CLASSES);

        printf("    %-6s  %-12s  %-12s\n", "Rank", "Logit", "Probability");
        printf("    %-6s  %-12s  %-12s\n", "----", "-----", "-----------");
        int k;
        for (k = 0; k < 5; k++) {
            printf("    #%-5d  class %-5d   logit: %8.4f   prob: %.6f\n",
                   k + 1, top_indices[k], top_scores[k],
                   probs[top_indices[k]]);
        }
        free(probs);
    }

    if (!weights_loaded) {
        printf("\n    NOTE: Predictions are meaningless without real weights.\n");
    }

    /* ---- 8. Validation checks ---- */
    printf("\n[7] Validation:\n");

    /* Check output is finite */
    int nan_count = 0, inf_count = 0;
    int i;
    for (i = 0; i < SN2_NUM_CLASSES; i++) {
        if (isnan(output[i])) nan_count++;
        if (isinf(output[i])) inf_count++;
    }
    printf("    Output NaN count : %d\n", nan_count);
    printf("    Output Inf count : %d\n", inf_count);
    printf("    Status           : %s\n",
           (nan_count == 0 && inf_count == 0) ? "PASS" : "FAIL");

    /* Output statistics */
    float out_min = output[0], out_max = output[0], out_sum = 0.0f;
    for (i = 0; i < SN2_NUM_CLASSES; i++) {
        if (output[i] < out_min) out_min = output[i];
        if (output[i] > out_max) out_max = output[i];
        out_sum += output[i];
    }
    printf("    Output min       : %.6f\n", out_min);
    printf("    Output max       : %.6f\n", out_max);
    printf("    Output mean      : %.6f\n", out_sum / SN2_NUM_CLASSES);

    /* ---- Cleanup ---- */
    printf("\n[8] Cleaning up...\n");
    free(input);
    free(output);
    sn2_workspace_free(&ws);
    sn2_destroy_model(model);
    printf("    Done.\n\n");

    return 0;
}

/* ================================================================== */
/*  ARM target: minimal stubs for newlib / semihosting                */
/* ================================================================== */

#if SN2_TARGET_ARM
/*
 * If not using semihosting or a full C library, you need minimal
 * stubs for _write, _read, _sbrk, etc.  These are typically provided
 * by the BSP or the startup code.  We provide _sbrk here as an
 * example for heap allocation support.
 */

extern unsigned int _end;  /* Defined by linker script */
static unsigned int *heap_ptr = NULL;

void *_sbrk(int incr)
{
    if (heap_ptr == NULL)
        heap_ptr = &_end;

    unsigned int *prev = heap_ptr;
    heap_ptr += incr / sizeof(unsigned int);
    return (void *)prev;
}

#endif /* SN2_TARGET_ARM */
