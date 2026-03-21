/**
 * @file shufflenet_v2.h
 * @brief ShuffleNet V2 1.0x — Public API for ARM Cortex-A Embedded Platforms
 *
 * Architecture: ShuffleNet V2 with 1.0x width multiplier
 *   Input  : 1 x 3 x 224 x 224  (CHW, float32)
 *   Output : 1000-class softmax logits
 *
 * Target hardware:
 *   CPU    : ARM Cortex-A53/A72 @ 1.5 GHz (e.g., RPi 4, i.MX 8M)
 *   RAM    : 512 MB+ DDR
 *   SIMD   : NEON 128-bit
 *   OS     : Embedded Linux
 *
 * Data layout: CHW (channels-first) throughout, matching PyTorch conventions.
 * Precision : float32 primary; int8 hooks marked with SN2_QUANT_HOOKS.
 *
 * Memory strategy:
 *   - Weights stored as const arrays (~8.7 MB float32, ~2.2 MB int8).
 *   - Activations use a ping-pong double-buffer scheme.
 *   - Optimized for L1/L2 cache locality and NEON vectorization.
 *
 * Copyright (c) 2026 — MIT License
 */

#ifndef SHUFFLENET_V2_H
#define SHUFFLENET_V2_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/*  Compile-time constants                                            */
/* ------------------------------------------------------------------ */

/** Number of output classes (ImageNet) */
#define SN2_NUM_CLASSES      1000

/** Input dimensions */
#define SN2_INPUT_C          3
#define SN2_INPUT_H          224
#define SN2_INPUT_W          224

/** Stage channel widths for 1.0x multiplier */
#define SN2_CONV1_OUT_C      24
#define SN2_STAGE2_OUT_C     116
#define SN2_STAGE3_OUT_C     232
#define SN2_STAGE4_OUT_C     464
#define SN2_CONV5_OUT_C      1024

/** Number of units per stage */
#define SN2_STAGE2_UNITS     4
#define SN2_STAGE3_UNITS     8
#define SN2_STAGE4_UNITS     4

/** Channel shuffle groups (always 2 for ShuffleNet V2) */
#define SN2_SHUFFLE_GROUPS   2

/** Maximum activation buffer size in floats.
 *  Worst case is after conv1: 24 * 56 * 56 = 75 264 floats
 *  but concat buffers during stage transitions can be larger.
 *  We allocate generously for the largest intermediate tensor.
 *  stage2 unit0 output: 116 * 28 * 28 = 90 944
 *  stage3 unit0 output: 232 * 14 * 14 = 45 472
 *  conv1 output before pool: 24 * 112 * 112 = 301 056  <-- largest
 */
#define SN2_MAX_ACT_FLOATS   (SN2_CONV5_OUT_C * 7 * 7)  /* 50 176 */

/* Actual largest single tensor in the forward pass */
#define SN2_BUF_FLOATS       (24 * 112 * 112)  /* 301 056 floats = ~1.2 MB */

/* Total activation workspace: two ping-pong buffers + one scratch */
#define SN2_WORKSPACE_FLOATS (SN2_BUF_FLOATS * 2 + SN2_BUF_FLOATS)

/* ------------------------------------------------------------------ */
/*  Data structures for layer parameters                              */
/* ------------------------------------------------------------------ */

/**
 * @brief 2-D convolution layer parameters (standard or depthwise).
 *
 * For depthwise convolution, out_c == in_c and groups == in_c.
 * Weight layout: [out_c, in_c/groups, kH, kW] stored contiguously.
 * Bias is optional (NULL when batch-norm follows).
 */
typedef struct {
    const float *weight;    /**< Filter coefficients                      */
    const float *bias;      /**< Per-channel bias (NULL if absent)        */
    int          in_c;      /**< Input channels                           */
    int          out_c;     /**< Output channels                          */
    int          kH;        /**< Kernel height                            */
    int          kW;        /**< Kernel width                             */
    int          stride;    /**< Stride (assumed equal in H and W)        */
    int          pad;       /**< Zero-padding (assumed symmetric)         */
    int          groups;    /**< 1 = standard conv, in_c = depthwise      */
} ConvLayer;

/**
 * @brief Batch normalisation parameters (inference mode: fused γ/β).
 *
 * During inference BN computes:
 *   y = γ * (x - μ) / sqrt(σ² + ε) + β
 * We store the four vectors directly; fusion into conv weights is an
 * optional optimisation (see sn2_fuse_bn).
 */
