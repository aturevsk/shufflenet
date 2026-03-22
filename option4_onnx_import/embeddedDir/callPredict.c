/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: callPredict.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:35:57
 */

/* Include Files */
#include "callPredict.h"
#include "Shape_To_SliceLayer1000.h"
#include "Shape_To_SliceLayer1004.h"
#include "Shape_To_SliceLayer1012.h"
#include "cat.h"
#include "conv2dDirectOptimizedColMajor.h"
#include "mean.h"
#include "permute.h"
#include "pool.h"
#include "predict_shufflenet_onnx_rtwutil.h"
#include "omp.h"
#include <arm_neon.h>
#include <string.h>

/* Type Definitions */
#ifndef typedef_cell_wrap_11
#define typedef_cell_wrap_11
typedef struct {
  float f1[45472];
} cell_wrap_11;
#endif /* typedef_cell_wrap_11 */

#ifndef typedef_cell_wrap_14
#define typedef_cell_wrap_14
typedef struct {
  float f1[22736];
} cell_wrap_14;
#endif /* typedef_cell_wrap_14 */

#ifndef typedef_cell_wrap_16
#define typedef_cell_wrap_16
typedef struct {
  float f1[11368];
} cell_wrap_16;
#endif /* typedef_cell_wrap_16 */

/* Function Declarations */
static void b_fromBlockedLayoutTransform(const float *inputTensor,
                                         float *outputTensor);

static void b_toBlockedLayoutTransform(const float *inputTensor,
                                       float *outputTensor);

static void c_fromBlockedLayoutTransform(const float *inputTensor,
                                         float *outputTensor);

