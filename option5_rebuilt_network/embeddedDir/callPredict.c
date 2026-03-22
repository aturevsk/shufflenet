/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: callPredict.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:41:39
 */

/* Include Files */
#include "callPredict.h"
#include "cat.h"
#include "conv2dDirectOptimizedColMajor.h"
#include "pool.h"
#include "predict_shufflenet_v5_rtwutil.h"
#include "reshape.h"
#include "omp.h"
#include <arm_neon.h>
#include <string.h>

/* Type Definitions */
#ifndef typedef_cell_wrap_20
#define typedef_cell_wrap_20
typedef struct {
  float f1[45472];
} cell_wrap_20;
#endif /* typedef_cell_wrap_20 */

#ifndef typedef_cell_wrap_26
#define typedef_cell_wrap_26
typedef struct {
  float f1[22736];
} cell_wrap_26;
#endif /* typedef_cell_wrap_26 */

#ifndef typedef_cell_wrap_29
#define typedef_cell_wrap_29
typedef struct {
  float f1[11368];
} cell_wrap_29;
#endif /* typedef_cell_wrap_29 */

/* Function Declarations */
static void b_fromBlockedLayoutTransform(const float *inputTensor,
                                         float *outputTensor);

static void b_toBlockedLayoutTransform(const float *inputTensor,
                                       float *outputTensor);

static void c_fromBlockedLayoutTransform(const float *inputTensor,
                                         float *outputTensor);

static void c_matrixMultiply163683382385183(int M, int K, int N, int blockSizeM,
                                            int blockSizeK, int blockSizeN,
                                            const float *A, const float *B,
                                            float *C);

static void c_toBlockedLayoutTransform(const float *inputTensor,
                                       float *outputTensor);

static void d_fromBlockedLayoutTransform(const float *inputTensor,
                                         float *outputTensor);

static void d_toBlockedLayoutTransform(const float *inputTensor,
                                       float *outputTensor);

static int div_nde_s32_floor(void);

static int div_s32_floor(int numerator, int denominator);

static void e_fromBlockedLayoutTransform(const float *inputTensor,
                                         float *outputTensor);

static void e_toBlockedLayoutTransform(const float *inputTensor,
                                       float *outputTensor);

static void f_fromBlockedLayoutTransform(const float *inputTensor,
                                         float *outputTensor);

static void f_toBlockedLayoutTransform(const float *inputTensor,
                                       float *outputTensor);

static void fromBlockedLayoutTransform(const float *inputTensor,
                                       float *outputTensor);

static void macroKernel16368338238518345485(int M, int K, int N, const float *A,
                                            int LDA, const float *B, int LDB,
                                            float *C, int LDC);

static void microKernel10161931794758542154(int K, const float *A, int LDA,
                                            const float *B, int LDB, float *C,
                                            int LDC);

static void microKernel17022649706040950902(int K, const float *A, int LDA,
                                            const float *B, int LDB, float *C,
                                            int LDC);

static void microKernel2626875722099002257(int K, const float *A, int LDA,
                                           const float *B, int LDB, float *C,
                                           int LDC);

static void toBlockedLayoutTransform(const float *inputTensor,
                                     float *outputTensor);

/* Function Definitions */
/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 * Return Type  : void
 */