typedef struct {
    const float *gamma;     /**< Scale (weight), length = C               */
    const float *beta;      /**< Shift (bias),   length = C               */
    const float *mean;      /**< Running mean,   length = C               */
    const float *var;       /**< Running var,    length = C               */
    int          channels;  /**< Number of channels                       */
    float        eps;       /**< Epsilon for numerical stability          */
} BNLayer;

/**
 * @brief Fully-connected (dense / linear) layer.
 *
 * Weight layout: [out_features, in_features] (row-major).
 */
typedef struct {
    const float *weight;    /**< Weight matrix                            */
    const float *bias;      /**< Bias vector                              */
    int          in_features;
    int          out_features;
} FCLayer;

/**
 * @brief One branch of a ShuffleNet V2 unit.
 *
 * Downsampling branch (unit index 0):
 *   branch1: DWConv3x3(s=2) → BN → Conv1x1 → BN → ReLU
 *   branch2: Conv1x1 → BN → ReLU → DWConv3x3(s=2) → BN → Conv1x1 → BN → ReLU
 *
 * Regular branch (unit index > 0):
 *   Only branch2 is used; branch1 is the identity (channel-split).
 *   branch2: Conv1x1 → BN → ReLU → DWConv3x3(s=1) → BN → Conv1x1 → BN → ReLU
 */

/** Branch with 3 conv + 3 BN layers (branch1 of downsampling unit) */
typedef struct {
    ConvLayer dw_conv;      /**< DWConv 3x3                               */
    BNLayer   dw_bn;
    ConvLayer pw_conv;      /**< Pointwise 1x1                            */
    BNLayer   pw_bn;
} ShuffleBranch1;

/** Branch with 3 conv + 3 BN layers (branch2 of every unit) */
typedef struct {
    ConvLayer pw_conv1;     /**< First pointwise 1x1                      */
    BNLayer   pw_bn1;
    ConvLayer dw_conv;      /**< DWConv 3x3                               */
    BNLayer   dw_bn;
    ConvLayer pw_conv2;     /**< Second pointwise 1x1                     */
    BNLayer   pw_bn2;
} ShuffleBranch2;

/**
 * @brief A single ShuffleNet V2 unit (inverted residual with shuffle).
 *
 * is_downsample == 1  →  unit 0 of each stage (stride 2, uses branch1).
 * is_downsample == 0  →  regular unit (stride 1, channel-split input).
 */
typedef struct {
    int            is_downsample;
    ShuffleBranch1 branch1;   /**< Only used when is_downsample == 1      */
    ShuffleBranch2 branch2;
} ShuffleUnit;

/**
 * @brief One stage of ShuffleNet V2 (sequence of ShuffleUnits).
 */
typedef struct {
    int          num_units;
    int          in_c;        /**< Input channels to this stage            */
    int          out_c;       /**< Output channels from this stage         */
    ShuffleUnit *units;       /**< Array of num_units ShuffleUnit structs  */
} ShuffleStage;

/**
 * @brief Complete ShuffleNet V2 1.0x model.
 */
typedef struct {
    /* Stem */
    ConvLayer    conv1;       /**< 3x3 Conv2d(3→24, s=2, p=1)             */
    BNLayer      bn1;

    /* Stages */
    ShuffleStage stage2;      /**< 4 units, 24  → 116                     */
    ShuffleStage stage3;      /**< 8 units, 116 → 232                     */
    ShuffleStage stage4;      /**< 4 units, 232 → 464                     */

    /* Head */
    ConvLayer    conv5;       /**< 1x1 Conv2d(464→1024)                   */
    BNLayer      bn5;
    FCLayer      fc;          /**< Linear(1024→1000)                       */
} ShuffleNetV2;

/* ------------------------------------------------------------------ */
/*  Workspace / buffer management                                     */
/* ------------------------------------------------------------------ */

/**
 * @brief Activation workspace with ping-pong buffers.
 *
 * The forward pass alternates between buf_a and buf_b so that the
 * output of one layer can be read from one buffer while writing to
 * the other.  scratch is available for intermediate results inside
 * a single unit (e.g., branch outputs before concat).
 */
typedef struct {
    float *buf_a;             /**< Primary activation buffer               */
    float *buf_b;             /**< Secondary activation buffer             */
    float *scratch;           /**< Scratch for branch temporaries          */
    size_t buf_floats;        /**< Size of each buffer in floats           */
} SN2Workspace;

/* ------------------------------------------------------------------ */
/*  Public API                                                        */
/* ------------------------------------------------------------------ */

/**
 * @brief Allocate and zero-initialise the model struct.
 *
 * Does NOT load weights — call sn2_load_weights() afterwards.
 * @return Pointer to heap-allocated ShuffleNetV2, or NULL on failure.
 */