static void c_matrixMultiply509232298252315(int M, int K, int N, int blockSizeM,
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

static void macroKernel5092322982523156551(int M, int K, int N, const float *A,
                                           int LDA, const float *B, int LDB,
                                           float *C, int LDC);

static void microKernel16179624166335670025(int K, const float *A, int LDA,
                                            const float *B, int LDB, float *C,
                                            int LDC);

static void microKernel4474929121922715983(int K, const float *A, int LDA,
                                           const float *B, int LDB, float *C,
                                           int LDC);

static void microKernel564510748923505135(int K, const float *A, int LDA,
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
static void c_matrixMultiply509232298252315(int M, int K, int N, int blockSizeM,
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
        macroKernel5092322982523156551(b_i, K2, N2, &A[i + M * k], M, ptrB, K,
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
  int blockIdx;
  int fusedBlockIdx;
  int fusedImageIdx;
  int outputTensorBaseIdx;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        fusedBlockIdx, blockIdx, outputTensorBaseIdx)

  for (fusedImageIdx = 0; fusedImageIdx < 12544; fusedImageIdx++) {
    fusedBlockIdx = fusedImageIdx % 12544;
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
static void macroKernel5092322982523156551(int M, int K, int N, const float *A,
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
      microKernel4474929121922715983(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
                                     LDC);
      idxA += 28;
      idxC += 28;
      i += 28;
    }
    while (i <= M - 4) {
      microKernel564510748923505135(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
                                    LDC);
      idxA += 4;
      idxC += 4;
      i += 4;
    }
    while (i <= M - 1) {
      microKernel16179624166335670025(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
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
static void microKernel16179624166335670025(int K, const float *A, int LDA,
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
 * Arguments    : int K
 *                const float *A
 *                int LDA
 *                const float *B
 *                int LDB
 *                float *C
 *                int LDC
 * Return Type  : void
 */
static void microKernel4474929121922715983(int K, const float *A, int LDA,
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
static void microKernel564510748923505135(int K, const float *A, int LDA,
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
  static cell_wrap_11 outT_f12[2];
  static cell_wrap_14 outT_f42[2];
  static cell_wrap_16 outT_f100[2];
  static float t0_Weights[1024000];
  static float X[301056];
  static float outT_f7_0_f1[188160];
  static float e_tempData[90944];
  static float outT_f34_0_f1[90944];
  static float tempData[90944];
  static float Z[75264];
  static float outT_f123_0_f1[50176];
  static float outT_f124_0_f1[50176];
  static float outT_f15_0_f1[47040];
  static float outT_f5_0_f1[47040];
  static float outT_f9_0_f1[47040];
  static float b_tempData[45472];
  static float outT_f10_0_f1[45472];
  static float c_tempData[22736];
  static float outT_f35_0_f1[22736];
  static float outT_f36_0_f1[22736];
  static float outT_f4_0_f1[18816];
  static float fv[1000];
  static bool bufferInitialized;
  float outT_f93_0_f1[11368];
  float outT_f94_0_f1[11368];
  float outT_f97_0_f1[11368];
  float d_tempData[1024];
  int i;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&t0_Weights[0],
                              "./embeddedDir//largeDnnConstants_5476399.bin",
                              1024000);
    readDnnConstants_real32_T(
        &fv[0], "./embeddedDir//largeDnnConstants_5476403.bin", 1000);
  }
  bufferInitialized = true;
  conv2dDirectOptimizedColMajor(inputsT_0_f1, X);
  pool(X, Z);
  b_conv2dDirectOptimizedColMajor(Z, outT_f4_0_f1);
  c_conv2dDirectOptimizedColMajor(outT_f4_0_f1, outT_f5_0_f1);
  fromBlockedLayoutTransform(&outT_f5_0_f1[0], &b_tempData[0]);
  d_conv2dDirectOptimizedColMajor(Z, outT_f7_0_f1);
  e_conv2dDirectOptimizedColMajor(outT_f7_0_f1, outT_f5_0_f1);
  f_conv2dDirectOptimizedColMajor(outT_f5_0_f1, outT_f9_0_f1);
  fromBlockedLayoutTransform(&outT_f9_0_f1[0], &outT_f10_0_f1[0]);
  memcpy(&tempData[0], &b_tempData[0], 45472U * sizeof(float));
  memcpy(&tempData[45472], &outT_f10_0_f1[0], 45472U * sizeof(float));
  Shape_To_SliceLayer1000_predict(tempData, outT_f12[0].f1, outT_f12[1].f1);
  toBlockedLayoutTransform(&outT_f12[0].f1[0], &outT_f5_0_f1[0]);
  g_conv2dDirectOptimizedColMajor(outT_f5_0_f1, outT_f9_0_f1);
  h_conv2dDirectOptimizedColMajor(outT_f9_0_f1, outT_f15_0_f1);
  i_conv2dDirectOptimizedColMajor(outT_f15_0_f1, outT_f5_0_f1);
  fromBlockedLayoutTransform(&outT_f5_0_f1[0], &b_tempData[0]);
  memcpy(&tempData[0], &outT_f12[1].f1[0], 45472U * sizeof(float));
  memcpy(&tempData[45472], &b_tempData[0], 45472U * sizeof(float));
  Shape_To_SliceLayer1000_predict(tempData, outT_f12[0].f1, outT_f12[1].f1);
  toBlockedLayoutTransform(&outT_f12[0].f1[0], &outT_f5_0_f1[0]);
  j_conv2dDirectOptimizedColMajor(outT_f5_0_f1, outT_f9_0_f1);
  k_conv2dDirectOptimizedColMajor(outT_f9_0_f1, outT_f15_0_f1);
  l_conv2dDirectOptimizedColMajor(outT_f15_0_f1, outT_f5_0_f1);
  fromBlockedLayoutTransform(&outT_f5_0_f1[0], &b_tempData[0]);
  memcpy(&tempData[0], &outT_f12[1].f1[0], 45472U * sizeof(float));
  memcpy(&tempData[45472], &b_tempData[0], 45472U * sizeof(float));
  Shape_To_SliceLayer1000_predict(tempData, outT_f12[0].f1, outT_f12[1].f1);
  toBlockedLayoutTransform(&outT_f12[0].f1[0], &outT_f5_0_f1[0]);
  m_conv2dDirectOptimizedColMajor(outT_f5_0_f1, outT_f9_0_f1);
  n_conv2dDirectOptimizedColMajor(outT_f9_0_f1, outT_f15_0_f1);
  o_conv2dDirectOptimizedColMajor(outT_f15_0_f1, outT_f5_0_f1);
  fromBlockedLayoutTransform(&outT_f5_0_f1[0], &b_tempData[0]);
  memcpy(&tempData[0], &outT_f12[1].f1[0], 45472U * sizeof(float));
  memcpy(&tempData[45472], &b_tempData[0], 45472U * sizeof(float));
  /*  Returns reverse-ONNX ordering numeric array */
  /*    Copyright 2024 The MathWorks, Inc.   */
  /*  Permute into reverse ONNX ordering */
  /*  Execute the operators: */
  /*  Shape: */
  /*  Gather: */
  /*  Shape: */
  /*  Gather: */
  /*  Shape: */
  /*  Gather: */
  /*  Shape: */
  /*  Gather: */
  /*  Div: */
  /*  Cast: */
  /*  Unsqueeze: */
  /*  Concat: */
  /*  Reshape: */
  /*  Transpose: */
  /*  Unsqueeze: */
  /*  Concat: */
  /*  Reshape: */
  /*  Set graph output arguments */
  /*  Returns DLT ordering */
  /*    Copyright 2024 The MathWorks, Inc. */
  /*  ndims >= 2 */
  /*  Use the inverse of the user's permutation. This is not just the */
  /*  flip of the permutation vector. */
  permute(tempData, outT_f34_0_f1);
  b_permute(outT_f34_0_f1, tempData);
  permute(tempData, e_tempData);
  b_toBlockedLayoutTransform(&e_tempData[0], &outT_f34_0_f1[0]);
  p_conv2dDirectOptimizedColMajor(outT_f34_0_f1, outT_f35_0_f1);
  q_conv2dDirectOptimizedColMajor(outT_f35_0_f1, outT_f36_0_f1);
  r_conv2dDirectOptimizedColMajor(outT_f34_0_f1, tempData);
  s_conv2dDirectOptimizedColMajor(tempData, outT_f35_0_f1);
  t_conv2dDirectOptimizedColMajor(outT_f35_0_f1, c_tempData);
  cat(outT_f36_0_f1, c_tempData, b_tempData);
  b_fromBlockedLayoutTransform(&b_tempData[0], &outT_f10_0_f1[0]);
  Shape_To_SliceLayer1004_predict(outT_f10_0_f1, outT_f42[0].f1,
                                  outT_f42[1].f1);
  c_toBlockedLayoutTransform(&outT_f42[0].f1[0], &outT_f35_0_f1[0]);
  u_conv2dDirectOptimizedColMajor(outT_f35_0_f1, c_tempData);
  v_conv2dDirectOptimizedColMajor(c_tempData, outT_f35_0_f1);
  w_conv2dDirectOptimizedColMajor(outT_f35_0_f1, c_tempData);
  c_fromBlockedLayoutTransform(&c_tempData[0], &outT_f35_0_f1[0]);
  cat(outT_f42[1].f1, outT_f35_0_f1, outT_f10_0_f1);
  Shape_To_SliceLayer1004_predict(outT_f10_0_f1, outT_f42[0].f1,
                                  outT_f42[1].f1);
  c_toBlockedLayoutTransform(&outT_f42[0].f1[0], &outT_f35_0_f1[0]);
  x_conv2dDirectOptimizedColMajor(outT_f35_0_f1, c_tempData);
  y_conv2dDirectOptimizedColMajor(c_tempData, outT_f35_0_f1);
  ab_conv2dDirectOptimizedColMajo(outT_f35_0_f1, c_tempData);
  c_fromBlockedLayoutTransform(&c_tempData[0], &outT_f35_0_f1[0]);
  cat(outT_f42[1].f1, outT_f35_0_f1, outT_f10_0_f1);
  Shape_To_SliceLayer1004_predict(outT_f10_0_f1, outT_f42[0].f1,
                                  outT_f42[1].f1);
  c_toBlockedLayoutTransform(&outT_f42[0].f1[0], &outT_f35_0_f1[0]);
  bb_conv2dDirectOptimizedColMajo(outT_f35_0_f1, c_tempData);
  cb_conv2dDirectOptimizedColMajo(c_tempData, outT_f35_0_f1);
  db_conv2dDirectOptimizedColMajo(outT_f35_0_f1, c_tempData);
  c_fromBlockedLayoutTransform(&c_tempData[0], &outT_f35_0_f1[0]);
  cat(outT_f42[1].f1, outT_f35_0_f1, outT_f10_0_f1);
  Shape_To_SliceLayer1004_predict(outT_f10_0_f1, outT_f42[0].f1,
                                  outT_f42[1].f1);
  c_toBlockedLayoutTransform(&outT_f42[0].f1[0], &outT_f35_0_f1[0]);
  eb_conv2dDirectOptimizedColMajo(outT_f35_0_f1, c_tempData);
  fb_conv2dDirectOptimizedColMajo(c_tempData, outT_f35_0_f1);
  gb_conv2dDirectOptimizedColMajo(outT_f35_0_f1, c_tempData);
  c_fromBlockedLayoutTransform(&c_tempData[0], &outT_f35_0_f1[0]);
  cat(outT_f42[1].f1, outT_f35_0_f1, outT_f10_0_f1);
  Shape_To_SliceLayer1004_predict(outT_f10_0_f1, outT_f42[0].f1,
                                  outT_f42[1].f1);
  c_toBlockedLayoutTransform(&outT_f42[0].f1[0], &outT_f35_0_f1[0]);
  hb_conv2dDirectOptimizedColMajo(outT_f35_0_f1, c_tempData);
  ib_conv2dDirectOptimizedColMajo(c_tempData, outT_f35_0_f1);
  jb_conv2dDirectOptimizedColMajo(outT_f35_0_f1, c_tempData);
  c_fromBlockedLayoutTransform(&c_tempData[0], &outT_f35_0_f1[0]);
  cat(outT_f42[1].f1, outT_f35_0_f1, outT_f10_0_f1);
  Shape_To_SliceLayer1004_predict(outT_f10_0_f1, outT_f42[0].f1,
                                  outT_f42[1].f1);
  c_toBlockedLayoutTransform(&outT_f42[0].f1[0], &outT_f35_0_f1[0]);
  kb_conv2dDirectOptimizedColMajo(outT_f35_0_f1, c_tempData);
  lb_conv2dDirectOptimizedColMajo(c_tempData, outT_f35_0_f1);
  mb_conv2dDirectOptimizedColMajo(outT_f35_0_f1, c_tempData);
  c_fromBlockedLayoutTransform(&c_tempData[0], &outT_f35_0_f1[0]);
  cat(outT_f42[1].f1, outT_f35_0_f1, outT_f10_0_f1);
  Shape_To_SliceLayer1004_predict(outT_f10_0_f1, outT_f42[0].f1,
                                  outT_f42[1].f1);
  c_toBlockedLayoutTransform(&outT_f42[0].f1[0], &outT_f35_0_f1[0]);
  nb_conv2dDirectOptimizedColMajo(outT_f35_0_f1, c_tempData);
  ob_conv2dDirectOptimizedColMajo(c_tempData, outT_f35_0_f1);
  pb_conv2dDirectOptimizedColMajo(outT_f35_0_f1, c_tempData);
  c_fromBlockedLayoutTransform(&c_tempData[0], &outT_f35_0_f1[0]);
  /*  Returns reverse-ONNX ordering numeric array */
  /*    Copyright 2024 The MathWorks, Inc.   */
  /*  Permute into reverse ONNX ordering */
  /*  Execute the operators: */
  /*  Shape: */
  /*  Gather: */
  /*  Shape: */
  /*  Gather: */
  /*  Shape: */
  /*  Gather: */
  /*  Shape: */
  /*  Gather: */
  /*  Div: */
  /*  Cast: */
  /*  Unsqueeze: */
  /*  Concat: */
  /*  Reshape: */
  /*  Transpose: */
  /*  Unsqueeze: */
  /*  Concat: */
  /*  Reshape: */
  /*  Set graph output arguments */
  /*  Returns DLT ordering */
  /*    Copyright 2024 The MathWorks, Inc. */
  /*  ndims >= 2 */
  /*  Use the inverse of the user's permutation. This is not just the */
  /*  flip of the permutation vector. */
  cat(outT_f42[1].f1, outT_f35_0_f1, outT_f10_0_f1);
  d_permute(outT_f10_0_f1, b_tempData);
  e_permute(b_tempData, outT_f10_0_f1);
  d_permute(outT_f10_0_f1, b_tempData);
  d_toBlockedLayoutTransform(&b_tempData[0], &outT_f10_0_f1[0]);
  qb_conv2dDirectOptimizedColMajo(outT_f10_0_f1, outT_f93_0_f1);
  rb_conv2dDirectOptimizedColMajo(outT_f93_0_f1, outT_f94_0_f1);
  sb_conv2dDirectOptimizedColMajo(outT_f10_0_f1, b_tempData);
  tb_conv2dDirectOptimizedColMajo(b_tempData, outT_f93_0_f1);
  ub_conv2dDirectOptimizedColMajo(outT_f93_0_f1, outT_f97_0_f1);
  memcpy(&outT_f35_0_f1[0], &outT_f94_0_f1[0], 11368U * sizeof(float));
  memcpy(&outT_f35_0_f1[11368], &outT_f97_0_f1[0], 11368U * sizeof(float));
  d_fromBlockedLayoutTransform(&outT_f35_0_f1[0], &c_tempData[0]);
  Shape_To_SliceLayer1012_predict(c_tempData, outT_f100[0].f1, outT_f100[1].f1);
  e_toBlockedLayoutTransform(&outT_f100[0].f1[0], &outT_f93_0_f1[0]);
  vb_conv2dDirectOptimizedColMajo(outT_f93_0_f1, outT_f97_0_f1);
  wb_conv2dDirectOptimizedColMajo(outT_f97_0_f1, outT_f93_0_f1);
  xb_conv2dDirectOptimizedColMajo(outT_f93_0_f1, outT_f97_0_f1);
  e_fromBlockedLayoutTransform(&outT_f97_0_f1[0], &outT_f93_0_f1[0]);
  memcpy(&outT_f35_0_f1[0], &outT_f100[1].f1[0], 11368U * sizeof(float));
  memcpy(&outT_f35_0_f1[11368], &outT_f93_0_f1[0], 11368U * sizeof(float));
  Shape_To_SliceLayer1012_predict(outT_f35_0_f1, outT_f100[0].f1,
                                  outT_f100[1].f1);
  e_toBlockedLayoutTransform(&outT_f100[0].f1[0], &outT_f93_0_f1[0]);
  yb_conv2dDirectOptimizedColMajo(outT_f93_0_f1, outT_f97_0_f1);
  ac_conv2dDirectOptimizedColMajo(outT_f97_0_f1, outT_f93_0_f1);
  bc_conv2dDirectOptimizedColMajo(outT_f93_0_f1, outT_f97_0_f1);
  e_fromBlockedLayoutTransform(&outT_f97_0_f1[0], &outT_f93_0_f1[0]);
  memcpy(&outT_f35_0_f1[0], &outT_f100[1].f1[0], 11368U * sizeof(float));
  memcpy(&outT_f35_0_f1[11368], &outT_f93_0_f1[0], 11368U * sizeof(float));
  Shape_To_SliceLayer1012_predict(outT_f35_0_f1, outT_f100[0].f1,
                                  outT_f100[1].f1);
  e_toBlockedLayoutTransform(&outT_f100[0].f1[0], &outT_f93_0_f1[0]);
  cc_conv2dDirectOptimizedColMajo(outT_f93_0_f1, outT_f97_0_f1);
  dc_conv2dDirectOptimizedColMajo(outT_f97_0_f1, outT_f93_0_f1);
  ec_conv2dDirectOptimizedColMajo(outT_f93_0_f1, outT_f97_0_f1);
  e_fromBlockedLayoutTransform(&outT_f97_0_f1[0], &outT_f93_0_f1[0]);
  memcpy(&outT_f35_0_f1[0], &outT_f100[1].f1[0], 11368U * sizeof(float));
  memcpy(&outT_f35_0_f1[11368], &outT_f93_0_f1[0], 11368U * sizeof(float));
  /*  Returns reverse-ONNX ordering numeric array */
  /*    Copyright 2024 The MathWorks, Inc.   */
  /*  Permute into reverse ONNX ordering */
  /*  Execute the operators: */
  /*  Shape: */
  /*  Gather: */
  /*  Shape: */
  /*  Gather: */
  /*  Shape: */
  /*  Gather: */
  /*  Shape: */
  /*  Gather: */
  /*  Div: */
  /*  Cast: */
  /*  Unsqueeze: */
  /*  Concat: */
  /*  Reshape: */
  /*  Transpose: */
  /*  Unsqueeze: */
  /*  Concat: */
  /*  Reshape: */
  /*  Set graph output arguments */
  /*  Returns DLT ordering */
  /*    Copyright 2024 The MathWorks, Inc. */
  /*  ndims >= 2 */
  /*  Use the inverse of the user's permutation. This is not just the */
  /*  flip of the permutation vector. */
  g_permute(outT_f35_0_f1, outT_f36_0_f1);
  h_permute(outT_f36_0_f1, outT_f35_0_f1);
  g_permute(outT_f35_0_f1, c_tempData);
  f_toBlockedLayoutTransform(&c_tempData[0], &outT_f35_0_f1[0]);
  fc_conv2dDirectOptimizedColMajo(outT_f35_0_f1, outT_f123_0_f1);
  f_fromBlockedLayoutTransform(&outT_f123_0_f1[0], &outT_f124_0_f1[0]);
  /*  Returns reverse-ONNX ordering numeric array */
  /*    Copyright 2024 The MathWorks, Inc.   */
  /*  Permute into reverse ONNX ordering */
  /*  Execute the operators: */
  /*  ReduceMean: */
  /*  Implements the ONNX Squeeze operator */
  /*  Copyright 2024 The MathWorks, Inc. */
  /*  Find the new ONNX shape */
  /*  Append 1's to shape if numDims<2 */
  j_permute(outT_f124_0_f1, outT_f123_0_f1);
  mean(outT_f123_0_f1, d_tempData);
  /*  Set graph output arguments */
  /*  Returns DLT ordering */
  /*    Copyright 2024 The MathWorks, Inc. */
  /*  ndims >= 2 */
  /*  Use the inverse of the user's permutation. This is not just the */
  /*  flip of the permutation vector. */
  c_matrixMultiply509232298252315(1000, 1024, 1, 64, 64, 64, &t0_Weights[0],
                                  &d_tempData[0], &outputs_0_f1[0]);
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
