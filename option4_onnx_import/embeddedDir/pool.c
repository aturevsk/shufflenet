/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: pool.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:35:57
 */

/* Include Files */
#include "pool.h"
#include "omp.h"
#include <arm_neon.h>

/* Function Declarations */
static void
c_maxPoolingKernel7231203818156(const float *inputBufferPtr,
                                float *outputBufferPtr, int poolOutputWidthIdx,
                                int c_startIdxWithPaddingOffsetInpu);

static void maxPooling7231203818156735551(const float *inputTensor,
                                          float *outputTensor);

/* Function Definitions */
/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                int poolOutputWidthIdx
 *                int c_startIdxWithPaddingOffsetInpu
 * Return Type  : void
 */
static void c_maxPoolingKernel7231203818156(const float *inputBufferPtr,
                                            float *outputBufferPtr,
                                            int poolOutputWidthIdx,
                                            int c_startIdxWithPaddingOffsetInpu)
{
  float32x4_t opReg_opHeightIdx_0;
  float32x4_t opReg_opHeightIdx_1;
  float32x4_t opReg_opHeightIdx_2;
  float32x4_t opReg_opHeightIdx_3;
  float32x4_t opReg_opHeightIdx_4;
  float32x4_t opReg_opHeightIdx_5;
  float32x4_t opReg_opHeightIdx_6;
  float32x4_t paddingValue;
  int c_idxToStrideInputBufferAlongHe;
  int outputHeightBlockIdx;
  int outputHeightIdx;
  int poolWidthIdx;
  paddingValue = vdupq_n_f32(-3.402823466E+38F);
  c_idxToStrideInputBufferAlongHe = c_startIdxWithPaddingOffsetInpu;
  outputHeightIdx = 0;
  for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 8;
       outputHeightBlockIdx++) {
    int b_topPaddingBound_tmp;
    int c_idxToStrideInputBufferAlongWi;
    int c_topPaddingBound_tmp;
    int d_topPaddingBound_tmp;
    int e_topPaddingBound_tmp;
    int f_topPaddingBound_tmp;
    int g_topPaddingBound_tmp;
    int topPaddingBound_tmp;
    bool areOutputRegistersInitialized;
    areOutputRegistersInitialized = false;
    c_idxToStrideInputBufferAlongWi = c_idxToStrideInputBufferAlongHe;
    topPaddingBound_tmp = outputHeightIdx << 1;
    b_topPaddingBound_tmp = (outputHeightIdx + 1) << 1;
    c_topPaddingBound_tmp = (outputHeightIdx + 2) << 1;
    d_topPaddingBound_tmp = (outputHeightIdx + 3) << 1;
    e_topPaddingBound_tmp = (outputHeightIdx + 4) << 1;
    f_topPaddingBound_tmp = (outputHeightIdx + 5) << 1;
    g_topPaddingBound_tmp = (outputHeightIdx + 6) << 1;
    for (poolWidthIdx = 0; poolWidthIdx < 3; poolWidthIdx++) {
      float32x4_t ipReg_opHeightIdx_0;
      float32x4_t ipReg_opHeightIdx_1;
      float32x4_t ipReg_opHeightIdx_2;
      float32x4_t ipReg_opHeightIdx_3;
      float32x4_t ipReg_opHeightIdx_4;
      float32x4_t ipReg_opHeightIdx_5;
      float32x4_t ipReg_opHeightIdx_6;
      int leftPaddingBound;
      bool b;
      leftPaddingBound = ((poolOutputWidthIdx << 1) + poolWidthIdx) - 1;
      b = ((leftPaddingBound >= 0) && (leftPaddingBound < 112));
      if (b && (topPaddingBound_tmp - 1 >= 0) &&
          (topPaddingBound_tmp - 1 < 112)) {
        ipReg_opHeightIdx_0 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi]);
      } else {
        ipReg_opHeightIdx_0 = paddingValue;
      }
      if (b && (b_topPaddingBound_tmp - 1 >= 0) &&
          (b_topPaddingBound_tmp - 1 < 112)) {
        ipReg_opHeightIdx_1 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 8]);
      } else {
        ipReg_opHeightIdx_1 = paddingValue;
      }
      if (b && (c_topPaddingBound_tmp - 1 >= 0) &&
          (c_topPaddingBound_tmp - 1 < 112)) {
        ipReg_opHeightIdx_2 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 16]);
      } else {
        ipReg_opHeightIdx_2 = paddingValue;
      }
      if (b && (d_topPaddingBound_tmp - 1 >= 0) &&
          (d_topPaddingBound_tmp - 1 < 112)) {
        ipReg_opHeightIdx_3 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 24]);
      } else {
        ipReg_opHeightIdx_3 = paddingValue;
      }
      if (b && (e_topPaddingBound_tmp - 1 >= 0) &&
          (e_topPaddingBound_tmp - 1 < 112)) {
        ipReg_opHeightIdx_4 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 32]);
      } else {
        ipReg_opHeightIdx_4 = paddingValue;
      }
      if (b && (f_topPaddingBound_tmp - 1 >= 0) &&
          (f_topPaddingBound_tmp - 1 < 112)) {
        ipReg_opHeightIdx_5 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 40]);
      } else {
        ipReg_opHeightIdx_5 = paddingValue;
      }
      if (b && (g_topPaddingBound_tmp - 1 >= 0) &&
          (g_topPaddingBound_tmp - 1 < 112)) {
        ipReg_opHeightIdx_6 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 48]);
      } else {
        ipReg_opHeightIdx_6 = paddingValue;
      }
      if (!areOutputRegistersInitialized) {
        opReg_opHeightIdx_0 = ipReg_opHeightIdx_0;
        opReg_opHeightIdx_1 = ipReg_opHeightIdx_1;
        opReg_opHeightIdx_2 = ipReg_opHeightIdx_2;
        opReg_opHeightIdx_3 = ipReg_opHeightIdx_3;
        opReg_opHeightIdx_4 = ipReg_opHeightIdx_4;
        opReg_opHeightIdx_5 = ipReg_opHeightIdx_5;
        opReg_opHeightIdx_6 = ipReg_opHeightIdx_6;
        areOutputRegistersInitialized = true;
      } else {
        opReg_opHeightIdx_0 =
            vmaxq_f32(ipReg_opHeightIdx_0, opReg_opHeightIdx_0);
        opReg_opHeightIdx_1 =
            vmaxq_f32(ipReg_opHeightIdx_1, opReg_opHeightIdx_1);
        opReg_opHeightIdx_2 =
            vmaxq_f32(ipReg_opHeightIdx_2, opReg_opHeightIdx_2);
        opReg_opHeightIdx_3 =
            vmaxq_f32(ipReg_opHeightIdx_3, opReg_opHeightIdx_3);
        opReg_opHeightIdx_4 =
            vmaxq_f32(ipReg_opHeightIdx_4, opReg_opHeightIdx_4);
        opReg_opHeightIdx_5 =
            vmaxq_f32(ipReg_opHeightIdx_5, opReg_opHeightIdx_5);
        opReg_opHeightIdx_6 =
            vmaxq_f32(ipReg_opHeightIdx_6, opReg_opHeightIdx_6);
      }
      if (b && (topPaddingBound_tmp >= 0) && (topPaddingBound_tmp < 112)) {
        ipReg_opHeightIdx_0 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 4]);
      } else {
        ipReg_opHeightIdx_0 = paddingValue;
      }
      if (b && (b_topPaddingBound_tmp >= 0) && (b_topPaddingBound_tmp < 112)) {
        ipReg_opHeightIdx_1 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 12]);
      } else {
        ipReg_opHeightIdx_1 = paddingValue;
      }
      if (b && (c_topPaddingBound_tmp >= 0) && (c_topPaddingBound_tmp < 112)) {
        ipReg_opHeightIdx_2 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 20]);
      } else {
        ipReg_opHeightIdx_2 = paddingValue;
      }
      if (b && (d_topPaddingBound_tmp >= 0) && (d_topPaddingBound_tmp < 112)) {
        ipReg_opHeightIdx_3 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 28]);
      } else {
        ipReg_opHeightIdx_3 = paddingValue;
      }
      if (b && (e_topPaddingBound_tmp >= 0) && (e_topPaddingBound_tmp < 112)) {
        ipReg_opHeightIdx_4 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 36]);
      } else {
        ipReg_opHeightIdx_4 = paddingValue;
      }
      if (b && (f_topPaddingBound_tmp >= 0) && (f_topPaddingBound_tmp < 112)) {
        ipReg_opHeightIdx_5 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 44]);
      } else {
        ipReg_opHeightIdx_5 = paddingValue;
      }
      if (b && (g_topPaddingBound_tmp >= 0) && (g_topPaddingBound_tmp < 112)) {
        ipReg_opHeightIdx_6 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 52]);
      } else {
        ipReg_opHeightIdx_6 = paddingValue;
      }
      opReg_opHeightIdx_0 = vmaxq_f32(ipReg_opHeightIdx_0, opReg_opHeightIdx_0);
      opReg_opHeightIdx_1 = vmaxq_f32(ipReg_opHeightIdx_1, opReg_opHeightIdx_1);
      opReg_opHeightIdx_2 = vmaxq_f32(ipReg_opHeightIdx_2, opReg_opHeightIdx_2);
      opReg_opHeightIdx_3 = vmaxq_f32(ipReg_opHeightIdx_3, opReg_opHeightIdx_3);
      opReg_opHeightIdx_4 = vmaxq_f32(ipReg_opHeightIdx_4, opReg_opHeightIdx_4);
      opReg_opHeightIdx_5 = vmaxq_f32(ipReg_opHeightIdx_5, opReg_opHeightIdx_5);
      opReg_opHeightIdx_6 = vmaxq_f32(ipReg_opHeightIdx_6, opReg_opHeightIdx_6);
      if (b && (topPaddingBound_tmp + 1 >= 0) &&
          (topPaddingBound_tmp + 1 < 112)) {
        ipReg_opHeightIdx_0 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 8]);
      } else {
        ipReg_opHeightIdx_0 = paddingValue;
      }
      if (b && (b_topPaddingBound_tmp + 1 >= 0) &&
          (b_topPaddingBound_tmp + 1 < 112)) {
        ipReg_opHeightIdx_1 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 16]);
      } else {
        ipReg_opHeightIdx_1 = paddingValue;
      }
      if (b && (c_topPaddingBound_tmp + 1 >= 0) &&
          (c_topPaddingBound_tmp + 1 < 112)) {
        ipReg_opHeightIdx_2 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 24]);
      } else {
        ipReg_opHeightIdx_2 = paddingValue;
      }
      if (b && (d_topPaddingBound_tmp + 1 >= 0) &&
          (d_topPaddingBound_tmp + 1 < 112)) {
        ipReg_opHeightIdx_3 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 32]);
      } else {
        ipReg_opHeightIdx_3 = paddingValue;
      }
      if (b && (e_topPaddingBound_tmp + 1 >= 0) &&
          (e_topPaddingBound_tmp + 1 < 112)) {
        ipReg_opHeightIdx_4 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 40]);
      } else {
        ipReg_opHeightIdx_4 = paddingValue;
      }
      if (b && (f_topPaddingBound_tmp + 1 >= 0) &&
          (f_topPaddingBound_tmp + 1 < 112)) {
        ipReg_opHeightIdx_5 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 48]);
      } else {
        ipReg_opHeightIdx_5 = paddingValue;
      }
      if (b && (g_topPaddingBound_tmp + 1 >= 0) &&
          (g_topPaddingBound_tmp + 1 < 112)) {
        ipReg_opHeightIdx_6 =
            vld1q_f32(&inputBufferPtr[c_idxToStrideInputBufferAlongWi + 56]);
      } else {
        ipReg_opHeightIdx_6 = paddingValue;
      }
      opReg_opHeightIdx_0 = vmaxq_f32(ipReg_opHeightIdx_0, opReg_opHeightIdx_0);
      opReg_opHeightIdx_1 = vmaxq_f32(ipReg_opHeightIdx_1, opReg_opHeightIdx_1);
      opReg_opHeightIdx_2 = vmaxq_f32(ipReg_opHeightIdx_2, opReg_opHeightIdx_2);
      opReg_opHeightIdx_3 = vmaxq_f32(ipReg_opHeightIdx_3, opReg_opHeightIdx_3);
      opReg_opHeightIdx_4 = vmaxq_f32(ipReg_opHeightIdx_4, opReg_opHeightIdx_4);
      opReg_opHeightIdx_5 = vmaxq_f32(ipReg_opHeightIdx_5, opReg_opHeightIdx_5);
      opReg_opHeightIdx_6 = vmaxq_f32(ipReg_opHeightIdx_6, opReg_opHeightIdx_6);
      c_idxToStrideInputBufferAlongWi += 448;
    }
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28], opReg_opHeightIdx_0);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 4],
              opReg_opHeightIdx_1);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 8],
              opReg_opHeightIdx_2);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 12],
              opReg_opHeightIdx_3);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 16],
              opReg_opHeightIdx_4);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 20],
              opReg_opHeightIdx_5);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 24],
              opReg_opHeightIdx_6);
    c_idxToStrideInputBufferAlongHe += 56;
    outputHeightIdx += 7;
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 * Return Type  : void
 */