ShuffleNetV2 *sn2_create_model(void);

/**
 * @brief Free all memory associated with the model (struct + units).
 */
void sn2_destroy_model(ShuffleNetV2 *model);

/**
 * @brief Load pre-trained weights from a flat binary file.
 *
 * The binary format is a sequence of float32 arrays in the order
 * produced by export_weights.py.  Each layer's weight and BN params
 * are laid out contiguously.
 *
 * @param model   Model struct (already created).
 * @param path    Path to the .bin weight file.
 * @return 0 on success, -1 on error.
 */
int sn2_load_weights(ShuffleNetV2 *model, const char *path);

/**
 * @brief Initialise the activation workspace.
 *
 * @param ws          Pointer to an SN2Workspace struct.
 * @param ext_memory  Base address of a contiguous memory region (e.g.,
 *                    SDRAM) for buffers, or NULL to malloc.
 * @param mem_bytes   Size of ext_memory in bytes (ignored if NULL).
 * @return 0 on success, -1 if memory is insufficient.
 */
int sn2_workspace_init(SN2Workspace *ws, void *ext_memory, size_t mem_bytes);

/**
 * @brief Free workspace buffers (only if they were malloc'd).
 */
void sn2_workspace_free(SN2Workspace *ws);

/**
 * @brief Run full forward inference.
 *
 * @param model   Initialised model with weights loaded.
 * @param input   Input tensor, CHW float32, size 3×224×224.
 * @param output  Output buffer, at least 1000 floats.
 * @param ws      Initialised workspace.
 * @return 0 on success.
 */
int sn2_forward(const ShuffleNetV2 *model,
                const float        *input,
                float              *output,
                SN2Workspace       *ws);

/* ------------------------------------------------------------------ */
/*  Low-level operations (exposed for unit testing / profiling)       */
/* ------------------------------------------------------------------ */

/** Standard or grouped 2-D convolution (CHW layout). */
void sn2_conv2d(const ConvLayer *layer,
                const float *input,  int inH, int inW,
                float *output);

/** Depthwise 3x3 convolution (optimised path). */
void sn2_dwconv3x3(const ConvLayer *layer,
                   const float *input, int inH, int inW,
                   float *output);

/** Batch normalisation (inference). */
void sn2_batchnorm(const BNLayer *layer,
                   float *data, int H, int W);

/** ReLU activation (in-place). */
void sn2_relu(float *data, int count);

/** Max pooling 3x3, stride 2, pad 1. */
void sn2_maxpool2d(const float *input, int C, int H, int W,
                   float *output);

/** Global average pooling over spatial dims. */
void sn2_global_avg_pool(const float *input, int C, int H, int W,
                         float *output);

/** Fully-connected layer. */
void sn2_fc(const FCLayer *layer,
            const float *input, float *output);

/** Channel shuffle: reshape to (2, C/2, H, W), transpose → (C/2, 2, H, W), flatten. */
void sn2_channel_shuffle(float *data, int C, int H, int W);

/** Split tensor along channel axis into two equal halves (pointers only). */
void sn2_channel_split(const float *input, int C, int H, int W,
                       const float **out_a, const float **out_b);

/** Concatenate two tensors along channel axis. */
void sn2_channel_concat(const float *a, int Ca,
                        const float *b, int Cb,
                        int H, int W,
                        float *output);

/* ------------------------------------------------------------------ */
/*  Utility                                                           */
/* ------------------------------------------------------------------ */

/**
 * @brief Allocate zero-filled dummy weights for smoke-testing.
 *
 * This allows the forward pass to run without a real weight file.
 * All outputs will be zero/uniform, but it validates the data flow.
 *
 * @return 0 on success, -1 on allocation failure.
 */
int sn2_init_dummy_weights(ShuffleNetV2 *model);

/** Return total number of model parameters (for diagnostics). */
size_t sn2_param_count(const ShuffleNetV2 *model);

/** Print a summary of each layer's shape to stdout. */
void sn2_print_summary(const ShuffleNetV2 *model);

/* ------------------------------------------------------------------ */
/*  Quantisation hooks (future)                                       */
/* ------------------------------------------------------------------ */
#ifdef SN2_QUANT_HOOKS
/* Placeholder for int8 inference path */
int sn2_forward_q8(const ShuffleNetV2 *model,
                   const int8_t       *input,
                   float              *output,
                   SN2Workspace       *ws);
#endif

#ifdef __cplusplus
}
#endif

#endif /* SHUFFLENET_V2_H */