static void b_fromBlockedLayoutTransform(const float *inputTensor,
                                         float *outputTensor)
{
  int blockIdx;
  int fusedBlockIdx;
  int fusedImageIdx;
  int outputTensorBaseIdx;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        fusedBlockIdx, blockIdx, outputTensorBaseIdx)

  for (fusedImageIdx = 0; fusedImageIdx < 11368; fusedImageIdx++) {
    fusedBlockIdx = fusedImageIdx % 11368;
    blockIdx = (int)((unsigned int)fusedBlockIdx / 196U);
    fusedBlockIdx %= 196;
    outputTensorBaseIdx = blockIdx * 784 + fusedBlockIdx;
    fusedBlockIdx = blockIdx * 784 + (fusedBlockIdx << 2);
    outputTensor[outputTensorBaseIdx] = inputTensor[fusedBlockIdx];
    outputTensor[outputTensorBaseIdx + 196] = inputTensor[fusedBlockIdx + 1];
    outputTensor[outputTensorBaseIdx + 392] = inputTensor[fusedBlockIdx + 2];
    outputTensor[outputTensorBaseIdx + 588] = inputTensor[fusedBlockIdx + 3];
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 * Return Type  : void
 */
static void b_toBlockedLayoutTransform(const float *inputTensor,
                                       float *outputTensor)
{
  int blockIdx;
  int fusedBlockIdx;
  int fusedImageIdx;
  int inputChannelBlockBaseIdx;
  int inputWidthIdx;
  memset(outputTensor, 0, (unsigned int)((int)sizeof(float) * 90944));
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        fusedBlockIdx, blockIdx, inputWidthIdx, inputChannelBlockBaseIdx)

  for (fusedImageIdx = 0; fusedImageIdx < 22736; fusedImageIdx++) {
    fusedBlockIdx = fusedImageIdx % 22736;
    blockIdx = (int)((unsigned int)fusedBlockIdx / 784U);
    fusedBlockIdx %= 784;
    inputWidthIdx = (int)((unsigned int)fusedBlockIdx / 28U);
    fusedBlockIdx %= 28;
    inputChannelBlockBaseIdx =
        (fusedBlockIdx + inputWidthIdx * 28) + blockIdx * 3136;
    fusedBlockIdx =
        ((fusedBlockIdx << 2) + inputWidthIdx * 112) + blockIdx * 3136;
    outputTensor[fusedBlockIdx] = inputTensor[inputChannelBlockBaseIdx];
    outputTensor[fusedBlockIdx + 1] =
        inputTensor[inputChannelBlockBaseIdx + 784];
    outputTensor[fusedBlockIdx + 2] =
        inputTensor[inputChannelBlockBaseIdx + 1568];
    outputTensor[fusedBlockIdx + 3] =
        inputTensor[inputChannelBlockBaseIdx + 2352];
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 * Return Type  : void
 */
static void c_fromBlockedLayoutTransform(const float *inputTensor,
                                         float *outputTensor)
{
  int blockIdx;
  int fusedBlockIdx;
  int fusedImageIdx;
  int outputTensorBaseIdx;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        fusedBlockIdx, blockIdx, outputTensorBaseIdx)

  for (fusedImageIdx = 0; fusedImageIdx < 5684; fusedImageIdx++) {
    fusedBlockIdx = fusedImageIdx % 5684;
    blockIdx = (int)((unsigned int)fusedBlockIdx / 196U);
    fusedBlockIdx %= 196;
    outputTensorBaseIdx = blockIdx * 784 + fusedBlockIdx;
    fusedBlockIdx = blockIdx * 784 + (fusedBlockIdx << 2);
    outputTensor[outputTensorBaseIdx] = inputTensor[fusedBlockIdx];
    outputTensor[outputTensorBaseIdx + 196] = inputTensor[fusedBlockIdx + 1];
    outputTensor[outputTensorBaseIdx + 392] = inputTensor[fusedBlockIdx + 2];
    outputTensor[outputTensorBaseIdx + 588] = inputTensor[fusedBlockIdx + 3];
  }
}

/*
 * Arguments    : int M
 *                int K
 *                int N
 *                int blockSizeM
 *                int blockSizeK
 *                int blockSizeN
 *                const float *A
 *                const float *B
 *                float *C
 * Return Type  : void
 */
static void c_matrixMultiply163683382385183(int M, int K, int N, int blockSizeM,
                                            int blockSizeK, int blockSizeN,
                                            const float *A, const float *B,
                                            float *C)
{
  const float *ptrB;
  int b_i;
  int b_j1;
  int i;
  int i0;
  int i0_ub;
  int k0;
  int k0_ub;
  memset(C, 0, (unsigned int)(M * N * (int)sizeof(float)));
  if (blockSizeM >= M) {
    blockSizeM = M;
  } else {
    blockSizeM = div_nde_s32_floor() * 28;
    if (blockSizeM <= 0) {
      blockSizeM = 1;
    }
  }
  if (blockSizeN >= N) {
    blockSizeN = N;
  } else if (blockSizeN <= 0) {
    blockSizeN = 1;
  }
  i0_ub = div_s32_floor(M - 1, blockSizeM) + 1;
  k0_ub = div_s32_floor(K - 1, blockSizeK) + 1;
  for (b_j1 = 0; b_j1 < N; b_j1 += blockSizeN) {
    int N2;
    if (b_j1 > N - blockSizeN) {
      N2 = N - b_j1;
    } else {
      N2 = blockSizeN;
    }
    for (k0 = 1; k0 <= k0_ub; k0++) {
      int K2;
      int k;
      k = (k0 - 1) * blockSizeK;
      if (k > K - blockSizeK) {
        K2 = K - k;
      } else {
        K2 = blockSizeK;
      }
      ptrB = &B[k + K * b_j1];
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i, b_i)

      for (i0 = 1; i0 <= i0_ub; i0++) {
        i = (i0 - 1) * blockSizeM;
        if (i > M - blockSizeM) {
          b_i = M - i;
        } else {
          b_i = blockSizeM;
        }
        macroKernel16368338238518345485(b_i, K2, N2, &A[i + M * k], M, ptrB, K,
                                        &C[i + M * b_j1], M);
      }
    }
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 * Return Type  : void
 */
static void c_toBlockedLayoutTransform(const float *inputTensor,
                                       float *outputTensor)
{
  int blockIdx;
  int fusedBlockIdx;
  int fusedImageIdx;
  int inputChannelBlockBaseIdx;
  int inputWidthIdx;
  memset(outputTensor, 0, (unsigned int)((int)sizeof(float) * 22736));
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        fusedBlockIdx, blockIdx, inputWidthIdx, inputChannelBlockBaseIdx)

  for (fusedImageIdx = 0; fusedImageIdx < 5684; fusedImageIdx++) {
    fusedBlockIdx = fusedImageIdx % 5684;
    blockIdx = (int)((unsigned int)fusedBlockIdx / 196U);
    fusedBlockIdx %= 196;
    inputWidthIdx = (int)((unsigned int)fusedBlockIdx / 14U);
    fusedBlockIdx %= 14;
    inputChannelBlockBaseIdx =
        (fusedBlockIdx + inputWidthIdx * 14) + blockIdx * 784;
    fusedBlockIdx =
        ((fusedBlockIdx << 2) + inputWidthIdx * 56) + blockIdx * 784;
    outputTensor[fusedBlockIdx] = inputTensor[inputChannelBlockBaseIdx];
    outputTensor[fusedBlockIdx + 1] =
        inputTensor[inputChannelBlockBaseIdx + 196];
    outputTensor[fusedBlockIdx + 2] =
        inputTensor[inputChannelBlockBaseIdx + 392];
    outputTensor[fusedBlockIdx + 3] =
        inputTensor[inputChannelBlockBaseIdx + 588];
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 * Return Type  : void
 */
static void d_fromBlockedLayoutTransform(const float *inputTensor,
                                         float *outputTensor)
{
  int blockIdx;
  int fusedBlockIdx;
  int fusedImageIdx;
  int outputTensorBaseIdx;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        fusedBlockIdx, blockIdx, outputTensorBaseIdx)

  for (fusedImageIdx = 0; fusedImageIdx < 5684; fusedImageIdx++) {
    fusedBlockIdx = fusedImageIdx % 5684;
    blockIdx = (int)((unsigned int)fusedBlockIdx / 49U);
    fusedBlockIdx %= 49;
    outputTensorBaseIdx = blockIdx * 196 + fusedBlockIdx;
    fusedBlockIdx = blockIdx * 196 + (fusedBlockIdx << 2);
    outputTensor[outputTensorBaseIdx] = inputTensor[fusedBlockIdx];
    outputTensor[outputTensorBaseIdx + 49] = inputTensor[fusedBlockIdx + 1];
    outputTensor[outputTensorBaseIdx + 98] = inputTensor[fusedBlockIdx + 2];
    outputTensor[outputTensorBaseIdx + 147] = inputTensor[fusedBlockIdx + 3];
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 * Return Type  : void
 */
static void d_toBlockedLayoutTransform(const float *inputTensor,
                                       float *outputTensor)
{
  int blockIdx;
  int fusedBlockIdx;
  int fusedImageIdx;
  int inputChannelBlockBaseIdx;
  int inputWidthIdx;
  memset(outputTensor, 0, (unsigned int)((int)sizeof(float) * 45472));
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        fusedBlockIdx, blockIdx, inputWidthIdx, inputChannelBlockBaseIdx)

  for (fusedImageIdx = 0; fusedImageIdx < 11368; fusedImageIdx++) {
    fusedBlockIdx = fusedImageIdx % 11368;
    blockIdx = (int)((unsigned int)fusedBlockIdx / 196U);
    fusedBlockIdx %= 196;
    inputWidthIdx = (int)((unsigned int)fusedBlockIdx / 14U);
    fusedBlockIdx %= 14;
    inputChannelBlockBaseIdx =
        (fusedBlockIdx + inputWidthIdx * 14) + blockIdx * 784;
    fusedBlockIdx =
        ((fusedBlockIdx << 2) + inputWidthIdx * 56) + blockIdx * 784;
    outputTensor[fusedBlockIdx] = inputTensor[inputChannelBlockBaseIdx];
    outputTensor[fusedBlockIdx + 1] =
        inputTensor[inputChannelBlockBaseIdx + 196];
    outputTensor[fusedBlockIdx + 2] =
        inputTensor[inputChannelBlockBaseIdx + 392];
    outputTensor[fusedBlockIdx + 3] =
        inputTensor[inputChannelBlockBaseIdx + 588];
  }
}

/*
 * Arguments    : void
 * Return Type  : int
 */
static int div_nde_s32_floor(void)
{
  return 2;
}

/*
 * Arguments    : int numerator
 *                int denominator
 * Return Type  : int
 */
static int div_s32_floor(int numerator, int denominator)
{
  return (int)((unsigned int)numerator / (unsigned int)denominator);
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 * Return Type  : void
 */
static void e_fromBlockedLayoutTransform(const float *inputTensor,
                                         float *outputTensor)
{
  int blockIdx;
  int fusedBlockIdx;
  int fusedImageIdx;
  int outputTensorBaseIdx;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        fusedBlockIdx, blockIdx, outputTensorBaseIdx)

  for (fusedImageIdx = 0; fusedImageIdx < 2842; fusedImageIdx++) {
    fusedBlockIdx = fusedImageIdx % 2842;
    blockIdx = (int)((unsigned int)fusedBlockIdx / 49U);
    fusedBlockIdx %= 49;
    outputTensorBaseIdx = blockIdx * 196 + fusedBlockIdx;
    fusedBlockIdx = blockIdx * 196 + (fusedBlockIdx << 2);
    outputTensor[outputTensorBaseIdx] = inputTensor[fusedBlockIdx];
    outputTensor[outputTensorBaseIdx + 49] = inputTensor[fusedBlockIdx + 1];
    outputTensor[outputTensorBaseIdx + 98] = inputTensor[fusedBlockIdx + 2];
    outputTensor[outputTensorBaseIdx + 147] = inputTensor[fusedBlockIdx + 3];
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 * Return Type  : void
 */
static void e_toBlockedLayoutTransform(const float *inputTensor,
                                       float *outputTensor)
{
  int blockIdx;
  int fusedBlockIdx;
  int fusedImageIdx;
  int inputChannelBlockBaseIdx;
  int inputWidthIdx;
  memset(outputTensor, 0, (unsigned int)((int)sizeof(float) * 11368));
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        fusedBlockIdx, blockIdx, inputWidthIdx, inputChannelBlockBaseIdx)

  for (fusedImageIdx = 0; fusedImageIdx < 2842; fusedImageIdx++) {
    fusedBlockIdx = fusedImageIdx % 2842;
    blockIdx = (int)((unsigned int)fusedBlockIdx / 49U);
    fusedBlockIdx %= 49;
    inputWidthIdx = (int)((unsigned int)fusedBlockIdx / 7U);
    fusedBlockIdx %= 7;
    inputChannelBlockBaseIdx =
        (fusedBlockIdx + inputWidthIdx * 7) + blockIdx * 196;
    fusedBlockIdx =
        ((fusedBlockIdx << 2) + inputWidthIdx * 28) + blockIdx * 196;
    outputTensor[fusedBlockIdx] = inputTensor[inputChannelBlockBaseIdx];
    outputTensor[fusedBlockIdx + 1] =
        inputTensor[inputChannelBlockBaseIdx + 49];
    outputTensor[fusedBlockIdx + 2] =
        inputTensor[inputChannelBlockBaseIdx + 98];
    outputTensor[fusedBlockIdx + 3] =
        inputTensor[inputChannelBlockBaseIdx + 147];
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 * Return Type  : void
 */
static void f_fromBlockedLayoutTransform(const float *inputTensor,
                                         float *outputTensor)
{
  int fusedImageIdx;
  int outputTensorBaseIdx;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        outputTensorBaseIdx)

  for (fusedImageIdx = 0; fusedImageIdx < 256; fusedImageIdx++) {
    outputTensorBaseIdx = (fusedImageIdx % 256) << 2;
    outputTensor[outputTensorBaseIdx] = inputTensor[outputTensorBaseIdx];
    outputTensor[outputTensorBaseIdx + 1] =
        inputTensor[outputTensorBaseIdx + 1];
    outputTensor[outputTensorBaseIdx + 2] =
        inputTensor[outputTensorBaseIdx + 2];
    outputTensor[outputTensorBaseIdx + 3] =
        inputTensor[outputTensorBaseIdx + 3];
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 * Return Type  : void
 */
static void f_toBlockedLayoutTransform(const float *inputTensor,
                                       float *outputTensor)
{
  int blockIdx;
  int fusedBlockIdx;
  int fusedImageIdx;
  int inputChannelBlockBaseIdx;
  int inputWidthIdx;
  memset(outputTensor, 0, (unsigned int)((int)sizeof(float) * 22736));
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        fusedBlockIdx, blockIdx, inputWidthIdx, inputChannelBlockBaseIdx)

  for (fusedImageIdx = 0; fusedImageIdx < 5684; fusedImageIdx++) {
    fusedBlockIdx = fusedImageIdx % 5684;
    blockIdx = (int)((unsigned int)fusedBlockIdx / 49U);
    fusedBlockIdx %= 49;
    inputWidthIdx = (int)((unsigned int)fusedBlockIdx / 7U);
    fusedBlockIdx %= 7;
    inputChannelBlockBaseIdx =
        (fusedBlockIdx + inputWidthIdx * 7) + blockIdx * 196;
    fusedBlockIdx =
        ((fusedBlockIdx << 2) + inputWidthIdx * 28) + blockIdx * 196;
    outputTensor[fusedBlockIdx] = inputTensor[inputChannelBlockBaseIdx];
    outputTensor[fusedBlockIdx + 1] =
        inputTensor[inputChannelBlockBaseIdx + 49];
    outputTensor[fusedBlockIdx + 2] =
        inputTensor[inputChannelBlockBaseIdx + 98];
    outputTensor[fusedBlockIdx + 3] =
        inputTensor[inputChannelBlockBaseIdx + 147];
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 * Return Type  : void
 */
static void fromBlockedLayoutTransform(const float *inputTensor,
                                       float *outputTensor)
{
  int blockIdx;
  int fusedBlockIdx;
  int fusedImageIdx;
  int inputTensorBaseIdx;
  int outputChannelIdx;
  int outputTensorBaseIdx;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        fusedBlockIdx, blockIdx, outputTensorBaseIdx, inputTensorBaseIdx,      \
            outputChannelIdx)

  for (fusedImageIdx = 0; fusedImageIdx < 11760; fusedImageIdx++) {
    fusedBlockIdx = fusedImageIdx % 11760;
    blockIdx = (int)((unsigned int)fusedBlockIdx / 784U);
    fusedBlockIdx %= 784;
    outputTensorBaseIdx = blockIdx * 3136 + fusedBlockIdx;
    inputTensorBaseIdx = blockIdx * 3136 + (fusedBlockIdx << 2);
    if (blockIdx == 14) {
      fusedBlockIdx = 2;
    } else {
      fusedBlockIdx = 4;
    }
    for (outputChannelIdx = 1; outputChannelIdx <= fusedBlockIdx;
         outputChannelIdx++) {
      outputTensor[outputTensorBaseIdx + (outputChannelIdx - 1) * 784] =
          inputTensor[(inputTensorBaseIdx + outputChannelIdx) - 1];
    }
  }
}

/*
 * Arguments    : int M
 *                int K
 *                int N
 *                const float *A
 *                int LDA
 *                const float *B
 *                int LDB
 *                float *C
 *                int LDC
 * Return Type  : void
 */
static void macroKernel16368338238518345485(int M, int K, int N, const float *A,
                                            int LDA, const float *B, int LDB,
                                            float *C, int LDC)
{
  int idxB;
  int j;
  j = 0;
  idxB = 0;
  while (j < N) {
    int i;
    int idxA;
    int idxC;
    idxC = LDC * j;
    i = 0;
    idxA = 0;
    while (i <= M - 28) {
      microKernel10161931794758542154(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
                                      LDC);
      idxA += 28;
      idxC += 28;
      i += 28;
    }
    while (i <= M - 4) {
      microKernel17022649706040950902(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
                                      LDC);
      idxA += 4;
      idxC += 4;
      i += 4;
    }
    while (i <= M - 1) {
      microKernel2626875722099002257(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
                                     LDC);
      idxA++;
      idxC++;
      i++;
    }
    idxB += LDB;
    j++;
  }
}

/*
 * Arguments    : int K
 *                const float *A
 *                int LDA
 *                const float *B
 *                int LDB
 *                float *C
 *                int LDC
 * Return Type  : void
 */
static void microKernel10161931794758542154(int K, const float *A, int LDA,
                                            const float *B, int LDB, float *C,
                                            int LDC)
{
  float32x4_t b_c;
  float32x4_t c;
  float32x4_t c_c;
  float32x4_t d_c;
  float32x4_t e_c;
  float32x4_t f_c;
  float32x4_t g_c;
  int idxA;
  int idxB;
  int k;
  (void)LDB;
  (void)LDC;
  idxA = 0;
  idxB = 0;
  c = vld1q_f32(&C[0]);
  b_c = vld1q_f32(&C[4]);
  c_c = vld1q_f32(&C[8]);
  d_c = vld1q_f32(&C[12]);
  e_c = vld1q_f32(&C[16]);
  f_c = vld1q_f32(&C[20]);
  g_c = vld1q_f32(&C[24]);
  for (k = 0; k < K; k++) {
    float32x4_t b;
    b = vdupq_n_f32(B[idxB]);
    c = vaddq_f32(c, vmulq_f32(vld1q_f32(&A[idxA]), b));
    b_c = vaddq_f32(b_c, vmulq_f32(vld1q_f32(&A[idxA + 4]), b));
    c_c = vaddq_f32(c_c, vmulq_f32(vld1q_f32(&A[idxA + 8]), b));
    d_c = vaddq_f32(d_c, vmulq_f32(vld1q_f32(&A[idxA + 12]), b));
    e_c = vaddq_f32(e_c, vmulq_f32(vld1q_f32(&A[idxA + 16]), b));
    f_c = vaddq_f32(f_c, vmulq_f32(vld1q_f32(&A[idxA + 20]), b));
    g_c = vaddq_f32(g_c, vmulq_f32(vld1q_f32(&A[idxA + 24]), b));
    idxA += LDA;
    idxB++;
  }
  vst1q_f32(&C[0], c);
  vst1q_f32(&C[4], b_c);
  vst1q_f32(&C[8], c_c);
  vst1q_f32(&C[12], d_c);
  vst1q_f32(&C[16], e_c);
  vst1q_f32(&C[20], f_c);
  vst1q_f32(&C[24], g_c);
}

/*
 * Arguments    : int K
 *                const float *A
 *                int LDA
 *                const float *B
 *                int LDB
 *                float *C
 *                int LDC
 * Return Type  : void
 */
static void microKernel17022649706040950902(int K, const float *A, int LDA,
                                            const float *B, int LDB, float *C,
                                            int LDC)
{
  float32x4_t c;
  int idxA;
  int idxB;
  int k;
  (void)LDB;
  (void)LDC;
  idxA = 0;
  idxB = 0;
  c = vld1q_f32(&C[0]);
  for (k = 0; k < K; k++) {
    c = vaddq_f32(c, vmulq_f32(vld1q_f32(&A[idxA]), vdupq_n_f32(B[idxB])));
    idxA += LDA;
    idxB++;
  }
  vst1q_f32(&C[0], c);
}

/*
 * Arguments    : int K
 *                const float *A
 *                int LDA
 *                const float *B
 *                int LDB
 *                float *C
 *                int LDC
 * Return Type  : void
 */
static void microKernel2626875722099002257(int K, const float *A, int LDA,
                                           const float *B, int LDB, float *C,
                                           int LDC)
{
  float c;
  int idxA;
  int idxB;
  int k;
  (void)LDB;
  (void)LDC;
  idxA = 0;
  idxB = 0;
  c = C[0];
  for (k = 0; k < K; k++) {
    c += A[idxA] * B[idxB];
    idxA += LDA;
    idxB++;
  }
  C[0] = c;
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 * Return Type  : void
 */
static void toBlockedLayoutTransform(const float *inputTensor,
                                     float *outputTensor)
{
  int blockIdx;
  int fusedBlockIdx;
  int fusedImageIdx;
  int inputChannelBlockBaseIdx;
  int inputWidthIdx;
  int outputChannelIdx;
  memset(outputTensor, 0, (unsigned int)((int)sizeof(float) * 47040));
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        fusedBlockIdx, blockIdx, inputWidthIdx, inputChannelBlockBaseIdx,      \
            outputChannelIdx)

  for (fusedImageIdx = 0; fusedImageIdx < 11760; fusedImageIdx++) {
    fusedBlockIdx = fusedImageIdx % 11760;
    blockIdx = (int)((unsigned int)fusedBlockIdx / 784U);
    fusedBlockIdx %= 784;
    inputWidthIdx = (int)((unsigned int)fusedBlockIdx / 28U);
    fusedBlockIdx %= 28;
    inputChannelBlockBaseIdx =
        (fusedBlockIdx + inputWidthIdx * 28) + blockIdx * 3136;
    inputWidthIdx =
        ((fusedBlockIdx << 2) + inputWidthIdx * 112) + blockIdx * 3136;
    if (blockIdx == 14) {
      fusedBlockIdx = 2;
    } else {
      fusedBlockIdx = 4;
    }
    for (outputChannelIdx = 1; outputChannelIdx <= fusedBlockIdx;
         outputChannelIdx++) {
      outputTensor[(inputWidthIdx + outputChannelIdx) - 1] =
          inputTensor[inputChannelBlockBaseIdx + (outputChannelIdx - 1) * 784];
    }
  }
}

/*
 * Arguments    : const float inputsT_0_f1[150528]
 *                float outputs_0_f1[1000]
 * Return Type  : void
 */
void predict(const float inputsT_0_f1[150528], float outputs_0_f1[1000])
{
  static cell_wrap_20 outT_f13[2];
  static cell_wrap_26 outT_f46[2];
  static cell_wrap_29 outT_f111[2];
  static float t0_Weights[1024000];
  static float c_X[301056];
  static float outT_f7_0_f1[188160];
  static float b_tempData[90944];
  static float e_tempData[90944];
  static float tempData[90944];
  static float Z[75264];
  static float X[50176];
  static float outT_f16_0_f1[47040];
  static float outT_f5_0_f1[47040];
  static float outT_f9_0_f1[47040];
  static float c_tempData[45472];
  static float outT_f102_0_f1[45472];
  static float outT_f10_0_f1[45472];
  static float d_tempData[22736];
  static float objY_Data[22736];
  static float outT_f39_0_f1[22736];
  static float outT_f42_0_f1[22736];
  static float outT_f4_0_f1[18816];
  static float fv[1000];
  static bool bufferInitialized;
  float outT_f103_0_f1[11368];
  float outT_f104_0_f1[11368];
  float outT_f107_0_f1[11368];
  float b_X[1024];
  float b_Z[1024];
  int i;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&t0_Weights[0],
                              "./embeddedDir//largeDnnConstants_13931762.bin",
                              1024000);
    readDnnConstants_real32_T(
        &fv[0], "./embeddedDir//largeDnnConstants_13931766.bin", 1000);
  }
  bufferInitialized = true;
  conv2dDirectOptimizedColMajor(inputsT_0_f1, c_X);
  pool(c_X, Z);
  b_conv2dDirectOptimizedColMajor(Z, outT_f4_0_f1);
  c_conv2dDirectOptimizedColMajor(outT_f4_0_f1, outT_f5_0_f1);
  fromBlockedLayoutTransform(&outT_f5_0_f1[0], &c_tempData[0]);
  d_conv2dDirectOptimizedColMajor(Z, outT_f7_0_f1);
  e_conv2dDirectOptimizedColMajor(outT_f7_0_f1, outT_f5_0_f1);
  f_conv2dDirectOptimizedColMajor(outT_f5_0_f1, outT_f9_0_f1);
  fromBlockedLayoutTransform(&outT_f9_0_f1[0], &outT_f10_0_f1[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  memcpy(&b_tempData[0], &c_tempData[0], 45472U * sizeof(float));
  memcpy(&b_tempData[45472], &outT_f10_0_f1[0], 45472U * sizeof(float));
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  dlarray_reshape(b_tempData, tempData);
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&outT_f13[0].f1[0], &tempData[0], 45472U * sizeof(float));
  memcpy(&outT_f13[1].f1[0], &tempData[45472], 45472U * sizeof(float));
  toBlockedLayoutTransform(&outT_f13[1].f1[0], &outT_f5_0_f1[0]);
  g_conv2dDirectOptimizedColMajor(outT_f5_0_f1, outT_f9_0_f1);
  h_conv2dDirectOptimizedColMajor(outT_f9_0_f1, outT_f16_0_f1);
  i_conv2dDirectOptimizedColMajor(outT_f16_0_f1, outT_f5_0_f1);
  fromBlockedLayoutTransform(&outT_f5_0_f1[0], &c_tempData[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  memcpy(&b_tempData[0], &outT_f13[0].f1[0], 45472U * sizeof(float));
  memcpy(&b_tempData[45472], &c_tempData[0], 45472U * sizeof(float));
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  dlarray_reshape(b_tempData, tempData);
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&outT_f13[0].f1[0], &tempData[0], 45472U * sizeof(float));
  memcpy(&outT_f13[1].f1[0], &tempData[45472], 45472U * sizeof(float));
  toBlockedLayoutTransform(&outT_f13[1].f1[0], &outT_f5_0_f1[0]);
  j_conv2dDirectOptimizedColMajor(outT_f5_0_f1, outT_f9_0_f1);
  k_conv2dDirectOptimizedColMajor(outT_f9_0_f1, outT_f16_0_f1);
  l_conv2dDirectOptimizedColMajor(outT_f16_0_f1, outT_f5_0_f1);
  fromBlockedLayoutTransform(&outT_f5_0_f1[0], &c_tempData[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  memcpy(&b_tempData[0], &outT_f13[0].f1[0], 45472U * sizeof(float));
  memcpy(&b_tempData[45472], &c_tempData[0], 45472U * sizeof(float));
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  dlarray_reshape(b_tempData, tempData);
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&outT_f13[0].f1[0], &tempData[0], 45472U * sizeof(float));
  memcpy(&outT_f13[1].f1[0], &tempData[45472], 45472U * sizeof(float));
  toBlockedLayoutTransform(&outT_f13[1].f1[0], &outT_f5_0_f1[0]);
  m_conv2dDirectOptimizedColMajor(outT_f5_0_f1, outT_f9_0_f1);
  n_conv2dDirectOptimizedColMajor(outT_f9_0_f1, outT_f16_0_f1);
  o_conv2dDirectOptimizedColMajor(outT_f16_0_f1, outT_f5_0_f1);
  fromBlockedLayoutTransform(&outT_f5_0_f1[0], &c_tempData[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  memcpy(&b_tempData[0], &outT_f13[0].f1[0], 45472U * sizeof(float));
  memcpy(&b_tempData[45472], &c_tempData[0], 45472U * sizeof(float));
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  dlarray_reshape(b_tempData, e_tempData);
  b_toBlockedLayoutTransform(&e_tempData[0], &tempData[0]);
  p_conv2dDirectOptimizedColMajor(tempData, d_tempData);
  q_conv2dDirectOptimizedColMajor(d_tempData, outT_f39_0_f1);
  r_conv2dDirectOptimizedColMajor(tempData, b_tempData);
  s_conv2dDirectOptimizedColMajor(b_tempData, d_tempData);
  t_conv2dDirectOptimizedColMajor(d_tempData, outT_f42_0_f1);
  cat(outT_f39_0_f1, outT_f42_0_f1, c_tempData);
  b_fromBlockedLayoutTransform(&c_tempData[0], &outT_f102_0_f1[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  b_dlarray_reshape(outT_f102_0_f1, c_tempData);
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&outT_f46[0].f1[0], &c_tempData[0], 22736U * sizeof(float));
  memcpy(&outT_f46[1].f1[0], &c_tempData[22736], 22736U * sizeof(float));
  c_toBlockedLayoutTransform(&outT_f46[1].f1[0], &d_tempData[0]);
  u_conv2dDirectOptimizedColMajor(d_tempData, outT_f42_0_f1);
  v_conv2dDirectOptimizedColMajor(outT_f42_0_f1, d_tempData);
  w_conv2dDirectOptimizedColMajor(d_tempData, outT_f42_0_f1);
  c_fromBlockedLayoutTransform(&outT_f42_0_f1[0], &d_tempData[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  cat(outT_f46[0].f1, d_tempData, outT_f10_0_f1);
  b_dlarray_reshape(outT_f10_0_f1, c_tempData);
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&outT_f46[0].f1[0], &c_tempData[0], 22736U * sizeof(float));
  memcpy(&outT_f46[1].f1[0], &c_tempData[22736], 22736U * sizeof(float));
  c_toBlockedLayoutTransform(&outT_f46[1].f1[0], &d_tempData[0]);
  x_conv2dDirectOptimizedColMajor(d_tempData, outT_f42_0_f1);
  y_conv2dDirectOptimizedColMajor(outT_f42_0_f1, d_tempData);
  ab_conv2dDirectOptimizedColMajo(d_tempData, outT_f42_0_f1);
  c_fromBlockedLayoutTransform(&outT_f42_0_f1[0], &d_tempData[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  cat(outT_f46[0].f1, d_tempData, outT_f10_0_f1);
  b_dlarray_reshape(outT_f10_0_f1, c_tempData);
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&outT_f46[0].f1[0], &c_tempData[0], 22736U * sizeof(float));
  memcpy(&outT_f46[1].f1[0], &c_tempData[22736], 22736U * sizeof(float));
  c_toBlockedLayoutTransform(&outT_f46[1].f1[0], &d_tempData[0]);
  bb_conv2dDirectOptimizedColMajo(d_tempData, outT_f42_0_f1);
  cb_conv2dDirectOptimizedColMajo(outT_f42_0_f1, d_tempData);
  db_conv2dDirectOptimizedColMajo(d_tempData, outT_f42_0_f1);
  c_fromBlockedLayoutTransform(&outT_f42_0_f1[0], &d_tempData[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  cat(outT_f46[0].f1, d_tempData, outT_f10_0_f1);
  b_dlarray_reshape(outT_f10_0_f1, c_tempData);
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&outT_f46[0].f1[0], &c_tempData[0], 22736U * sizeof(float));
  memcpy(&outT_f46[1].f1[0], &c_tempData[22736], 22736U * sizeof(float));
  c_toBlockedLayoutTransform(&outT_f46[1].f1[0], &d_tempData[0]);
  eb_conv2dDirectOptimizedColMajo(d_tempData, outT_f42_0_f1);
  fb_conv2dDirectOptimizedColMajo(outT_f42_0_f1, d_tempData);
  gb_conv2dDirectOptimizedColMajo(d_tempData, outT_f42_0_f1);
  c_fromBlockedLayoutTransform(&outT_f42_0_f1[0], &d_tempData[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  cat(outT_f46[0].f1, d_tempData, outT_f10_0_f1);
  b_dlarray_reshape(outT_f10_0_f1, c_tempData);
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&outT_f46[0].f1[0], &c_tempData[0], 22736U * sizeof(float));
  memcpy(&outT_f46[1].f1[0], &c_tempData[22736], 22736U * sizeof(float));
  c_toBlockedLayoutTransform(&outT_f46[1].f1[0], &d_tempData[0]);
  hb_conv2dDirectOptimizedColMajo(d_tempData, outT_f42_0_f1);
  ib_conv2dDirectOptimizedColMajo(outT_f42_0_f1, d_tempData);
  jb_conv2dDirectOptimizedColMajo(d_tempData, outT_f42_0_f1);
  c_fromBlockedLayoutTransform(&outT_f42_0_f1[0], &d_tempData[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  cat(outT_f46[0].f1, d_tempData, outT_f10_0_f1);
  b_dlarray_reshape(outT_f10_0_f1, c_tempData);
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&outT_f46[0].f1[0], &c_tempData[0], 22736U * sizeof(float));
  memcpy(&outT_f46[1].f1[0], &c_tempData[22736], 22736U * sizeof(float));
  c_toBlockedLayoutTransform(&outT_f46[1].f1[0], &d_tempData[0]);
  kb_conv2dDirectOptimizedColMajo(d_tempData, outT_f42_0_f1);
  lb_conv2dDirectOptimizedColMajo(outT_f42_0_f1, d_tempData);
  mb_conv2dDirectOptimizedColMajo(d_tempData, outT_f42_0_f1);
  c_fromBlockedLayoutTransform(&outT_f42_0_f1[0], &d_tempData[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  cat(outT_f46[0].f1, d_tempData, outT_f10_0_f1);
  b_dlarray_reshape(outT_f10_0_f1, c_tempData);
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&outT_f46[0].f1[0], &c_tempData[0], 22736U * sizeof(float));
  memcpy(&outT_f46[1].f1[0], &c_tempData[22736], 22736U * sizeof(float));
  c_toBlockedLayoutTransform(&outT_f46[1].f1[0], &d_tempData[0]);
  nb_conv2dDirectOptimizedColMajo(d_tempData, outT_f42_0_f1);
  ob_conv2dDirectOptimizedColMajo(outT_f42_0_f1, d_tempData);
  pb_conv2dDirectOptimizedColMajo(d_tempData, outT_f42_0_f1);
  c_fromBlockedLayoutTransform(&outT_f42_0_f1[0], &d_tempData[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  cat(outT_f46[0].f1, d_tempData, outT_f10_0_f1);
  b_dlarray_reshape(outT_f10_0_f1, c_tempData);
  d_toBlockedLayoutTransform(&c_tempData[0], &outT_f102_0_f1[0]);
  qb_conv2dDirectOptimizedColMajo(outT_f102_0_f1, outT_f103_0_f1);
  rb_conv2dDirectOptimizedColMajo(outT_f103_0_f1, outT_f104_0_f1);
  sb_conv2dDirectOptimizedColMajo(outT_f102_0_f1, outT_f10_0_f1);
  tb_conv2dDirectOptimizedColMajo(outT_f10_0_f1, outT_f103_0_f1);
  ub_conv2dDirectOptimizedColMajo(outT_f103_0_f1, outT_f107_0_f1);
  b_cat(outT_f104_0_f1, outT_f107_0_f1, d_tempData);
  d_fromBlockedLayoutTransform(&d_tempData[0], &objY_Data[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  c_dlarray_reshape(objY_Data, d_tempData);
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&outT_f111[0].f1[0], &d_tempData[0], 11368U * sizeof(float));
  memcpy(&outT_f111[1].f1[0], &d_tempData[11368], 11368U * sizeof(float));
  e_toBlockedLayoutTransform(&outT_f111[1].f1[0], &outT_f103_0_f1[0]);
  vb_conv2dDirectOptimizedColMajo(outT_f103_0_f1, outT_f107_0_f1);
  wb_conv2dDirectOptimizedColMajo(outT_f107_0_f1, outT_f103_0_f1);
  xb_conv2dDirectOptimizedColMajo(outT_f103_0_f1, outT_f107_0_f1);
  e_fromBlockedLayoutTransform(&outT_f107_0_f1[0], &outT_f103_0_f1[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  b_cat(outT_f111[0].f1, outT_f103_0_f1, outT_f39_0_f1);
  c_dlarray_reshape(outT_f39_0_f1, d_tempData);
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&outT_f111[0].f1[0], &d_tempData[0], 11368U * sizeof(float));
  memcpy(&outT_f111[1].f1[0], &d_tempData[11368], 11368U * sizeof(float));
  e_toBlockedLayoutTransform(&outT_f111[1].f1[0], &outT_f103_0_f1[0]);
  yb_conv2dDirectOptimizedColMajo(outT_f103_0_f1, outT_f107_0_f1);
  ac_conv2dDirectOptimizedColMajo(outT_f107_0_f1, outT_f103_0_f1);
  bc_conv2dDirectOptimizedColMajo(outT_f103_0_f1, outT_f107_0_f1);
  e_fromBlockedLayoutTransform(&outT_f107_0_f1[0], &outT_f103_0_f1[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  b_cat(outT_f111[0].f1, outT_f103_0_f1, outT_f39_0_f1);
  c_dlarray_reshape(outT_f39_0_f1, d_tempData);
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&outT_f111[0].f1[0], &d_tempData[0], 11368U * sizeof(float));
  memcpy(&outT_f111[1].f1[0], &d_tempData[11368], 11368U * sizeof(float));
  e_toBlockedLayoutTransform(&outT_f111[1].f1[0], &outT_f103_0_f1[0]);
  cc_conv2dDirectOptimizedColMajo(outT_f103_0_f1, outT_f107_0_f1);
  dc_conv2dDirectOptimizedColMajo(outT_f107_0_f1, outT_f103_0_f1);
  ec_conv2dDirectOptimizedColMajo(outT_f103_0_f1, outT_f107_0_f1);
  e_fromBlockedLayoutTransform(&outT_f107_0_f1[0], &outT_f103_0_f1[0]);
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  b_cat(outT_f111[0].f1, outT_f103_0_f1, outT_f39_0_f1);
  c_dlarray_reshape(outT_f39_0_f1, d_tempData);
  f_toBlockedLayoutTransform(&d_tempData[0], &outT_f42_0_f1[0]);
  fc_conv2dDirectOptimizedColMajo(outT_f42_0_f1, X);
  b_pool(X, b_Z);
  f_fromBlockedLayoutTransform(&b_Z[0], &b_X[0]);
  c_matrixMultiply163683382385183(1000, 1024, 1, 64, 64, 64, &t0_Weights[0],
                                  &b_X[0], &outputs_0_f1[0]);
  for (i = 0; i <= 996; i += 4) {
    float32x4_t r;
    r = vld1q_f32(&outputs_0_f1[i]);
    vst1q_f32(&outputs_0_f1[i], vaddq_f32(r, vld1q_f32(&fv[i])));
  }
}

/*
 * File trailer for callPredict.c
 *
 * [EOF]
 */