static void maxPooling7231203818156735551(const float *inputTensor,
                                          float *outputTensor)
{
  int c_fusedOutputWidthAndChannelBlo;
  int outputChannelBlockIdx;
  int outputWidthIdx;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        outputChannelBlockIdx, outputWidthIdx)

  for (c_fusedOutputWidthAndChannelBlo = 0;
       c_fusedOutputWidthAndChannelBlo < 336;
       c_fusedOutputWidthAndChannelBlo++) {
    outputChannelBlockIdx =
        (int)((unsigned int)c_fusedOutputWidthAndChannelBlo / 56U);
    outputWidthIdx = c_fusedOutputWidthAndChannelBlo % 56;
    c_maxPoolingKernel7231203818156(
        &inputTensor[outputChannelBlockIdx * 50176],
        &outputTensor[outputWidthIdx * 224 + outputChannelBlockIdx * 12544],
        outputWidthIdx, ((outputWidthIdx << 1) - 1) * 448 - 4);
  }
}

/*
 * Arguments    : const float X[301056]
 *                float Z[75264]
 * Return Type  : void
 */
void pool(const float X[301056], float Z[75264])
{
  maxPooling7231203818156735551(&X[0], &Z[0]);
}

/*
 * File trailer for pool.c
 *
 * [EOF]
 */
