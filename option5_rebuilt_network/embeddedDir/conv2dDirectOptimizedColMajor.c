/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: conv2dDirectOptimizedColMajor.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:41:39
 */

/* Include Files */
#include "conv2dDirectOptimizedColMajor.h"
#include "predict_shufflenet_v5_rtwutil.h"
#include "omp.h"
#include <arm_neon.h>
#include <string.h>

/* Function Declarations */
static void b_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor);
static void b_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool outputChannelTailCase,
  bool c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const
  float *biasBufferPtr);
static void b_groupedConvolution(const float *inputTensor, float *outputTensor,
  const float *weights, const float *bias);
static void b_groupedConvolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, int convOutputWidthIdx, int
  c_startIdxWithPaddingOffsetInpu, const float *biasBufferPtr);
static void c_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor);
static void c_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool outputChannelTailCase,
  bool c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const
  float *biasBufferPtr);
static void c_groupedConvolution(const float *inputTensor, float *outputTensor,
  const float *weights, const float *bias);
static void c_groupedConvolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, int convOutputWidthIdx, int
  c_startIdxWithPaddingOffsetInpu, const float *biasBufferPtr);
static void convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor);
static void convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool outputChannelTailCase,
  bool c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const
  float *biasBufferPtr);
static void d_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor);
static void d_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool outputChannelTailCase,
  bool c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const
  float *biasBufferPtr);
static void d_groupedConvolution(const float *inputTensor, float *outputTensor,
  const float *weights, const float *bias);
static void d_groupedConvolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, int convOutputWidthIdx, int
  c_startIdxWithPaddingOffsetInpu, const float *biasBufferPtr);
static void e_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor);
static void e_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool outputChannelTailCase,
  bool c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const
  float *biasBufferPtr);
static void e_groupedConvolution(const float *inputTensor, float *outputTensor,
  const float *weights, const float *bias);
static void e_groupedConvolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, int convOutputWidthIdx, int
  c_startIdxWithPaddingOffsetInpu, const float *biasBufferPtr);
static void f_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor);
static void f_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, const float *biasBufferPtr);
static void f_groupedConvolution(const float *inputTensor, float *outputTensor,
  const float *weights, const float *bias);
static void f_groupedConvolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, int convOutputWidthIdx, int
  c_startIdxWithPaddingOffsetInpu, const float *biasBufferPtr);
static void g_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor);
static void g_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool
  c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const float
  *biasBufferPtr);
static void g_groupedConvolution(const float *inputTensor, float *outputTensor,
  const float *weights, const float *bias);
static void groupedConvolution(const float *inputTensor, float *outputTensor,
  const float *weights, const float *bias);
static void groupedConvolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, int convOutputWidthIdx, int
  c_startIdxWithPaddingOffsetInpu, const float *biasBufferPtr);
static void h_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor);
static void h_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool
  c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const float
  *biasBufferPtr);
static void i_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor);
static void i_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool
  c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const float
  *biasBufferPtr);

/* Function Definitions */
/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weightsTensor
 *                const float *biasTensor
 * Return Type  : void
 */
static void b_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor)
{
  int c_fusedOutputWidthAndChannelBlo;
  int inputChannelBlockIdx;
  int outputBufferIdx;
  int outputBufferIdx_tmp;
  int outputChannelBlockIdx;
  int weightsIdx;
  for (inputChannelBlockIdx = 0; inputChannelBlockIdx < 3; inputChannelBlockIdx
       ++) {
    int inputChannelBlockIdxOffset;
    int inputScratchpadBufferBaseIdx;
    inputChannelBlockIdxOffset = inputChannelBlockIdx << 5;
    inputScratchpadBufferBaseIdx = inputChannelBlockIdx * 6272;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,outputBufferIdx_tmp,outputBufferIdx,weightsIdx)

    for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
         140; c_fusedOutputWidthAndChannelBlo++) {
      outputChannelBlockIdx = (int)((unsigned int)
        c_fusedOutputWidthAndChannelBlo / 28U);
      outputBufferIdx_tmp = c_fusedOutputWidthAndChannelBlo % 28 * 112;
      outputBufferIdx = outputBufferIdx_tmp + outputChannelBlockIdx * 9408;
      weightsIdx = outputChannelBlockIdx * 288 + inputChannelBlockIdxOffset;
      outputBufferIdx_tmp += inputScratchpadBufferBaseIdx;
      g_convolutionKernel(&inputTensor[outputBufferIdx_tmp],
                          &outputTensor[outputBufferIdx],
                          &weightsTensor[weightsIdx], inputChannelBlockIdx == 0,
                          false, &biasTensor[outputChannelBlockIdx * 12]);
      g_convolutionKernel(&inputTensor[outputBufferIdx_tmp + 3136],
                          &outputTensor[outputBufferIdx],
                          &weightsTensor[weightsIdx + 16], false,
                          inputChannelBlockIdx == 2,
                          &biasTensor[outputChannelBlockIdx * 12]);
    }
  }
}

/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                const float *weightsBufferPtr
 *                bool outputChannelTailCase
 *                bool c_canInitializeOutputRegistersW
 *                bool canApplyActivationOperation
 *                const float *biasBufferPtr
 * Return Type  : void
 */
static void b_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool outputChannelTailCase,
  bool c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const
  float *biasBufferPtr)
{
  float32x4_t reluZero;
  int outputHeightBlockIdx;
  reluZero = vdupq_n_f32(0.0F);
  if (!outputChannelTailCase) {
    float32x4_t b_outputRegister;
    float32x4_t e_outputRegister;
    float32x4_t inputRegister0_0;
    float32x4_t outputRegister;
    int c_idxToStrideInputBufferAlongHe;
    c_idxToStrideInputBufferAlongHe = 0;
    for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 9;
         outputHeightBlockIdx++) {
      float32x4_t c_outputRegister;
      float32x4_t d_outputRegister;
      float32x4_t f_outputRegister;
      float32x4_t g_outputRegister;
      float32x4_t h_outputRegister;
      float32x4_t i_outputRegister;
      float32x4_t inputRegister0_1;
      float32x4_t inputRegister0_2;
      float32x4_t weightsRegister;
      if (c_canInitializeOutputRegistersW) {
        outputRegister = vld1q_f32(&biasBufferPtr[0]);
        c_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        d_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        b_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        f_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        g_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        e_outputRegister = vld1q_f32(&biasBufferPtr[8]);
        h_outputRegister = vld1q_f32(&biasBufferPtr[8]);
        i_outputRegister = vld1q_f32(&biasBufferPtr[8]);
      } else {
        outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12]);
        c_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 4]);
        d_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 8]);
        b_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 3136]);
        f_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 3140]);
        g_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 3144]);
        e_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 6272]);
        h_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 6276]);
        i_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 6280]);
      }

      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 8]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[464]);
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[928]);
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 9]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[468]);
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[932]);
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 10]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[472]);
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[936]);
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 11]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[476]);
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[940]);
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      if (canApplyActivationOperation) {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], vmaxq_f32
                  (outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4], vmaxq_f32
                  (c_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8], vmaxq_f32
                  (d_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3136], vmaxq_f32
                  (b_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3140], vmaxq_f32
                  (f_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3144], vmaxq_f32
                  (g_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6272], vmaxq_f32
                  (e_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6276], vmaxq_f32
                  (h_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6280], vmaxq_f32
                  (i_outputRegister, reluZero));
      } else {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4],
                  c_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8],
                  d_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3136],
                  b_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3140],
                  f_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3144],
                  g_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6272],
                  e_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6276],
                  h_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6280],
                  i_outputRegister);
      }

      c_idxToStrideInputBufferAlongHe += 12;
    }

    if (c_canInitializeOutputRegistersW) {
      outputRegister = vld1q_f32(&biasBufferPtr[0]);
      b_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      e_outputRegister = vld1q_f32(&biasBufferPtr[8]);
    } else {
      outputRegister = vld1q_f32(&outputBufferPtr[108]);
      b_outputRegister = vld1q_f32(&outputBufferPtr[3244]);
      e_outputRegister = vld1q_f32(&outputBufferPtr[6380]);
    }

    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[0])));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[464])));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[928])));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[4])));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[468])));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[932])));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[8])));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[472])));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[936])));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[12])));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[476])));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[940])));
    if (canApplyActivationOperation) {
      vst1q_f32(&outputBufferPtr[108], vmaxq_f32(outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[3244], vmaxq_f32(b_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[6380], vmaxq_f32(e_outputRegister, reluZero));
    } else {
      vst1q_f32(&outputBufferPtr[108], outputRegister);
      vst1q_f32(&outputBufferPtr[3244], b_outputRegister);
      vst1q_f32(&outputBufferPtr[6380], e_outputRegister);
    }
  } else {
    float32x4_t b_outputRegister;
    float32x4_t inputRegister0_0;
    float32x4_t outputRegister;
    int c_idxToStrideInputBufferAlongHe;
    c_idxToStrideInputBufferAlongHe = 0;
    for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 9;
         outputHeightBlockIdx++) {
      float32x4_t c_outputRegister;
      float32x4_t d_outputRegister;
      float32x4_t f_outputRegister;
      float32x4_t g_outputRegister;
      float32x4_t inputRegister0_1;
      float32x4_t inputRegister0_2;
      float32x4_t weightsRegister;
      if (c_canInitializeOutputRegistersW) {
        outputRegister = vld1q_f32(&biasBufferPtr[0]);
        c_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        d_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        b_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        f_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        g_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      } else {
        outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12]);
        c_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 4]);
        d_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 8]);
        b_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 3136]);
        f_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 3140]);
        g_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 3144]);
      }

      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 8]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[464]);
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 9]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[468]);
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 10]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[472]);
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 11]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[476]);
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      if (canApplyActivationOperation) {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], vmaxq_f32
                  (outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4], vmaxq_f32
                  (c_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8], vmaxq_f32
                  (d_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3136], vmaxq_f32
                  (b_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3140], vmaxq_f32
                  (f_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3144], vmaxq_f32
                  (g_outputRegister, reluZero));
      } else {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4],
                  c_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8],
                  d_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3136],
                  b_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3140],
                  f_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3144],
                  g_outputRegister);
      }

      c_idxToStrideInputBufferAlongHe += 12;
    }

    if (c_canInitializeOutputRegistersW) {
      outputRegister = vld1q_f32(&biasBufferPtr[0]);
      b_outputRegister = vld1q_f32(&biasBufferPtr[4]);
    } else {
      outputRegister = vld1q_f32(&outputBufferPtr[108]);
      b_outputRegister = vld1q_f32(&outputBufferPtr[3244]);
    }

    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[0])));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[464])));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[4])));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[468])));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[8])));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[472])));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[12])));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[476])));
    if (canApplyActivationOperation) {
      vst1q_f32(&outputBufferPtr[108], vmaxq_f32(outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[3244], vmaxq_f32(b_outputRegister, reluZero));
    } else {
      vst1q_f32(&outputBufferPtr[108], outputRegister);
      vst1q_f32(&outputBufferPtr[3244], b_outputRegister);
    }
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weights
 *                const float *bias
 * Return Type  : void
 */
static void b_groupedConvolution(const float *inputTensor, float *outputTensor,
  const float *weights, const float *bias)
{
  int c_fusedOutputWidthAndChannelBlo;
  int outputChannelBlockIdx;
  int outputWidthIdx;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,outputWidthIdx)

  for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
       420; c_fusedOutputWidthAndChannelBlo++) {
    outputChannelBlockIdx = (int)((unsigned int)c_fusedOutputWidthAndChannelBlo /
      28U);
    outputWidthIdx = c_fusedOutputWidthAndChannelBlo % 28;
    groupedConvolutionKernel(&inputTensor[outputChannelBlockIdx * 12544],
      &outputTensor[outputWidthIdx * 112 + outputChannelBlockIdx * 3136],
      &weights[outputChannelBlockIdx * 36], outputWidthIdx, ((outputWidthIdx <<
      1) - 1) * 224 - 4, &bias[outputChannelBlockIdx << 2]);
  }
}

/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                const float *weightsBufferPtr
 *                int convOutputWidthIdx
 *                int c_startIdxWithPaddingOffsetInpu
 *                const float *biasBufferPtr
 * Return Type  : void
 */
static void b_groupedConvolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, int convOutputWidthIdx, int
  c_startIdxWithPaddingOffsetInpu, const float *biasBufferPtr)
{
  float32x4_t biasRegister;
  int c_mIdxToStrideInputBufferAlongH;
  int kernelWidthIdx;
  int mOutputHeightIdx;
  int outputHeightBlockIdx;
  biasRegister = vld1q_f32(&biasBufferPtr[0]);
  c_mIdxToStrideInputBufferAlongH = c_startIdxWithPaddingOffsetInpu;
  mOutputHeightIdx = 0;
  for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 4; outputHeightBlockIdx
       ++) {
    float32x4_t b_outputRegister;
    float32x4_t c_outputRegister;
    float32x4_t d_outputRegister;
    float32x4_t e_outputRegister;
    float32x4_t f_outputRegister;
    float32x4_t g_outputRegister;
    float32x4_t outputRegister;
    int c_mIdxToStrideInputBufferAlongW;
    outputRegister = biasRegister;
    b_outputRegister = biasRegister;
    c_outputRegister = biasRegister;
    d_outputRegister = biasRegister;
    e_outputRegister = biasRegister;
    f_outputRegister = biasRegister;
    g_outputRegister = biasRegister;
    c_mIdxToStrideInputBufferAlongW = c_mIdxToStrideInputBufferAlongH;
    for (kernelWidthIdx = 0; kernelWidthIdx < 3; kernelWidthIdx++) {
      float32x4_t b_inputRegister;
      float32x4_t c_inputRegister;
      float32x4_t d_inputRegister;
      float32x4_t e_inputRegister;
      float32x4_t f_inputRegister;
      float32x4_t g_inputRegister;
      float32x4_t inputRegister;
      float32x4_t weightsRegister;
      int leftPaddingBound;
      bool b;
      bool b1;
      bool b2;
      bool b3;
      bool b4;
      bool b5;
      bool b6;
      leftPaddingBound = (convOutputWidthIdx + kernelWidthIdx) - 1;
      b = ((leftPaddingBound >= 0) && (leftPaddingBound < 28));
      if (b && (mOutputHeightIdx - 1 >= 0) && (mOutputHeightIdx - 1 < 28)) {
        inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW]);
      } else {
        inputRegister = vdupq_n_f32(0.0F);
      }

      b1 = (b && (mOutputHeightIdx >= 0) && (mOutputHeightIdx < 28));
      if (b1) {
        b_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 4]);
      } else {
        b_inputRegister = vdupq_n_f32(0.0F);
      }

      b2 = (b && (mOutputHeightIdx + 1 >= 0) && (mOutputHeightIdx + 1 < 28));
      if (b2) {
        c_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 8]);
      } else {
        c_inputRegister = vdupq_n_f32(0.0F);
      }

      b3 = (b && (mOutputHeightIdx + 2 >= 0) && (mOutputHeightIdx + 2 < 28));
      if (b3) {
        d_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 12]);
      } else {
        d_inputRegister = vdupq_n_f32(0.0F);
      }

      b4 = (b && (mOutputHeightIdx + 3 >= 0) && (mOutputHeightIdx + 3 < 28));
      if (b4) {
        e_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 16]);
      } else {
        e_inputRegister = vdupq_n_f32(0.0F);
      }

      b5 = (b && (mOutputHeightIdx + 4 >= 0) && (mOutputHeightIdx + 4 < 28));
      if (b5) {
        f_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 20]);
      } else {
        f_inputRegister = vdupq_n_f32(0.0F);
      }

      b6 = (b && (mOutputHeightIdx + 5 >= 0) && (mOutputHeightIdx + 5 < 28));
      if (b6) {
        g_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 24]);
      } else {
        g_inputRegister = vdupq_n_f32(0.0F);
      }

      weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(g_inputRegister,
        weightsRegister));
      if (b1) {
        inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 4]);
      } else {
        inputRegister = vdupq_n_f32(0.0F);
      }

      if (b2) {
        b_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 8]);
      } else {
        b_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b3) {
        c_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 12]);
      } else {
        c_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b4) {
        d_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 16]);
      } else {
        d_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b5) {
        e_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 20]);
      } else {
        e_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b6) {
        f_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 24]);
      } else {
        f_inputRegister = vdupq_n_f32(0.0F);
      }

      b1 = (b && (mOutputHeightIdx + 6 >= 0) && (mOutputHeightIdx + 6 < 28));
      if (b1) {
        g_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 28]);
      } else {
        g_inputRegister = vdupq_n_f32(0.0F);
      }

      weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12 + 4]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(g_inputRegister,
        weightsRegister));
      if (b2) {
        inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 8]);
      } else {
        inputRegister = vdupq_n_f32(0.0F);
      }

      if (b3) {
        b_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 12]);
      } else {
        b_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b4) {
        c_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 16]);
      } else {
        c_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b5) {
        d_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 20]);
      } else {
        d_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b6) {
        e_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 24]);
      } else {
        e_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b1) {
        f_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 28]);
      } else {
        f_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b && (mOutputHeightIdx + 7 >= 0) && (mOutputHeightIdx + 7 < 28)) {
        g_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 32]);
      } else {
        g_inputRegister = vdupq_n_f32(0.0F);
      }

      weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12 + 8]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(g_inputRegister,
        weightsRegister));
      c_mIdxToStrideInputBufferAlongW += 112;
    }

    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28], outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 4], b_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 8], c_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 12], d_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 16], e_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 20], f_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 24], g_outputRegister);
    c_mIdxToStrideInputBufferAlongH += 28;
    mOutputHeightIdx += 7;
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weightsTensor
 *                const float *biasTensor
 * Return Type  : void
 */
static void c_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor)
{
  int c_fusedOutputWidthAndChannelBlo;
  int inputChannelBlockIdx;
  int outputBufferIdx;
  int outputBufferIdx_tmp;
  int outputChannelBlockIdx;
  int weightsIdx;
  for (inputChannelBlockIdx = 0; inputChannelBlockIdx < 3; inputChannelBlockIdx
       ++) {
    int inputChannelBlockIdxOffset;
    int inputScratchpadBufferBaseIdx;
    inputChannelBlockIdxOffset = inputChannelBlockIdx << 5;
    inputScratchpadBufferBaseIdx = inputChannelBlockIdx * 25088;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,outputBufferIdx_tmp,outputBufferIdx,weightsIdx)

    for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
         280; c_fusedOutputWidthAndChannelBlo++) {
      outputChannelBlockIdx = (int)((unsigned int)
        c_fusedOutputWidthAndChannelBlo / 56U);
      outputBufferIdx_tmp = c_fusedOutputWidthAndChannelBlo % 56 * 224;
      outputBufferIdx = outputBufferIdx_tmp + outputChannelBlockIdx * 37632;
      weightsIdx = outputChannelBlockIdx * 288 + inputChannelBlockIdxOffset;
      outputBufferIdx_tmp += inputScratchpadBufferBaseIdx;
      h_convolutionKernel(&inputTensor[outputBufferIdx_tmp],
                          &outputTensor[outputBufferIdx],
                          &weightsTensor[weightsIdx], inputChannelBlockIdx == 0,
                          false, &biasTensor[outputChannelBlockIdx * 12]);
      h_convolutionKernel(&inputTensor[outputBufferIdx_tmp + 12544],
                          &outputTensor[outputBufferIdx],
                          &weightsTensor[weightsIdx + 16], false,
                          inputChannelBlockIdx == 2,
                          &biasTensor[outputChannelBlockIdx * 12]);
    }
  }
}

/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                const float *weightsBufferPtr
 *                bool outputChannelTailCase
 *                bool c_canInitializeOutputRegistersW
 *                bool canApplyActivationOperation
 *                const float *biasBufferPtr
 * Return Type  : void
 */
static void c_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool outputChannelTailCase,
  bool c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const
  float *biasBufferPtr)
{
  float32x4_t reluZero;
  int outputHeightBlockIdx;
  reluZero = vdupq_n_f32(0.0F);
  if (!outputChannelTailCase) {
    float32x4_t c_outputRegister;
    float32x4_t e_outputRegister;
    float32x4_t inputRegister0_0;
    float32x4_t outputRegister;
    int c_idxToStrideInputBufferAlongHe;
    c_idxToStrideInputBufferAlongHe = 0;
    for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 2;
         outputHeightBlockIdx++) {
      float32x4_t b_outputRegister;
      float32x4_t d_outputRegister;
      float32x4_t f_outputRegister;
      float32x4_t g_outputRegister;
      float32x4_t h_outputRegister;
      float32x4_t i_outputRegister;
      float32x4_t inputRegister0_1;
      float32x4_t inputRegister0_2;
      float32x4_t weightsRegister;
      if (c_canInitializeOutputRegistersW) {
        outputRegister = vld1q_f32(&biasBufferPtr[0]);
        b_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        d_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        c_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        f_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        g_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        e_outputRegister = vld1q_f32(&biasBufferPtr[8]);
        h_outputRegister = vld1q_f32(&biasBufferPtr[8]);
        i_outputRegister = vld1q_f32(&biasBufferPtr[8]);
      } else {
        outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12]);
        b_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 4]);
        d_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 8]);
        c_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 196]);
        f_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 200]);
        g_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 204]);
        e_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 392]);
        h_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 396]);
        i_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 400]);
      }

      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 8]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[928]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[1856]);
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 9]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[932]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[1860]);
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 10]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[936]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[1864]);
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 11]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[940]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[1868]);
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      if (canApplyActivationOperation) {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], vmaxq_f32
                  (outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4], vmaxq_f32
                  (b_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8], vmaxq_f32
                  (d_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 196], vmaxq_f32
                  (c_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 200], vmaxq_f32
                  (f_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 204], vmaxq_f32
                  (g_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 392], vmaxq_f32
                  (e_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 396], vmaxq_f32
                  (h_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 400], vmaxq_f32
                  (i_outputRegister, reluZero));
      } else {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4],
                  b_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8],
                  d_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 196],
                  c_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 200],
                  f_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 204],
                  g_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 392],
                  e_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 396],
                  h_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 400],
                  i_outputRegister);
      }

      c_idxToStrideInputBufferAlongHe += 12;
    }

    if (c_canInitializeOutputRegistersW) {
      outputRegister = vld1q_f32(&biasBufferPtr[0]);
      c_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      e_outputRegister = vld1q_f32(&biasBufferPtr[8]);
    } else {
      outputRegister = vld1q_f32(&outputBufferPtr[24]);
      c_outputRegister = vld1q_f32(&outputBufferPtr[220]);
      e_outputRegister = vld1q_f32(&outputBufferPtr[416]);
    }

    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[0])));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[928])));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[1856])));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[4])));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[932])));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[1860])));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[8])));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[936])));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[1864])));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[12])));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[940])));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[1868])));
    if (canApplyActivationOperation) {
      vst1q_f32(&outputBufferPtr[24], vmaxq_f32(outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[220], vmaxq_f32(c_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[416], vmaxq_f32(e_outputRegister, reluZero));
    } else {
      vst1q_f32(&outputBufferPtr[24], outputRegister);
      vst1q_f32(&outputBufferPtr[220], c_outputRegister);
      vst1q_f32(&outputBufferPtr[416], e_outputRegister);
    }
  } else {
    float32x4_t outputRegister;
    int c_idxToStrideInputBufferAlongHe;
    c_idxToStrideInputBufferAlongHe = 0;
    for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 2;
         outputHeightBlockIdx++) {
      float32x4_t b_outputRegister;
      float32x4_t d_outputRegister;
      float32x4_t weightsRegister;
      if (c_canInitializeOutputRegistersW) {
        outputRegister = vld1q_f32(&biasBufferPtr[0]);
        b_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        d_outputRegister = vld1q_f32(&biasBufferPtr[0]);
      } else {
        outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12]);
        b_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 4]);
        d_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 8]);
      }

      weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe]), weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]), weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 8]), weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]), weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]), weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 9]), weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]), weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]), weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 10]), weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]), weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]), weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 11]), weightsRegister));
      if (canApplyActivationOperation) {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], vmaxq_f32
                  (outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4], vmaxq_f32
                  (b_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8], vmaxq_f32
                  (d_outputRegister, reluZero));
      } else {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4],
                  b_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8],
                  d_outputRegister);
      }

      c_idxToStrideInputBufferAlongHe += 12;
    }

    if (c_canInitializeOutputRegistersW) {
      outputRegister = vld1q_f32(&biasBufferPtr[0]);
    } else {
      outputRegister = vld1q_f32(&outputBufferPtr[24]);
    }

    outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe]), vld1q_f32
      (&weightsBufferPtr[0])));
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]), vld1q_f32
      (&weightsBufferPtr[4])));
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]), vld1q_f32
      (&weightsBufferPtr[8])));
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]), vld1q_f32
      (&weightsBufferPtr[12])));
    if (canApplyActivationOperation) {
      vst1q_f32(&outputBufferPtr[24], vmaxq_f32(outputRegister, reluZero));
    } else {
      vst1q_f32(&outputBufferPtr[24], outputRegister);
    }
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weights
 *                const float *bias
 * Return Type  : void
 */
static void c_groupedConvolution(const float *inputTensor, float *outputTensor,
  const float *weights, const float *bias)
{
  int c_fusedOutputWidthAndChannelBlo;
  int outputChannelBlockIdx;
  int outputWidthIdx;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,outputWidthIdx)

  for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
       420; c_fusedOutputWidthAndChannelBlo++) {
    outputChannelBlockIdx = (int)((unsigned int)c_fusedOutputWidthAndChannelBlo /
      28U);
    outputWidthIdx = c_fusedOutputWidthAndChannelBlo % 28;
    b_groupedConvolutionKernel(&inputTensor[outputChannelBlockIdx * 3136],
      &outputTensor[outputWidthIdx * 112 + outputChannelBlockIdx * 3136],
      &weights[outputChannelBlockIdx * 36], outputWidthIdx, (outputWidthIdx - 1)
      * 112 - 4, &bias[outputChannelBlockIdx << 2]);
  }
}

/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                const float *weightsBufferPtr
 *                int convOutputWidthIdx
 *                int c_startIdxWithPaddingOffsetInpu
 *                const float *biasBufferPtr
 * Return Type  : void
 */
static void c_groupedConvolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, int convOutputWidthIdx, int
  c_startIdxWithPaddingOffsetInpu, const float *biasBufferPtr)
{
  float32x4_t biasRegister;
  int c_mIdxToStrideInputBufferAlongH;
  int kernelWidthIdx;
  int mOutputHeightIdx;
  int outputHeightBlockIdx;
  biasRegister = vld1q_f32(&biasBufferPtr[0]);
  c_mIdxToStrideInputBufferAlongH = c_startIdxWithPaddingOffsetInpu;
  mOutputHeightIdx = 0;
  for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 2; outputHeightBlockIdx
       ++) {
    float32x4_t b_outputRegister;
    float32x4_t c_outputRegister;
    float32x4_t d_outputRegister;
    float32x4_t e_outputRegister;
    float32x4_t f_outputRegister;
    float32x4_t g_outputRegister;
    float32x4_t outputRegister;
    int b_topPaddingBound_tmp;
    int c_mIdxToStrideInputBufferAlongW;
    int c_topPaddingBound_tmp;
    int d_topPaddingBound_tmp;
    int e_topPaddingBound_tmp;
    int f_topPaddingBound_tmp;
    int g_topPaddingBound_tmp;
    int topPaddingBound_tmp;
    outputRegister = biasRegister;
    b_outputRegister = biasRegister;
    c_outputRegister = biasRegister;
    d_outputRegister = biasRegister;
    e_outputRegister = biasRegister;
    f_outputRegister = biasRegister;
    g_outputRegister = biasRegister;
    c_mIdxToStrideInputBufferAlongW = c_mIdxToStrideInputBufferAlongH;
    topPaddingBound_tmp = mOutputHeightIdx << 1;
    b_topPaddingBound_tmp = (mOutputHeightIdx + 1) << 1;
    c_topPaddingBound_tmp = (mOutputHeightIdx + 2) << 1;
    d_topPaddingBound_tmp = (mOutputHeightIdx + 3) << 1;
    e_topPaddingBound_tmp = (mOutputHeightIdx + 4) << 1;
    f_topPaddingBound_tmp = (mOutputHeightIdx + 5) << 1;
    g_topPaddingBound_tmp = (mOutputHeightIdx + 6) << 1;
    for (kernelWidthIdx = 0; kernelWidthIdx < 3; kernelWidthIdx++) {
      float32x4_t b_inputRegister;
      float32x4_t c_inputRegister;
      float32x4_t d_inputRegister;
      float32x4_t e_inputRegister;
      float32x4_t f_inputRegister;
      float32x4_t g_inputRegister;
      float32x4_t inputRegister;
      float32x4_t weightsRegister;
      int i;
      i = ((convOutputWidthIdx << 1) + kernelWidthIdx) - 1;
      if ((i >= 0) && (topPaddingBound_tmp - 1 >= 0) && (topPaddingBound_tmp - 1
           < 28)) {
        inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW]);
      } else {
        inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (b_topPaddingBound_tmp - 1 >= 0) && (b_topPaddingBound_tmp
           - 1 < 28)) {
        b_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 8]);
      } else {
        b_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (c_topPaddingBound_tmp - 1 >= 0) && (c_topPaddingBound_tmp
           - 1 < 28)) {
        c_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 16]);
      } else {
        c_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (d_topPaddingBound_tmp - 1 >= 0) && (d_topPaddingBound_tmp
           - 1 < 28)) {
        d_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 24]);
      } else {
        d_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (e_topPaddingBound_tmp - 1 >= 0) && (e_topPaddingBound_tmp
           - 1 < 28)) {
        e_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 32]);
      } else {
        e_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (f_topPaddingBound_tmp - 1 >= 0) && (f_topPaddingBound_tmp
           - 1 < 28)) {
        f_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 40]);
      } else {
        f_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (g_topPaddingBound_tmp - 1 >= 0) && (g_topPaddingBound_tmp
           - 1 < 28)) {
        g_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 48]);
      } else {
        g_inputRegister = vdupq_n_f32(0.0F);
      }

      weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(g_inputRegister,
        weightsRegister));
      if ((i >= 0) && (topPaddingBound_tmp >= 0) && (topPaddingBound_tmp < 28))
      {
        inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 4]);
      } else {
        inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (b_topPaddingBound_tmp >= 0) && (b_topPaddingBound_tmp <
           28)) {
        b_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 12]);
      } else {
        b_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (c_topPaddingBound_tmp >= 0) && (c_topPaddingBound_tmp <
           28)) {
        c_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 20]);
      } else {
        c_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (d_topPaddingBound_tmp >= 0) && (d_topPaddingBound_tmp <
           28)) {
        d_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 28]);
      } else {
        d_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (e_topPaddingBound_tmp >= 0) && (e_topPaddingBound_tmp <
           28)) {
        e_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 36]);
      } else {
        e_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (f_topPaddingBound_tmp >= 0) && (f_topPaddingBound_tmp <
           28)) {
        f_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 44]);
      } else {
        f_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (g_topPaddingBound_tmp >= 0) && (g_topPaddingBound_tmp <
           28)) {
        g_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 52]);
      } else {
        g_inputRegister = vdupq_n_f32(0.0F);
      }

      weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12 + 4]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(g_inputRegister,
        weightsRegister));
      if ((i >= 0) && (topPaddingBound_tmp + 1 >= 0) && (topPaddingBound_tmp + 1
           < 28)) {
        inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 8]);
      } else {
        inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (b_topPaddingBound_tmp + 1 >= 0) && (b_topPaddingBound_tmp
           + 1 < 28)) {
        b_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 16]);
      } else {
        b_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (c_topPaddingBound_tmp + 1 >= 0) && (c_topPaddingBound_tmp
           + 1 < 28)) {
        c_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 24]);
      } else {
        c_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (d_topPaddingBound_tmp + 1 >= 0) && (d_topPaddingBound_tmp
           + 1 < 28)) {
        d_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 32]);
      } else {
        d_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (e_topPaddingBound_tmp + 1 >= 0) && (e_topPaddingBound_tmp
           + 1 < 28)) {
        e_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 40]);
      } else {
        e_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (f_topPaddingBound_tmp + 1 >= 0) && (f_topPaddingBound_tmp
           + 1 < 28)) {
        f_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 48]);
      } else {
        f_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (g_topPaddingBound_tmp + 1 >= 0) && (g_topPaddingBound_tmp
           + 1 < 28)) {
        g_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 56]);
      } else {
        g_inputRegister = vdupq_n_f32(0.0F);
      }

      weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12 + 8]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(g_inputRegister,
        weightsRegister));
      c_mIdxToStrideInputBufferAlongW += 112;
    }

    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28], outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 4], b_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 8], c_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 12], d_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 16], e_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 20], f_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 24], g_outputRegister);
    c_mIdxToStrideInputBufferAlongH += 56;
    mOutputHeightIdx += 7;
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weightsTensor
 *                const float *biasTensor
 * Return Type  : void
 */
static void convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor)
{
  static float inputScratchpadBuffer[153228];
  static bool bufferInitialized;
  int c_fusedOutputWidthAndChannelBlo;
  int c_inputChannelMiniblockBaseIdxI;
  int fusedInputChannelMiniBlockIdx;
  int fusedInputWidthAndHeightIdx;
  int i;
  int inputWidthIdx;
  int outputChannelBlockIdx;
  if (!bufferInitialized) {
    memset(&inputScratchpadBuffer[0], 0, (unsigned int)((int)sizeof(float) *
            153228));
    bufferInitialized = true;
  }

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(fusedInputWidthAndHeightIdx,inputWidthIdx,c_inputChannelMiniblockBaseIdxI)

  for (fusedInputChannelMiniBlockIdx = 0; fusedInputChannelMiniBlockIdx < 50176;
       fusedInputChannelMiniBlockIdx++) {
    fusedInputWidthAndHeightIdx = fusedInputChannelMiniBlockIdx % 50176;
    inputWidthIdx = (int)((unsigned int)fusedInputWidthAndHeightIdx / 224U);
    fusedInputWidthAndHeightIdx %= 224;
    c_inputChannelMiniblockBaseIdxI = fusedInputWidthAndHeightIdx +
      inputWidthIdx * 224;
    fusedInputWidthAndHeightIdx = (fusedInputWidthAndHeightIdx * 3 +
      inputWidthIdx * 678) + 681;
    inputScratchpadBuffer[fusedInputWidthAndHeightIdx] =
      inputTensor[c_inputChannelMiniblockBaseIdxI];
    inputScratchpadBuffer[fusedInputWidthAndHeightIdx + 1] =
      inputTensor[c_inputChannelMiniblockBaseIdxI + 50176];
    inputScratchpadBuffer[fusedInputWidthAndHeightIdx + 2] =
      inputTensor[c_inputChannelMiniblockBaseIdxI + 100352];
  }

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,i)

  for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
       224; c_fusedOutputWidthAndChannelBlo++) {
    outputChannelBlockIdx = (int)((unsigned int)c_fusedOutputWidthAndChannelBlo /
      112U);
    i = c_fusedOutputWidthAndChannelBlo % 112;
    f_convolutionKernel(&inputScratchpadBuffer[i * 1356], &outputTensor[i * 448
                        + outputChannelBlockIdx * 150528],
                        &weightsTensor[outputChannelBlockIdx * 324],
                        &biasTensor[outputChannelBlockIdx * 12]);
  }
}

/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                const float *weightsBufferPtr
 *                bool outputChannelTailCase
 *                bool c_canInitializeOutputRegistersW
 *                bool canApplyActivationOperation
 *                const float *biasBufferPtr
 * Return Type  : void
 */
static void convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool outputChannelTailCase,
  bool c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const
  float *biasBufferPtr)
{
  float32x4_t reluZero;
  int outputHeightBlockIdx;
  reluZero = vdupq_n_f32(0.0F);
  if (!outputChannelTailCase) {
    float32x4_t b_outputRegister;
    float32x4_t c_outputRegister;
    float32x4_t e_outputRegister;
    float32x4_t f_outputRegister;
    float32x4_t h_outputRegister;
    float32x4_t inputRegister0_0;
    float32x4_t inputRegister0_1;
    float32x4_t outputRegister;
    float32x4_t weightsRegister;
    int c_idxToStrideInputBufferAlongHe;
    c_idxToStrideInputBufferAlongHe = 0;
    for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 4;
         outputHeightBlockIdx++) {
      float32x4_t d_outputRegister;
      float32x4_t g_outputRegister;
      float32x4_t i_outputRegister;
      float32x4_t inputRegister0_2;
      if (c_canInitializeOutputRegistersW) {
        outputRegister = vld1q_f32(&biasBufferPtr[0]);
        b_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        d_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        c_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        e_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        g_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        f_outputRegister = vld1q_f32(&biasBufferPtr[8]);
        h_outputRegister = vld1q_f32(&biasBufferPtr[8]);
        i_outputRegister = vld1q_f32(&biasBufferPtr[8]);
      } else {
        outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12]);
        b_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 4]);
        d_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 8]);
        c_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 784]);
        e_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 788]);
        g_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 792]);
        f_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 1568]);
        h_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 1572]);
        i_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 1576]);
      }

      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 8]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[464]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[928]);
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 9]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[468]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[932]);
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 10]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[472]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[936]);
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 11]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[476]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[940]);
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      if (canApplyActivationOperation) {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], vmaxq_f32
                  (outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4], vmaxq_f32
                  (b_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8], vmaxq_f32
                  (d_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 784], vmaxq_f32
                  (c_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 788], vmaxq_f32
                  (e_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 792], vmaxq_f32
                  (g_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 1568], vmaxq_f32
                  (f_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 1572], vmaxq_f32
                  (h_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 1576], vmaxq_f32
                  (i_outputRegister, reluZero));
      } else {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4],
                  b_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8],
                  d_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 784],
                  c_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 788],
                  e_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 792],
                  g_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 1568],
                  f_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 1572],
                  h_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 1576],
                  i_outputRegister);
      }

      c_idxToStrideInputBufferAlongHe += 12;
    }

    if (c_canInitializeOutputRegistersW) {
      outputRegister = vld1q_f32(&biasBufferPtr[0]);
      b_outputRegister = vld1q_f32(&biasBufferPtr[0]);
      c_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      e_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      f_outputRegister = vld1q_f32(&biasBufferPtr[8]);
      h_outputRegister = vld1q_f32(&biasBufferPtr[8]);
    } else {
      outputRegister = vld1q_f32(&outputBufferPtr[48]);
      b_outputRegister = vld1q_f32(&outputBufferPtr[52]);
      c_outputRegister = vld1q_f32(&outputBufferPtr[832]);
      e_outputRegister = vld1q_f32(&outputBufferPtr[836]);
      f_outputRegister = vld1q_f32(&outputBufferPtr[1616]);
      h_outputRegister = vld1q_f32(&outputBufferPtr[1620]);
    }

    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[464]);
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[928]);
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[468]);
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[932]);
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[472]);
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[936]);
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[476]);
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[940]);
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    if (canApplyActivationOperation) {
      vst1q_f32(&outputBufferPtr[48], vmaxq_f32(outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[52], vmaxq_f32(b_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[832], vmaxq_f32(c_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[836], vmaxq_f32(e_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[1616], vmaxq_f32(f_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[1620], vmaxq_f32(h_outputRegister, reluZero));
    } else {
      vst1q_f32(&outputBufferPtr[48], outputRegister);
      vst1q_f32(&outputBufferPtr[52], b_outputRegister);
      vst1q_f32(&outputBufferPtr[832], c_outputRegister);
      vst1q_f32(&outputBufferPtr[836], e_outputRegister);
      vst1q_f32(&outputBufferPtr[1616], f_outputRegister);
      vst1q_f32(&outputBufferPtr[1620], h_outputRegister);
    }
  } else {
    float32x4_t b_outputRegister;
    float32x4_t c_outputRegister;
    float32x4_t e_outputRegister;
    float32x4_t inputRegister0_0;
    float32x4_t inputRegister0_1;
    float32x4_t outputRegister;
    float32x4_t weightsRegister;
    int c_idxToStrideInputBufferAlongHe;
    c_idxToStrideInputBufferAlongHe = 0;
    for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 4;
         outputHeightBlockIdx++) {
      float32x4_t d_outputRegister;
      float32x4_t g_outputRegister;
      float32x4_t inputRegister0_2;
      if (c_canInitializeOutputRegistersW) {
        outputRegister = vld1q_f32(&biasBufferPtr[0]);
        b_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        d_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        c_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        e_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        g_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      } else {
        outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12]);
        b_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 4]);
        d_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 8]);
        c_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 784]);
        e_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 788]);
        g_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 792]);
      }

      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 8]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[464]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 9]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[468]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 10]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[472]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 11]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[476]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      if (canApplyActivationOperation) {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], vmaxq_f32
                  (outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4], vmaxq_f32
                  (b_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8], vmaxq_f32
                  (d_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 784], vmaxq_f32
                  (c_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 788], vmaxq_f32
                  (e_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 792], vmaxq_f32
                  (g_outputRegister, reluZero));
      } else {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4],
                  b_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8],
                  d_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 784],
                  c_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 788],
                  e_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 792],
                  g_outputRegister);
      }

      c_idxToStrideInputBufferAlongHe += 12;
    }

    if (c_canInitializeOutputRegistersW) {
      outputRegister = vld1q_f32(&biasBufferPtr[0]);
      b_outputRegister = vld1q_f32(&biasBufferPtr[0]);
      c_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      e_outputRegister = vld1q_f32(&biasBufferPtr[4]);
    } else {
      outputRegister = vld1q_f32(&outputBufferPtr[48]);
      b_outputRegister = vld1q_f32(&outputBufferPtr[52]);
      c_outputRegister = vld1q_f32(&outputBufferPtr[832]);
      e_outputRegister = vld1q_f32(&outputBufferPtr[836]);
    }

    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[464]);
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[468]);
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[472]);
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[476]);
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    if (canApplyActivationOperation) {
      vst1q_f32(&outputBufferPtr[48], vmaxq_f32(outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[52], vmaxq_f32(b_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[832], vmaxq_f32(c_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[836], vmaxq_f32(e_outputRegister, reluZero));
    } else {
      vst1q_f32(&outputBufferPtr[48], outputRegister);
      vst1q_f32(&outputBufferPtr[52], b_outputRegister);
      vst1q_f32(&outputBufferPtr[832], c_outputRegister);
      vst1q_f32(&outputBufferPtr[836], e_outputRegister);
    }
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weightsTensor
 *                const float *biasTensor
 * Return Type  : void
 */
static void d_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor)
{
  int c_fusedOutputWidthAndChannelBlo;
  int c_numInputChannelMiniblocksPerB;
  int inputChannelBlockIdx;
  int inputChannelMiniblockIdx;
  int outputBufferIdx;
  int outputBufferIdx_tmp;
  int outputChannelBlockIdx;
  int weightsIdx;
  for (inputChannelBlockIdx = 0; inputChannelBlockIdx < 4; inputChannelBlockIdx
       ++) {
    int inputChannelBlockIdxOffset;
    int inputScratchpadBufferBaseIdx;
    inputChannelBlockIdxOffset = inputChannelBlockIdx << 6;
    inputScratchpadBufferBaseIdx = inputChannelBlockIdx * 12544;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,outputBufferIdx_tmp,outputBufferIdx,weightsIdx,c_numInputChannelMiniblocksPerB,inputChannelMiniblockIdx)

    for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
         140; c_fusedOutputWidthAndChannelBlo++) {
      outputChannelBlockIdx = (int)((unsigned int)
        c_fusedOutputWidthAndChannelBlo / 28U);
      outputBufferIdx_tmp = c_fusedOutputWidthAndChannelBlo % 28 * 112;
      outputBufferIdx = outputBufferIdx_tmp + outputChannelBlockIdx * 9408;
      weightsIdx = outputChannelBlockIdx * 720 + inputChannelBlockIdxOffset;
      outputBufferIdx_tmp += inputScratchpadBufferBaseIdx;
      if (inputChannelBlockIdx == 3) {
        c_numInputChannelMiniblocksPerB = 2;
      } else {
        c_numInputChannelMiniblocksPerB = 3;
      }

      for (inputChannelMiniblockIdx = 0; inputChannelMiniblockIdx <=
           c_numInputChannelMiniblocksPerB; inputChannelMiniblockIdx++) {
        i_convolutionKernel(&inputTensor[outputBufferIdx_tmp +
                            inputChannelMiniblockIdx * 3136],
                            &outputTensor[outputBufferIdx],
                            &weightsTensor[weightsIdx +
                            (inputChannelMiniblockIdx << 4)],
                            (inputChannelBlockIdx == 0) &&
                            (inputChannelMiniblockIdx == 0),
                            (inputChannelBlockIdx == 3) &&
                            (inputChannelMiniblockIdx == 2),
                            &biasTensor[outputChannelBlockIdx * 12]);
      }
    }
  }
}

/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                const float *weightsBufferPtr
 *                bool outputChannelTailCase
 *                bool c_canInitializeOutputRegistersW
 *                bool canApplyActivationOperation
 *                const float *biasBufferPtr
 * Return Type  : void
 */
static void d_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool outputChannelTailCase,
  bool c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const
  float *biasBufferPtr)
{
  float32x4_t reluZero;
  int outputHeightBlockIdx;
  reluZero = vdupq_n_f32(0.0F);
  if (!outputChannelTailCase) {
    float32x4_t b_outputRegister;
    float32x4_t d_outputRegister;
    float32x4_t e_outputRegister;
    float32x4_t f_outputRegister;
    float32x4_t g_outputRegister;
    float32x4_t inputRegister0_0;
    float32x4_t inputRegister0_1;
    float32x4_t outputRegister;
    float32x4_t weightsRegister;
    int c_idxToStrideInputBufferAlongHe;
    c_idxToStrideInputBufferAlongHe = 0;
    for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 4;
         outputHeightBlockIdx++) {
      float32x4_t c_outputRegister;
      float32x4_t h_outputRegister;
      float32x4_t i_outputRegister;
      float32x4_t inputRegister0_2;
      if (c_canInitializeOutputRegistersW) {
        outputRegister = vld1q_f32(&biasBufferPtr[0]);
        b_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        c_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        d_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        e_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        h_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        f_outputRegister = vld1q_f32(&biasBufferPtr[8]);
        g_outputRegister = vld1q_f32(&biasBufferPtr[8]);
        i_outputRegister = vld1q_f32(&biasBufferPtr[8]);
      } else {
        outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12]);
        b_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 4]);
        c_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 8]);
        d_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 784]);
        e_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 788]);
        h_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 792]);
        f_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 1568]);
        g_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 1572]);
        i_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 1576]);
      }

      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 8]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[928]);
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[1856]);
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 9]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[932]);
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[1860]);
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 10]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[936]);
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[1864]);
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 11]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[940]);
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[1868]);
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      if (canApplyActivationOperation) {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], vmaxq_f32
                  (outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4], vmaxq_f32
                  (b_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8], vmaxq_f32
                  (c_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 784], vmaxq_f32
                  (d_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 788], vmaxq_f32
                  (e_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 792], vmaxq_f32
                  (h_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 1568], vmaxq_f32
                  (f_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 1572], vmaxq_f32
                  (g_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 1576], vmaxq_f32
                  (i_outputRegister, reluZero));
      } else {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4],
                  b_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8],
                  c_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 784],
                  d_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 788],
                  e_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 792],
                  h_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 1568],
                  f_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 1572],
                  g_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 1576],
                  i_outputRegister);
      }

      c_idxToStrideInputBufferAlongHe += 12;
    }

    if (c_canInitializeOutputRegistersW) {
      outputRegister = vld1q_f32(&biasBufferPtr[0]);
      b_outputRegister = vld1q_f32(&biasBufferPtr[0]);
      d_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      e_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      f_outputRegister = vld1q_f32(&biasBufferPtr[8]);
      g_outputRegister = vld1q_f32(&biasBufferPtr[8]);
    } else {
      outputRegister = vld1q_f32(&outputBufferPtr[48]);
      b_outputRegister = vld1q_f32(&outputBufferPtr[52]);
      d_outputRegister = vld1q_f32(&outputBufferPtr[832]);
      e_outputRegister = vld1q_f32(&outputBufferPtr[836]);
      f_outputRegister = vld1q_f32(&outputBufferPtr[1616]);
      g_outputRegister = vld1q_f32(&outputBufferPtr[1620]);
    }

    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[928]);
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[1856]);
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[932]);
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[1860]);
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[936]);
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[1864]);
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[940]);
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[1868]);
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    if (canApplyActivationOperation) {
      vst1q_f32(&outputBufferPtr[48], vmaxq_f32(outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[52], vmaxq_f32(b_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[832], vmaxq_f32(d_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[836], vmaxq_f32(e_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[1616], vmaxq_f32(f_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[1620], vmaxq_f32(g_outputRegister, reluZero));
    } else {
      vst1q_f32(&outputBufferPtr[48], outputRegister);
      vst1q_f32(&outputBufferPtr[52], b_outputRegister);
      vst1q_f32(&outputBufferPtr[832], d_outputRegister);
      vst1q_f32(&outputBufferPtr[836], e_outputRegister);
      vst1q_f32(&outputBufferPtr[1616], f_outputRegister);
      vst1q_f32(&outputBufferPtr[1620], g_outputRegister);
    }
  } else {
    float32x4_t b_outputRegister;
    float32x4_t outputRegister;
    float32x4_t weightsRegister;
    int c_idxToStrideInputBufferAlongHe;
    c_idxToStrideInputBufferAlongHe = 0;
    for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 4;
         outputHeightBlockIdx++) {
      float32x4_t c_outputRegister;
      if (c_canInitializeOutputRegistersW) {
        outputRegister = vld1q_f32(&biasBufferPtr[0]);
        b_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        c_outputRegister = vld1q_f32(&biasBufferPtr[0]);
      } else {
        outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12]);
        b_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 4]);
        c_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 8]);
      }

      weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe]), weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]), weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 8]), weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]), weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]), weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 9]), weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]), weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]), weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 10]), weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]), weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]), weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 11]), weightsRegister));
      if (canApplyActivationOperation) {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], vmaxq_f32
                  (outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4], vmaxq_f32
                  (b_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8], vmaxq_f32
                  (c_outputRegister, reluZero));
      } else {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4],
                  b_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8],
                  c_outputRegister);
      }

      c_idxToStrideInputBufferAlongHe += 12;
    }

    if (c_canInitializeOutputRegistersW) {
      outputRegister = vld1q_f32(&biasBufferPtr[0]);
      b_outputRegister = vld1q_f32(&biasBufferPtr[0]);
    } else {
      outputRegister = vld1q_f32(&outputBufferPtr[48]);
      b_outputRegister = vld1q_f32(&outputBufferPtr[52]);
    }

    weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe]), weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]), weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]), weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]), weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]), weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]), weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]), weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]), weightsRegister));
    if (canApplyActivationOperation) {
      vst1q_f32(&outputBufferPtr[48], vmaxq_f32(outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[52], vmaxq_f32(b_outputRegister, reluZero));
    } else {
      vst1q_f32(&outputBufferPtr[48], outputRegister);
      vst1q_f32(&outputBufferPtr[52], b_outputRegister);
    }
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weights
 *                const float *bias
 * Return Type  : void
 */
static void d_groupedConvolution(const float *inputTensor, float *outputTensor,
  const float *weights, const float *bias)
{
  int c_fusedOutputWidthAndChannelBlo;
  int outputChannelBlockIdx;
  int outputWidthIdx;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,outputWidthIdx)

  for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
       406; c_fusedOutputWidthAndChannelBlo++) {
    outputChannelBlockIdx = (int)((unsigned int)c_fusedOutputWidthAndChannelBlo /
      14U);
    outputWidthIdx = c_fusedOutputWidthAndChannelBlo % 14;
    c_groupedConvolutionKernel(&inputTensor[outputChannelBlockIdx * 3136],
      &outputTensor[outputWidthIdx * 56 + outputChannelBlockIdx * 784],
      &weights[outputChannelBlockIdx * 36], outputWidthIdx, ((outputWidthIdx <<
      1) - 1) * 112 - 4, &bias[outputChannelBlockIdx << 2]);
  }
}

/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                const float *weightsBufferPtr
 *                int convOutputWidthIdx
 *                int c_startIdxWithPaddingOffsetInpu
 *                const float *biasBufferPtr
 * Return Type  : void
 */
static void d_groupedConvolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, int convOutputWidthIdx, int
  c_startIdxWithPaddingOffsetInpu, const float *biasBufferPtr)
{
  float32x4_t biasRegister;
  int c_mIdxToStrideInputBufferAlongH;
  int kernelWidthIdx;
  int mOutputHeightIdx;
  int outputHeightBlockIdx;
  biasRegister = vld1q_f32(&biasBufferPtr[0]);
  c_mIdxToStrideInputBufferAlongH = c_startIdxWithPaddingOffsetInpu;
  mOutputHeightIdx = 0;
  for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 2; outputHeightBlockIdx
       ++) {
    float32x4_t b_outputRegister;
    float32x4_t c_outputRegister;
    float32x4_t d_outputRegister;
    float32x4_t e_outputRegister;
    float32x4_t f_outputRegister;
    float32x4_t g_outputRegister;
    float32x4_t outputRegister;
    int c_mIdxToStrideInputBufferAlongW;
    outputRegister = biasRegister;
    b_outputRegister = biasRegister;
    c_outputRegister = biasRegister;
    d_outputRegister = biasRegister;
    e_outputRegister = biasRegister;
    f_outputRegister = biasRegister;
    g_outputRegister = biasRegister;
    c_mIdxToStrideInputBufferAlongW = c_mIdxToStrideInputBufferAlongH;
    for (kernelWidthIdx = 0; kernelWidthIdx < 3; kernelWidthIdx++) {
      float32x4_t b_inputRegister;
      float32x4_t c_inputRegister;
      float32x4_t d_inputRegister;
      float32x4_t e_inputRegister;
      float32x4_t f_inputRegister;
      float32x4_t g_inputRegister;
      float32x4_t inputRegister;
      float32x4_t weightsRegister;
      int leftPaddingBound;
      bool b;
      bool b1;
      bool b2;
      bool b3;
      bool b4;
      bool b5;
      bool b6;
      leftPaddingBound = (convOutputWidthIdx + kernelWidthIdx) - 1;
      b = ((leftPaddingBound >= 0) && (leftPaddingBound < 14));
      if (b && (mOutputHeightIdx - 1 >= 0) && (mOutputHeightIdx - 1 < 14)) {
        inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW]);
      } else {
        inputRegister = vdupq_n_f32(0.0F);
      }

      b1 = (b && (mOutputHeightIdx >= 0) && (mOutputHeightIdx < 14));
      if (b1) {
        b_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 4]);
      } else {
        b_inputRegister = vdupq_n_f32(0.0F);
      }

      b2 = (b && (mOutputHeightIdx + 1 >= 0) && (mOutputHeightIdx + 1 < 14));
      if (b2) {
        c_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 8]);
      } else {
        c_inputRegister = vdupq_n_f32(0.0F);
      }

      b3 = (b && (mOutputHeightIdx + 2 >= 0) && (mOutputHeightIdx + 2 < 14));
      if (b3) {
        d_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 12]);
      } else {
        d_inputRegister = vdupq_n_f32(0.0F);
      }

      b4 = (b && (mOutputHeightIdx + 3 >= 0) && (mOutputHeightIdx + 3 < 14));
      if (b4) {
        e_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 16]);
      } else {
        e_inputRegister = vdupq_n_f32(0.0F);
      }

      b5 = (b && (mOutputHeightIdx + 4 >= 0) && (mOutputHeightIdx + 4 < 14));
      if (b5) {
        f_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 20]);
      } else {
        f_inputRegister = vdupq_n_f32(0.0F);
      }

      b6 = (b && (mOutputHeightIdx + 5 >= 0) && (mOutputHeightIdx + 5 < 14));
      if (b6) {
        g_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 24]);
      } else {
        g_inputRegister = vdupq_n_f32(0.0F);
      }

      weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(g_inputRegister,
        weightsRegister));
      if (b1) {
        inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 4]);
      } else {
        inputRegister = vdupq_n_f32(0.0F);
      }

      if (b2) {
        b_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 8]);
      } else {
        b_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b3) {
        c_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 12]);
      } else {
        c_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b4) {
        d_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 16]);
      } else {
        d_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b5) {
        e_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 20]);
      } else {
        e_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b6) {
        f_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 24]);
      } else {
        f_inputRegister = vdupq_n_f32(0.0F);
      }

      b1 = (b && (mOutputHeightIdx + 6 >= 0) && (mOutputHeightIdx + 6 < 14));
      if (b1) {
        g_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 28]);
      } else {
        g_inputRegister = vdupq_n_f32(0.0F);
      }

      weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12 + 4]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(g_inputRegister,
        weightsRegister));
      if (b2) {
        inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 8]);
      } else {
        inputRegister = vdupq_n_f32(0.0F);
      }

      if (b3) {
        b_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 12]);
      } else {
        b_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b4) {
        c_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 16]);
      } else {
        c_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b5) {
        d_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 20]);
      } else {
        d_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b6) {
        e_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 24]);
      } else {
        e_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b1) {
        f_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 28]);
      } else {
        f_inputRegister = vdupq_n_f32(0.0F);
      }

      if (b && (mOutputHeightIdx + 7 >= 0) && (mOutputHeightIdx + 7 < 14)) {
        g_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 32]);
      } else {
        g_inputRegister = vdupq_n_f32(0.0F);
      }

      weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12 + 8]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(g_inputRegister,
        weightsRegister));
      c_mIdxToStrideInputBufferAlongW += 56;
    }

    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28], outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 4], b_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 8], c_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 12], d_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 16], e_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 20], f_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 24], g_outputRegister);
    c_mIdxToStrideInputBufferAlongH += 28;
    mOutputHeightIdx += 7;
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weightsTensor
 *                const float *biasTensor
 * Return Type  : void
 */
static void e_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor)
{
  int c_fusedOutputWidthAndChannelBlo;
  int c_numInputChannelMiniblocksPerB;
  int inputChannelBlockIdx;
  int inputChannelMiniblockIdx;
  int outputBufferIdx;
  int outputBufferIdx_tmp;
  int outputChannelBlockIdx;
  int weightsIdx;
  bool outputChannelTailCase;
  for (inputChannelBlockIdx = 0; inputChannelBlockIdx < 4; inputChannelBlockIdx
       ++) {
    int inputChannelBlockIdxOffset;
    int inputScratchpadBufferBaseIdx;
    inputChannelBlockIdxOffset = inputChannelBlockIdx << 7;
    inputScratchpadBufferBaseIdx = inputChannelBlockIdx * 6272;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,outputBufferIdx_tmp,outputBufferIdx,weightsIdx,c_numInputChannelMiniblocksPerB,outputChannelTailCase,inputChannelMiniblockIdx)

    for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
         140; c_fusedOutputWidthAndChannelBlo++) {
      outputChannelBlockIdx = (int)((unsigned int)
        c_fusedOutputWidthAndChannelBlo / 14U);
      outputBufferIdx_tmp = c_fusedOutputWidthAndChannelBlo % 14 * 56;
      outputBufferIdx = outputBufferIdx_tmp + outputChannelBlockIdx * 2352;
      weightsIdx = outputChannelBlockIdx * 1392 + inputChannelBlockIdxOffset;
      outputBufferIdx_tmp += inputScratchpadBufferBaseIdx;
      if (inputChannelBlockIdx == 3) {
        c_numInputChannelMiniblocksPerB = 4;
      } else {
        c_numInputChannelMiniblocksPerB = 7;
      }

      outputChannelTailCase = (outputChannelBlockIdx == 9);
      for (inputChannelMiniblockIdx = 0; inputChannelMiniblockIdx <=
           c_numInputChannelMiniblocksPerB; inputChannelMiniblockIdx++) {
        convolutionKernel(&inputTensor[outputBufferIdx_tmp +
                          inputChannelMiniblockIdx * 784],
                          &outputTensor[outputBufferIdx],
                          &weightsTensor[weightsIdx + (inputChannelMiniblockIdx <<
          4)], outputChannelTailCase, (inputChannelBlockIdx == 0) &&
                          (inputChannelMiniblockIdx == 0), (inputChannelBlockIdx
          == 3) && (inputChannelMiniblockIdx == 4),
                          &biasTensor[outputChannelBlockIdx * 12]);
      }
    }
  }
}

/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                const float *weightsBufferPtr
 *                bool outputChannelTailCase
 *                bool c_canInitializeOutputRegistersW
 *                bool canApplyActivationOperation
 *                const float *biasBufferPtr
 * Return Type  : void
 */
static void e_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool outputChannelTailCase,
  bool c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const
  float *biasBufferPtr)
{
  float32x4_t reluZero;
  int outputHeightBlockIdx;
  reluZero = vdupq_n_f32(0.0F);
  if (!outputChannelTailCase) {
    float32x4_t c_outputRegister;
    float32x4_t e_outputRegister;
    float32x4_t inputRegister0_0;
    float32x4_t outputRegister;
    int c_idxToStrideInputBufferAlongHe;
    c_idxToStrideInputBufferAlongHe = 0;
    for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 2;
         outputHeightBlockIdx++) {
      float32x4_t b_outputRegister;
      float32x4_t d_outputRegister;
      float32x4_t f_outputRegister;
      float32x4_t g_outputRegister;
      float32x4_t h_outputRegister;
      float32x4_t i_outputRegister;
      float32x4_t inputRegister0_1;
      float32x4_t inputRegister0_2;
      float32x4_t weightsRegister;
      if (c_canInitializeOutputRegistersW) {
        outputRegister = vld1q_f32(&biasBufferPtr[0]);
        b_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        d_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        c_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        f_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        g_outputRegister = vld1q_f32(&biasBufferPtr[4]);
        e_outputRegister = vld1q_f32(&biasBufferPtr[8]);
        h_outputRegister = vld1q_f32(&biasBufferPtr[8]);
        i_outputRegister = vld1q_f32(&biasBufferPtr[8]);
      } else {
        outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12]);
        b_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 4]);
        d_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 8]);
        c_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 196]);
        f_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 200]);
        g_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 204]);
        e_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 392]);
        h_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 396]);
        i_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 400]);
      }

      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 8]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[1856]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[3712]);
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 9]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[1860]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[3716]);
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 10]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[1864]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[3720]);
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
      inputRegister0_1 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]);
      inputRegister0_2 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 11]);
      weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[1868]);
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[3724]);
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
        weightsRegister));
      h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
        weightsRegister));
      i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
        weightsRegister));
      if (canApplyActivationOperation) {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], vmaxq_f32
                  (outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4], vmaxq_f32
                  (b_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8], vmaxq_f32
                  (d_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 196], vmaxq_f32
                  (c_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 200], vmaxq_f32
                  (f_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 204], vmaxq_f32
                  (g_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 392], vmaxq_f32
                  (e_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 396], vmaxq_f32
                  (h_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 400], vmaxq_f32
                  (i_outputRegister, reluZero));
      } else {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4],
                  b_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8],
                  d_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 196],
                  c_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 200],
                  f_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 204],
                  g_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 392],
                  e_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 396],
                  h_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 400],
                  i_outputRegister);
      }

      c_idxToStrideInputBufferAlongHe += 12;
    }

    if (c_canInitializeOutputRegistersW) {
      outputRegister = vld1q_f32(&biasBufferPtr[0]);
      c_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      e_outputRegister = vld1q_f32(&biasBufferPtr[8]);
    } else {
      outputRegister = vld1q_f32(&outputBufferPtr[24]);
      c_outputRegister = vld1q_f32(&outputBufferPtr[220]);
      e_outputRegister = vld1q_f32(&outputBufferPtr[416]);
    }

    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[0])));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[1856])));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[3712])));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[4])));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[1860])));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[3716])));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[8])));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[1864])));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[3720])));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[12])));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[1868])));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_0,
      vld1q_f32(&weightsBufferPtr[3724])));
    if (canApplyActivationOperation) {
      vst1q_f32(&outputBufferPtr[24], vmaxq_f32(outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[220], vmaxq_f32(c_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[416], vmaxq_f32(e_outputRegister, reluZero));
    } else {
      vst1q_f32(&outputBufferPtr[24], outputRegister);
      vst1q_f32(&outputBufferPtr[220], c_outputRegister);
      vst1q_f32(&outputBufferPtr[416], e_outputRegister);
    }
  } else {
    float32x4_t outputRegister;
    int c_idxToStrideInputBufferAlongHe;
    c_idxToStrideInputBufferAlongHe = 0;
    for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 2;
         outputHeightBlockIdx++) {
      float32x4_t b_outputRegister;
      float32x4_t d_outputRegister;
      float32x4_t weightsRegister;
      if (c_canInitializeOutputRegistersW) {
        outputRegister = vld1q_f32(&biasBufferPtr[0]);
        b_outputRegister = vld1q_f32(&biasBufferPtr[0]);
        d_outputRegister = vld1q_f32(&biasBufferPtr[0]);
      } else {
        outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12]);
        b_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 4]);
        d_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12
          + 8]);
      }

      weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe]), weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]), weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 8]), weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]), weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]), weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 9]), weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]), weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]), weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 10]), weightsRegister));
      weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]), weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]), weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 11]), weightsRegister));
      if (canApplyActivationOperation) {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], vmaxq_f32
                  (outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4], vmaxq_f32
                  (b_outputRegister, reluZero));
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8], vmaxq_f32
                  (d_outputRegister, reluZero));
      } else {
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4],
                  b_outputRegister);
        vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8],
                  d_outputRegister);
      }

      c_idxToStrideInputBufferAlongHe += 12;
    }

    if (c_canInitializeOutputRegistersW) {
      outputRegister = vld1q_f32(&biasBufferPtr[0]);
    } else {
      outputRegister = vld1q_f32(&outputBufferPtr[24]);
    }

    outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe]), vld1q_f32
      (&weightsBufferPtr[0])));
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]), vld1q_f32
      (&weightsBufferPtr[4])));
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]), vld1q_f32
      (&weightsBufferPtr[8])));
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]), vld1q_f32
      (&weightsBufferPtr[12])));
    if (canApplyActivationOperation) {
      vst1q_f32(&outputBufferPtr[24], vmaxq_f32(outputRegister, reluZero));
    } else {
      vst1q_f32(&outputBufferPtr[24], outputRegister);
    }
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weights
 *                const float *bias
 * Return Type  : void
 */
static void e_groupedConvolution(const float *inputTensor, float *outputTensor,
  const float *weights, const float *bias)
{
  int c_fusedOutputWidthAndChannelBlo;
  int outputChannelBlockIdx;
  int outputWidthIdx;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,outputWidthIdx)

  for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
       406; c_fusedOutputWidthAndChannelBlo++) {
    outputChannelBlockIdx = (int)((unsigned int)c_fusedOutputWidthAndChannelBlo /
      14U);
    outputWidthIdx = c_fusedOutputWidthAndChannelBlo % 14;
    d_groupedConvolutionKernel(&inputTensor[outputChannelBlockIdx * 784],
      &outputTensor[outputWidthIdx * 56 + outputChannelBlockIdx * 784],
      &weights[outputChannelBlockIdx * 36], outputWidthIdx, (outputWidthIdx - 1)
      * 56 - 4, &bias[outputChannelBlockIdx << 2]);
  }
}

/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                const float *weightsBufferPtr
 *                int convOutputWidthIdx
 *                int c_startIdxWithPaddingOffsetInpu
 *                const float *biasBufferPtr
 * Return Type  : void
 */
static void e_groupedConvolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, int convOutputWidthIdx, int
  c_startIdxWithPaddingOffsetInpu, const float *biasBufferPtr)
{
  float32x4_t b_outputRegister;
  float32x4_t biasRegister;
  float32x4_t c_outputRegister;
  float32x4_t d_outputRegister;
  float32x4_t e_outputRegister;
  float32x4_t f_outputRegister;
  float32x4_t inputRegister_tmp_tmp;
  float32x4_t outputRegister;
  int c_mIdxToStrideInputBufferAlongW;
  int kernelWidthIdx;
  biasRegister = vld1q_f32(&biasBufferPtr[0]);
  c_mIdxToStrideInputBufferAlongW = c_startIdxWithPaddingOffsetInpu;
  outputRegister = biasRegister;
  b_outputRegister = biasRegister;
  c_outputRegister = biasRegister;
  d_outputRegister = biasRegister;
  e_outputRegister = biasRegister;
  f_outputRegister = biasRegister;
  inputRegister_tmp_tmp = vdupq_n_f32(0.0F);
  for (kernelWidthIdx = 0; kernelWidthIdx < 3; kernelWidthIdx++) {
    float32x4_t b_inputRegister;
    float32x4_t c_inputRegister;
    float32x4_t d_inputRegister;
    float32x4_t e_inputRegister;
    float32x4_t f_inputRegister;
    float32x4_t g_inputRegister;
    float32x4_t inputRegister;
    float32x4_t weightsRegister;
    int i;
    i = ((convOutputWidthIdx << 1) + kernelWidthIdx) - 1;
    if (i >= 0) {
      inputRegister = vld1q_f32(&inputBufferPtr[c_mIdxToStrideInputBufferAlongW
        + 8]);
      b_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 16]);
      c_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 24]);
      d_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 32]);
      e_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 40]);
      f_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 48]);
    } else {
      inputRegister = inputRegister_tmp_tmp;
      b_inputRegister = inputRegister_tmp_tmp;
      c_inputRegister = inputRegister_tmp_tmp;
      d_inputRegister = inputRegister_tmp_tmp;
      e_inputRegister = inputRegister_tmp_tmp;
      f_inputRegister = inputRegister_tmp_tmp;
    }

    weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12]);
    biasRegister = vaddq_f32(biasRegister, vmulq_f32(inputRegister_tmp_tmp,
      weightsRegister));
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
      weightsRegister));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
      weightsRegister));
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
      weightsRegister));
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
      weightsRegister));
    if (i >= 0) {
      g_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 4]);
      inputRegister = vld1q_f32(&inputBufferPtr[c_mIdxToStrideInputBufferAlongW
        + 12]);
      b_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 20]);
      c_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 28]);
      d_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 36]);
      e_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 44]);
      f_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 52]);
    } else {
      g_inputRegister = inputRegister_tmp_tmp;
      inputRegister = inputRegister_tmp_tmp;
      b_inputRegister = inputRegister_tmp_tmp;
      c_inputRegister = inputRegister_tmp_tmp;
      d_inputRegister = inputRegister_tmp_tmp;
      e_inputRegister = inputRegister_tmp_tmp;
      f_inputRegister = inputRegister_tmp_tmp;
    }

    weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12 + 4]);
    biasRegister = vaddq_f32(biasRegister, vmulq_f32(g_inputRegister,
      weightsRegister));
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
      weightsRegister));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
      weightsRegister));
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
      weightsRegister));
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
      weightsRegister));
    if (i >= 0) {
      g_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 8]);
      inputRegister = vld1q_f32(&inputBufferPtr[c_mIdxToStrideInputBufferAlongW
        + 16]);
      b_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 24]);
      c_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 32]);
      d_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 40]);
      e_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 48]);
      f_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 56]);
    } else {
      g_inputRegister = inputRegister_tmp_tmp;
      inputRegister = inputRegister_tmp_tmp;
      b_inputRegister = inputRegister_tmp_tmp;
      c_inputRegister = inputRegister_tmp_tmp;
      d_inputRegister = inputRegister_tmp_tmp;
      e_inputRegister = inputRegister_tmp_tmp;
      f_inputRegister = inputRegister_tmp_tmp;
    }

    weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12 + 8]);
    biasRegister = vaddq_f32(biasRegister, vmulq_f32(g_inputRegister,
      weightsRegister));
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
      weightsRegister));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
      weightsRegister));
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
      weightsRegister));
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
      weightsRegister));
    c_mIdxToStrideInputBufferAlongW += 56;
  }

  vst1q_f32(&outputBufferPtr[0], biasRegister);
  vst1q_f32(&outputBufferPtr[4], outputRegister);
  vst1q_f32(&outputBufferPtr[8], b_outputRegister);
  vst1q_f32(&outputBufferPtr[12], c_outputRegister);
  vst1q_f32(&outputBufferPtr[16], d_outputRegister);
  vst1q_f32(&outputBufferPtr[20], e_outputRegister);
  vst1q_f32(&outputBufferPtr[24], f_outputRegister);
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weightsTensor
 *                const float *biasTensor
 * Return Type  : void
 */
static void f_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor)
{
  int c_fusedOutputWidthAndChannelBlo;
  int c_numInputChannelMiniblocksPerB;
  int inputChannelBlockIdx;
  int inputChannelMiniblockIdx;
  int outputBufferIdx;
  int outputBufferIdx_tmp;
  int outputChannelBlockIdx;
  int weightsIdx;
  bool outputChannelTailCase;
  for (inputChannelBlockIdx = 0; inputChannelBlockIdx < 4; inputChannelBlockIdx
       ++) {
    int inputChannelBlockIdxOffset;
    int inputScratchpadBufferBaseIdx;
    inputChannelBlockIdxOffset = inputChannelBlockIdx << 7;
    inputScratchpadBufferBaseIdx = inputChannelBlockIdx * 25088;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,outputBufferIdx_tmp,outputBufferIdx,weightsIdx,c_numInputChannelMiniblocksPerB,outputChannelTailCase,inputChannelMiniblockIdx)

    for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
         280; c_fusedOutputWidthAndChannelBlo++) {
      outputChannelBlockIdx = (int)((unsigned int)
        c_fusedOutputWidthAndChannelBlo / 28U);
      outputBufferIdx_tmp = c_fusedOutputWidthAndChannelBlo % 28 * 112;
      outputBufferIdx = outputBufferIdx_tmp + outputChannelBlockIdx * 9408;
      weightsIdx = outputChannelBlockIdx * 1392 + inputChannelBlockIdxOffset;
      outputBufferIdx_tmp += inputScratchpadBufferBaseIdx;
      if (inputChannelBlockIdx == 3) {
        c_numInputChannelMiniblocksPerB = 4;
      } else {
        c_numInputChannelMiniblocksPerB = 7;
      }

      outputChannelTailCase = (outputChannelBlockIdx == 9);
      for (inputChannelMiniblockIdx = 0; inputChannelMiniblockIdx <=
           c_numInputChannelMiniblocksPerB; inputChannelMiniblockIdx++) {
        b_convolutionKernel(&inputTensor[outputBufferIdx_tmp +
                            inputChannelMiniblockIdx * 3136],
                            &outputTensor[outputBufferIdx],
                            &weightsTensor[weightsIdx +
                            (inputChannelMiniblockIdx << 4)],
                            outputChannelTailCase, (inputChannelBlockIdx == 0) &&
                            (inputChannelMiniblockIdx == 0),
                            (inputChannelBlockIdx == 3) &&
                            (inputChannelMiniblockIdx == 4),
                            &biasTensor[outputChannelBlockIdx * 12]);
      }
    }
  }
}

/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                const float *weightsBufferPtr
 *                const float *biasBufferPtr
 * Return Type  : void
 */
static void f_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, const float *biasBufferPtr)
{
  float32x4_t b_outputRegister;
  float32x4_t d_outputRegister;
  float32x4_t inputRegister0_0;
  float32x4_t outputRegister;
  float32x4_t reluZero;
  int c_idxToStrideInputBufferAlongFi;
  int c_idxToStrideInputBufferAlongHe;
  int c_idxToStrideInputBufferAlongWi;
  int kernelHeightIdx;
  int kernelWidthIdx;
  int outputHeightBlockIdx;
  reluZero = vdupq_n_f32(0.0F);
  c_idxToStrideInputBufferAlongHe = 0;
  for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 37; outputHeightBlockIdx
       ++) {
    float32x4_t c_outputRegister;
    float32x4_t e_outputRegister;
    float32x4_t f_outputRegister;
    float32x4_t g_outputRegister;
    float32x4_t h_outputRegister;
    float32x4_t i_outputRegister;
    outputRegister = vld1q_f32(&biasBufferPtr[0]);
    c_outputRegister = vld1q_f32(&biasBufferPtr[0]);
    e_outputRegister = vld1q_f32(&biasBufferPtr[0]);
    b_outputRegister = vld1q_f32(&biasBufferPtr[4]);
    f_outputRegister = vld1q_f32(&biasBufferPtr[4]);
    g_outputRegister = vld1q_f32(&biasBufferPtr[4]);
    d_outputRegister = vld1q_f32(&biasBufferPtr[8]);
    h_outputRegister = vld1q_f32(&biasBufferPtr[8]);
    i_outputRegister = vld1q_f32(&biasBufferPtr[8]);
    c_idxToStrideInputBufferAlongWi = c_idxToStrideInputBufferAlongHe;
    for (kernelWidthIdx = 0; kernelWidthIdx < 3; kernelWidthIdx++) {
      c_idxToStrideInputBufferAlongFi = c_idxToStrideInputBufferAlongWi;
      for (kernelHeightIdx = 0; kernelHeightIdx < 3; kernelHeightIdx++) {
        float32x4_t inputRegister0_1;
        float32x4_t inputRegister0_2;
        float32x4_t weightsRegister;
        int weightsRegister_tmp;
        inputRegister0_0 = vdupq_n_f32
          (inputBufferPtr[c_idxToStrideInputBufferAlongFi]);
        inputRegister0_1 = vdupq_n_f32
          (inputBufferPtr[c_idxToStrideInputBufferAlongFi + 6]);
        inputRegister0_2 = vdupq_n_f32
          (inputBufferPtr[c_idxToStrideInputBufferAlongFi + 12]);
        weightsRegister_tmp = kernelWidthIdx * 36 + kernelHeightIdx * 12;
        weightsRegister = vld1q_f32(&weightsBufferPtr[weightsRegister_tmp]);
        outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
          weightsRegister));
        c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32
          (inputRegister0_1, weightsRegister));
        e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32
          (inputRegister0_2, weightsRegister));
        weightsRegister = vld1q_f32(&weightsBufferPtr[weightsRegister_tmp + 108]);
        b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32
          (inputRegister0_0, weightsRegister));
        f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32
          (inputRegister0_1, weightsRegister));
        g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32
          (inputRegister0_2, weightsRegister));
        weightsRegister = vld1q_f32(&weightsBufferPtr[weightsRegister_tmp + 216]);
        d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32
          (inputRegister0_0, weightsRegister));
        h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32
          (inputRegister0_1, weightsRegister));
        i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32
          (inputRegister0_2, weightsRegister));
        inputRegister0_0 = vdupq_n_f32
          (inputBufferPtr[c_idxToStrideInputBufferAlongFi + 1]);
        inputRegister0_1 = vdupq_n_f32
          (inputBufferPtr[c_idxToStrideInputBufferAlongFi + 7]);
        inputRegister0_2 = vdupq_n_f32
          (inputBufferPtr[c_idxToStrideInputBufferAlongFi + 13]);
        weightsRegister = vld1q_f32(&weightsBufferPtr[weightsRegister_tmp + 4]);
        outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
          weightsRegister));
        c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32
          (inputRegister0_1, weightsRegister));
        e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32
          (inputRegister0_2, weightsRegister));
        weightsRegister = vld1q_f32(&weightsBufferPtr[weightsRegister_tmp + 112]);
        b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32
          (inputRegister0_0, weightsRegister));
        f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32
          (inputRegister0_1, weightsRegister));
        g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32
          (inputRegister0_2, weightsRegister));
        weightsRegister = vld1q_f32(&weightsBufferPtr[weightsRegister_tmp + 220]);
        d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32
          (inputRegister0_0, weightsRegister));
        h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32
          (inputRegister0_1, weightsRegister));
        i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32
          (inputRegister0_2, weightsRegister));
        inputRegister0_0 = vdupq_n_f32
          (inputBufferPtr[c_idxToStrideInputBufferAlongFi + 2]);
        inputRegister0_1 = vdupq_n_f32
          (inputBufferPtr[c_idxToStrideInputBufferAlongFi + 8]);
        inputRegister0_2 = vdupq_n_f32
          (inputBufferPtr[c_idxToStrideInputBufferAlongFi + 14]);
        weightsRegister = vld1q_f32(&weightsBufferPtr[weightsRegister_tmp + 8]);
        outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
          weightsRegister));
        c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32
          (inputRegister0_1, weightsRegister));
        e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32
          (inputRegister0_2, weightsRegister));
        weightsRegister = vld1q_f32(&weightsBufferPtr[weightsRegister_tmp + 116]);
        b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32
          (inputRegister0_0, weightsRegister));
        f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32
          (inputRegister0_1, weightsRegister));
        g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32
          (inputRegister0_2, weightsRegister));
        weightsRegister = vld1q_f32(&weightsBufferPtr[weightsRegister_tmp + 224]);
        d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32
          (inputRegister0_0, weightsRegister));
        h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32
          (inputRegister0_1, weightsRegister));
        i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32
          (inputRegister0_2, weightsRegister));
        c_idxToStrideInputBufferAlongFi += 3;
      }

      c_idxToStrideInputBufferAlongWi += 678;
    }

    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], vmaxq_f32
              (outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4], vmaxq_f32
              (c_outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8], vmaxq_f32
              (e_outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 50176], vmaxq_f32
              (b_outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 50180], vmaxq_f32
              (f_outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 50184], vmaxq_f32
              (g_outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 100352], vmaxq_f32
              (d_outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 100356], vmaxq_f32
              (h_outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 100360], vmaxq_f32
              (i_outputRegister, reluZero));
    c_idxToStrideInputBufferAlongHe += 18;
  }

  outputRegister = vld1q_f32(&biasBufferPtr[0]);
  b_outputRegister = vld1q_f32(&biasBufferPtr[4]);
  d_outputRegister = vld1q_f32(&biasBufferPtr[8]);
  c_idxToStrideInputBufferAlongWi = c_idxToStrideInputBufferAlongHe;
  for (kernelWidthIdx = 0; kernelWidthIdx < 3; kernelWidthIdx++) {
    c_idxToStrideInputBufferAlongFi = c_idxToStrideInputBufferAlongWi;
    for (kernelHeightIdx = 0; kernelHeightIdx < 3; kernelHeightIdx++) {
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongFi]);
      c_idxToStrideInputBufferAlongHe = kernelWidthIdx * 36 + kernelHeightIdx *
        12;
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        vld1q_f32(&weightsBufferPtr[c_idxToStrideInputBufferAlongHe])));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
        vld1q_f32(&weightsBufferPtr[c_idxToStrideInputBufferAlongHe + 108])));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
        vld1q_f32(&weightsBufferPtr[c_idxToStrideInputBufferAlongHe + 216])));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongFi + 1]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        vld1q_f32(&weightsBufferPtr[c_idxToStrideInputBufferAlongHe + 4])));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
        vld1q_f32(&weightsBufferPtr[c_idxToStrideInputBufferAlongHe + 112])));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
        vld1q_f32(&weightsBufferPtr[c_idxToStrideInputBufferAlongHe + 220])));
      inputRegister0_0 = vdupq_n_f32
        (inputBufferPtr[c_idxToStrideInputBufferAlongFi + 2]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
        vld1q_f32(&weightsBufferPtr[c_idxToStrideInputBufferAlongHe + 8])));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
        vld1q_f32(&weightsBufferPtr[c_idxToStrideInputBufferAlongHe + 116])));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
        vld1q_f32(&weightsBufferPtr[c_idxToStrideInputBufferAlongHe + 224])));
      c_idxToStrideInputBufferAlongFi += 3;
    }

    c_idxToStrideInputBufferAlongWi += 678;
  }

  vst1q_f32(&outputBufferPtr[444], vmaxq_f32(outputRegister, reluZero));
  vst1q_f32(&outputBufferPtr[50620], vmaxq_f32(b_outputRegister, reluZero));
  vst1q_f32(&outputBufferPtr[100796], vmaxq_f32(d_outputRegister, reluZero));
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weights
 *                const float *bias
 * Return Type  : void
 */
static void f_groupedConvolution(const float *inputTensor, float *outputTensor,
  const float *weights, const float *bias)
{
  int c_fusedOutputWidthAndChannelBlo;
  int outputChannelBlockIdx;
  int outputWidthIdx;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,outputWidthIdx)

  for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
       406; c_fusedOutputWidthAndChannelBlo++) {
    outputChannelBlockIdx = (int)((unsigned int)c_fusedOutputWidthAndChannelBlo /
      7U);
    outputWidthIdx = c_fusedOutputWidthAndChannelBlo % 7;
    e_groupedConvolutionKernel(&inputTensor[outputChannelBlockIdx * 784],
      &outputTensor[outputWidthIdx * 28 + outputChannelBlockIdx * 196],
      &weights[outputChannelBlockIdx * 36], outputWidthIdx, ((outputWidthIdx <<
      1) - 1) * 56 - 4, &bias[outputChannelBlockIdx << 2]);
  }
}

/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                const float *weightsBufferPtr
 *                int convOutputWidthIdx
 *                int c_startIdxWithPaddingOffsetInpu
 *                const float *biasBufferPtr
 * Return Type  : void
 */
static void f_groupedConvolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, int convOutputWidthIdx, int
  c_startIdxWithPaddingOffsetInpu, const float *biasBufferPtr)
{
  float32x4_t b_outputRegister;
  float32x4_t biasRegister;
  float32x4_t c_outputRegister;
  float32x4_t d_outputRegister;
  float32x4_t e_outputRegister;
  float32x4_t f_outputRegister;
  float32x4_t inputRegister_tmp_tmp;
  float32x4_t outputRegister;
  int c_mIdxToStrideInputBufferAlongW;
  int kernelWidthIdx;
  biasRegister = vld1q_f32(&biasBufferPtr[0]);
  c_mIdxToStrideInputBufferAlongW = c_startIdxWithPaddingOffsetInpu;
  outputRegister = biasRegister;
  b_outputRegister = biasRegister;
  c_outputRegister = biasRegister;
  d_outputRegister = biasRegister;
  e_outputRegister = biasRegister;
  f_outputRegister = biasRegister;
  inputRegister_tmp_tmp = vdupq_n_f32(0.0F);
  for (kernelWidthIdx = 0; kernelWidthIdx < 3; kernelWidthIdx++) {
    float32x4_t b_inputRegister;
    float32x4_t c_inputRegister;
    float32x4_t d_inputRegister;
    float32x4_t e_inputRegister;
    float32x4_t f_inputRegister;
    float32x4_t g_inputRegister;
    float32x4_t inputRegister;
    float32x4_t weightsRegister;
    int leftPaddingBound;
    bool b;
    leftPaddingBound = (convOutputWidthIdx + kernelWidthIdx) - 1;
    b = ((leftPaddingBound >= 0) && (leftPaddingBound < 7));
    if (b) {
      inputRegister = vld1q_f32(&inputBufferPtr[c_mIdxToStrideInputBufferAlongW
        + 4]);
      b_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 8]);
      c_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 12]);
      d_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 16]);
      e_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 20]);
      f_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 24]);
    } else {
      inputRegister = inputRegister_tmp_tmp;
      b_inputRegister = inputRegister_tmp_tmp;
      c_inputRegister = inputRegister_tmp_tmp;
      d_inputRegister = inputRegister_tmp_tmp;
      e_inputRegister = inputRegister_tmp_tmp;
      f_inputRegister = inputRegister_tmp_tmp;
    }

    weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12]);
    biasRegister = vaddq_f32(biasRegister, vmulq_f32(inputRegister_tmp_tmp,
      weightsRegister));
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
      weightsRegister));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
      weightsRegister));
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
      weightsRegister));
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
      weightsRegister));
    if (b) {
      g_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 4]);
      inputRegister = vld1q_f32(&inputBufferPtr[c_mIdxToStrideInputBufferAlongW
        + 8]);
      b_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 12]);
      c_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 16]);
      d_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 20]);
      e_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 24]);
      f_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 28]);
    } else {
      g_inputRegister = inputRegister_tmp_tmp;
      inputRegister = inputRegister_tmp_tmp;
      b_inputRegister = inputRegister_tmp_tmp;
      c_inputRegister = inputRegister_tmp_tmp;
      d_inputRegister = inputRegister_tmp_tmp;
      e_inputRegister = inputRegister_tmp_tmp;
      f_inputRegister = inputRegister_tmp_tmp;
    }

    weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12 + 4]);
    biasRegister = vaddq_f32(biasRegister, vmulq_f32(g_inputRegister,
      weightsRegister));
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
      weightsRegister));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
      weightsRegister));
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
      weightsRegister));
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
      weightsRegister));
    if (b) {
      g_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 8]);
      inputRegister = vld1q_f32(&inputBufferPtr[c_mIdxToStrideInputBufferAlongW
        + 12]);
      b_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 16]);
      c_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 20]);
      d_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 24]);
      e_inputRegister = vld1q_f32
        (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 28]);
    } else {
      g_inputRegister = inputRegister_tmp_tmp;
      inputRegister = inputRegister_tmp_tmp;
      b_inputRegister = inputRegister_tmp_tmp;
      c_inputRegister = inputRegister_tmp_tmp;
      d_inputRegister = inputRegister_tmp_tmp;
      e_inputRegister = inputRegister_tmp_tmp;
    }

    weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12 + 8]);
    biasRegister = vaddq_f32(biasRegister, vmulq_f32(g_inputRegister,
      weightsRegister));
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
      weightsRegister));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
      weightsRegister));
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
      weightsRegister));
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32
      (inputRegister_tmp_tmp, weightsRegister));
    c_mIdxToStrideInputBufferAlongW += 28;
  }

  vst1q_f32(&outputBufferPtr[0], biasRegister);
  vst1q_f32(&outputBufferPtr[4], outputRegister);
  vst1q_f32(&outputBufferPtr[8], b_outputRegister);
  vst1q_f32(&outputBufferPtr[12], c_outputRegister);
  vst1q_f32(&outputBufferPtr[16], d_outputRegister);
  vst1q_f32(&outputBufferPtr[20], e_outputRegister);
  vst1q_f32(&outputBufferPtr[24], f_outputRegister);
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weightsTensor
 *                const float *biasTensor
 * Return Type  : void
 */
static void g_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor)
{
  int c_fusedOutputWidthAndChannelBlo;
  int c_numInputChannelMiniblocksPerB;
  int inputChannelBlockIdx;
  int inputChannelMiniblockIdx;
  int outputBufferIdx;
  int outputBufferIdx_tmp;
  int outputChannelBlockIdx;
  int weightsIdx;
  bool outputChannelTailCase;
  for (inputChannelBlockIdx = 0; inputChannelBlockIdx < 4; inputChannelBlockIdx
       ++) {
    int inputChannelBlockIdxOffset;
    int inputScratchpadBufferBaseIdx;
    inputChannelBlockIdxOffset = inputChannelBlockIdx * 240;
    inputScratchpadBufferBaseIdx = inputChannelBlockIdx * 2940;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,outputBufferIdx_tmp,outputBufferIdx,weightsIdx,c_numInputChannelMiniblocksPerB,outputChannelTailCase,inputChannelMiniblockIdx)

    for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
         140; c_fusedOutputWidthAndChannelBlo++) {
      outputChannelBlockIdx = (int)((unsigned int)
        c_fusedOutputWidthAndChannelBlo / 7U);
      outputBufferIdx_tmp = c_fusedOutputWidthAndChannelBlo % 7 * 28;
      outputBufferIdx = outputBufferIdx_tmp + outputChannelBlockIdx * 588;
      weightsIdx = outputChannelBlockIdx * 2784 + inputChannelBlockIdxOffset;
      outputBufferIdx_tmp += inputScratchpadBufferBaseIdx;
      if (inputChannelBlockIdx == 3) {
        c_numInputChannelMiniblocksPerB = 12;
      } else {
        c_numInputChannelMiniblocksPerB = 14;
      }

      outputChannelTailCase = (outputChannelBlockIdx == 19);
      for (inputChannelMiniblockIdx = 0; inputChannelMiniblockIdx <=
           c_numInputChannelMiniblocksPerB; inputChannelMiniblockIdx++) {
        c_convolutionKernel(&inputTensor[outputBufferIdx_tmp +
                            inputChannelMiniblockIdx * 196],
                            &outputTensor[outputBufferIdx],
                            &weightsTensor[weightsIdx +
                            (inputChannelMiniblockIdx << 4)],
                            outputChannelTailCase, (inputChannelBlockIdx == 0) &&
                            (inputChannelMiniblockIdx == 0),
                            (inputChannelBlockIdx == 3) &&
                            (inputChannelMiniblockIdx == 12),
                            &biasTensor[outputChannelBlockIdx * 12]);
      }
    }
  }
}

/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                const float *weightsBufferPtr
 *                bool c_canInitializeOutputRegistersW
 *                bool canApplyActivationOperation
 *                const float *biasBufferPtr
 * Return Type  : void
 */
static void g_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool
  c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const float
  *biasBufferPtr)
{
  float32x4_t b_outputRegister;
  float32x4_t d_outputRegister;
  float32x4_t inputRegister0_0;
  float32x4_t outputRegister;
  float32x4_t reluZero;
  int c_idxToStrideInputBufferAlongHe;
  int outputHeightBlockIdx;
  reluZero = vdupq_n_f32(0.0F);
  c_idxToStrideInputBufferAlongHe = 0;
  for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 9; outputHeightBlockIdx
       ++) {
    float32x4_t c_outputRegister;
    float32x4_t e_outputRegister;
    float32x4_t f_outputRegister;
    float32x4_t g_outputRegister;
    float32x4_t h_outputRegister;
    float32x4_t i_outputRegister;
    float32x4_t inputRegister0_1;
    float32x4_t inputRegister0_2;
    float32x4_t weightsRegister;
    if (c_canInitializeOutputRegistersW) {
      outputRegister = vld1q_f32(&biasBufferPtr[0]);
      c_outputRegister = vld1q_f32(&biasBufferPtr[0]);
      e_outputRegister = vld1q_f32(&biasBufferPtr[0]);
      b_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      f_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      g_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      d_outputRegister = vld1q_f32(&biasBufferPtr[8]);
      h_outputRegister = vld1q_f32(&biasBufferPtr[8]);
      i_outputRegister = vld1q_f32(&biasBufferPtr[8]);
    } else {
      outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12]);
      c_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        4]);
      e_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        8]);
      b_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        3136]);
      f_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        3140]);
      g_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        3144]);
      d_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        6272]);
      h_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        6276]);
      i_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        6280]);
    }

    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]);
    inputRegister0_2 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 8]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[96]);
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[192]);
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]);
    inputRegister0_2 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 9]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[100]);
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[196]);
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]);
    inputRegister0_2 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 10]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[104]);
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[200]);
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]);
    inputRegister0_2 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 11]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[108]);
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[204]);
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    if (canApplyActivationOperation) {
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], vmaxq_f32
                (outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4], vmaxq_f32
                (c_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8], vmaxq_f32
                (e_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3136], vmaxq_f32
                (b_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3140], vmaxq_f32
                (f_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3144], vmaxq_f32
                (g_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6272], vmaxq_f32
                (d_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6276], vmaxq_f32
                (h_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6280], vmaxq_f32
                (i_outputRegister, reluZero));
    } else {
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4],
                c_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8],
                e_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3136],
                b_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3140],
                f_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3144],
                g_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6272],
                d_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6276],
                h_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6280],
                i_outputRegister);
    }

    c_idxToStrideInputBufferAlongHe += 12;
  }

  if (c_canInitializeOutputRegistersW) {
    outputRegister = vld1q_f32(&biasBufferPtr[0]);
    b_outputRegister = vld1q_f32(&biasBufferPtr[4]);
    d_outputRegister = vld1q_f32(&biasBufferPtr[8]);
  } else {
    outputRegister = vld1q_f32(&outputBufferPtr[108]);
    b_outputRegister = vld1q_f32(&outputBufferPtr[3244]);
    d_outputRegister = vld1q_f32(&outputBufferPtr[6380]);
  }

  inputRegister0_0 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
  outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[0])));
  b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[96])));
  d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[192])));
  inputRegister0_0 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe
    + 1]);
  outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[4])));
  b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[100])));
  d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[196])));
  inputRegister0_0 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe
    + 2]);
  outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[8])));
  b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[104])));
  d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[200])));
  inputRegister0_0 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe
    + 3]);
  outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[12])));
  b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[108])));
  d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[204])));
  if (canApplyActivationOperation) {
    vst1q_f32(&outputBufferPtr[108], vmaxq_f32(outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[3244], vmaxq_f32(b_outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[6380], vmaxq_f32(d_outputRegister, reluZero));
  } else {
    vst1q_f32(&outputBufferPtr[108], outputRegister);
    vst1q_f32(&outputBufferPtr[3244], b_outputRegister);
    vst1q_f32(&outputBufferPtr[6380], d_outputRegister);
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weights
 *                const float *bias
 * Return Type  : void
 */
static void g_groupedConvolution(const float *inputTensor, float *outputTensor,
  const float *weights, const float *bias)
{
  int c_fusedOutputWidthAndChannelBlo;
  int outputChannelBlockIdx;
  int outputWidthIdx;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,outputWidthIdx)

  for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
       406; c_fusedOutputWidthAndChannelBlo++) {
    outputChannelBlockIdx = (int)((unsigned int)c_fusedOutputWidthAndChannelBlo /
      7U);
    outputWidthIdx = c_fusedOutputWidthAndChannelBlo % 7;
    f_groupedConvolutionKernel(&inputTensor[outputChannelBlockIdx * 196],
      &outputTensor[outputWidthIdx * 28 + outputChannelBlockIdx * 196],
      &weights[outputChannelBlockIdx * 36], outputWidthIdx, (outputWidthIdx - 1)
      * 28 - 4, &bias[outputChannelBlockIdx << 2]);
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weights
 *                const float *bias
 * Return Type  : void
 */
static void groupedConvolution(const float *inputTensor, float *outputTensor,
  const float *weights, const float *bias)
{
  int c_fusedOutputWidthAndChannelBlo;
  int outputChannelBlockIdx;
  int outputWidthIdx;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,outputWidthIdx)

  for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
       168; c_fusedOutputWidthAndChannelBlo++) {
    outputChannelBlockIdx = (int)((unsigned int)c_fusedOutputWidthAndChannelBlo /
      28U);
    outputWidthIdx = c_fusedOutputWidthAndChannelBlo % 28;
    groupedConvolutionKernel(&inputTensor[outputChannelBlockIdx * 12544],
      &outputTensor[outputWidthIdx * 112 + outputChannelBlockIdx * 3136],
      &weights[outputChannelBlockIdx * 36], outputWidthIdx, ((outputWidthIdx <<
      1) - 1) * 224 - 4, &bias[outputChannelBlockIdx << 2]);
  }
}

/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                const float *weightsBufferPtr
 *                int convOutputWidthIdx
 *                int c_startIdxWithPaddingOffsetInpu
 *                const float *biasBufferPtr
 * Return Type  : void
 */
static void groupedConvolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, int convOutputWidthIdx, int
  c_startIdxWithPaddingOffsetInpu, const float *biasBufferPtr)
{
  float32x4_t biasRegister;
  int c_mIdxToStrideInputBufferAlongH;
  int kernelWidthIdx;
  int mOutputHeightIdx;
  int outputHeightBlockIdx;
  biasRegister = vld1q_f32(&biasBufferPtr[0]);
  c_mIdxToStrideInputBufferAlongH = c_startIdxWithPaddingOffsetInpu;
  mOutputHeightIdx = 0;
  for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 4; outputHeightBlockIdx
       ++) {
    float32x4_t b_outputRegister;
    float32x4_t c_outputRegister;
    float32x4_t d_outputRegister;
    float32x4_t e_outputRegister;
    float32x4_t f_outputRegister;
    float32x4_t g_outputRegister;
    float32x4_t outputRegister;
    int b_topPaddingBound_tmp;
    int c_mIdxToStrideInputBufferAlongW;
    int c_topPaddingBound_tmp;
    int d_topPaddingBound_tmp;
    int e_topPaddingBound_tmp;
    int f_topPaddingBound_tmp;
    int g_topPaddingBound_tmp;
    int topPaddingBound_tmp;
    outputRegister = biasRegister;
    b_outputRegister = biasRegister;
    c_outputRegister = biasRegister;
    d_outputRegister = biasRegister;
    e_outputRegister = biasRegister;
    f_outputRegister = biasRegister;
    g_outputRegister = biasRegister;
    c_mIdxToStrideInputBufferAlongW = c_mIdxToStrideInputBufferAlongH;
    topPaddingBound_tmp = mOutputHeightIdx << 1;
    b_topPaddingBound_tmp = (mOutputHeightIdx + 1) << 1;
    c_topPaddingBound_tmp = (mOutputHeightIdx + 2) << 1;
    d_topPaddingBound_tmp = (mOutputHeightIdx + 3) << 1;
    e_topPaddingBound_tmp = (mOutputHeightIdx + 4) << 1;
    f_topPaddingBound_tmp = (mOutputHeightIdx + 5) << 1;
    g_topPaddingBound_tmp = (mOutputHeightIdx + 6) << 1;
    for (kernelWidthIdx = 0; kernelWidthIdx < 3; kernelWidthIdx++) {
      float32x4_t b_inputRegister;
      float32x4_t c_inputRegister;
      float32x4_t d_inputRegister;
      float32x4_t e_inputRegister;
      float32x4_t f_inputRegister;
      float32x4_t g_inputRegister;
      float32x4_t inputRegister;
      float32x4_t weightsRegister;
      int i;
      i = ((convOutputWidthIdx << 1) + kernelWidthIdx) - 1;
      if ((i >= 0) && (topPaddingBound_tmp - 1 >= 0) && (topPaddingBound_tmp - 1
           < 56)) {
        inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW]);
      } else {
        inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (b_topPaddingBound_tmp - 1 >= 0) && (b_topPaddingBound_tmp
           - 1 < 56)) {
        b_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 8]);
      } else {
        b_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (c_topPaddingBound_tmp - 1 >= 0) && (c_topPaddingBound_tmp
           - 1 < 56)) {
        c_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 16]);
      } else {
        c_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (d_topPaddingBound_tmp - 1 >= 0) && (d_topPaddingBound_tmp
           - 1 < 56)) {
        d_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 24]);
      } else {
        d_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (e_topPaddingBound_tmp - 1 >= 0) && (e_topPaddingBound_tmp
           - 1 < 56)) {
        e_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 32]);
      } else {
        e_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (f_topPaddingBound_tmp - 1 >= 0) && (f_topPaddingBound_tmp
           - 1 < 56)) {
        f_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 40]);
      } else {
        f_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (g_topPaddingBound_tmp - 1 >= 0) && (g_topPaddingBound_tmp
           - 1 < 56)) {
        g_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 48]);
      } else {
        g_inputRegister = vdupq_n_f32(0.0F);
      }

      weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(g_inputRegister,
        weightsRegister));
      if ((i >= 0) && (topPaddingBound_tmp >= 0) && (topPaddingBound_tmp < 56))
      {
        inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 4]);
      } else {
        inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (b_topPaddingBound_tmp >= 0) && (b_topPaddingBound_tmp <
           56)) {
        b_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 12]);
      } else {
        b_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (c_topPaddingBound_tmp >= 0) && (c_topPaddingBound_tmp <
           56)) {
        c_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 20]);
      } else {
        c_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (d_topPaddingBound_tmp >= 0) && (d_topPaddingBound_tmp <
           56)) {
        d_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 28]);
      } else {
        d_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (e_topPaddingBound_tmp >= 0) && (e_topPaddingBound_tmp <
           56)) {
        e_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 36]);
      } else {
        e_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (f_topPaddingBound_tmp >= 0) && (f_topPaddingBound_tmp <
           56)) {
        f_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 44]);
      } else {
        f_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (g_topPaddingBound_tmp >= 0) && (g_topPaddingBound_tmp <
           56)) {
        g_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 52]);
      } else {
        g_inputRegister = vdupq_n_f32(0.0F);
      }

      weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12 + 4]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(g_inputRegister,
        weightsRegister));
      if ((i >= 0) && (topPaddingBound_tmp + 1 >= 0) && (topPaddingBound_tmp + 1
           < 56)) {
        inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 8]);
      } else {
        inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (b_topPaddingBound_tmp + 1 >= 0) && (b_topPaddingBound_tmp
           + 1 < 56)) {
        b_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 16]);
      } else {
        b_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (c_topPaddingBound_tmp + 1 >= 0) && (c_topPaddingBound_tmp
           + 1 < 56)) {
        c_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 24]);
      } else {
        c_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (d_topPaddingBound_tmp + 1 >= 0) && (d_topPaddingBound_tmp
           + 1 < 56)) {
        d_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 32]);
      } else {
        d_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (e_topPaddingBound_tmp + 1 >= 0) && (e_topPaddingBound_tmp
           + 1 < 56)) {
        e_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 40]);
      } else {
        e_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (f_topPaddingBound_tmp + 1 >= 0) && (f_topPaddingBound_tmp
           + 1 < 56)) {
        f_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 48]);
      } else {
        f_inputRegister = vdupq_n_f32(0.0F);
      }

      if ((i >= 0) && (g_topPaddingBound_tmp + 1 >= 0) && (g_topPaddingBound_tmp
           + 1 < 56)) {
        g_inputRegister = vld1q_f32
          (&inputBufferPtr[c_mIdxToStrideInputBufferAlongW + 56]);
      } else {
        g_inputRegister = vdupq_n_f32(0.0F);
      }

      weightsRegister = vld1q_f32(&weightsBufferPtr[kernelWidthIdx * 12 + 8]);
      outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister,
        weightsRegister));
      b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(b_inputRegister,
        weightsRegister));
      c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(c_inputRegister,
        weightsRegister));
      d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(d_inputRegister,
        weightsRegister));
      e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(e_inputRegister,
        weightsRegister));
      f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(f_inputRegister,
        weightsRegister));
      g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(g_inputRegister,
        weightsRegister));
      c_mIdxToStrideInputBufferAlongW += 224;
    }

    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28], outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 4], b_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 8], c_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 12], d_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 16], e_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 20], f_outputRegister);
    vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 28 + 24], g_outputRegister);
    c_mIdxToStrideInputBufferAlongH += 56;
    mOutputHeightIdx += 7;
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weightsTensor
 *                const float *biasTensor
 * Return Type  : void
 */
static void h_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor)
{
  int c_fusedOutputWidthAndChannelBlo;
  int c_numInputChannelMiniblocksPerB;
  int inputChannelBlockIdx;
  int inputChannelMiniblockIdx;
  int outputBufferIdx;
  int outputBufferIdx_tmp;
  int outputChannelBlockIdx;
  int weightsIdx;
  bool outputChannelTailCase;
  for (inputChannelBlockIdx = 0; inputChannelBlockIdx < 4; inputChannelBlockIdx
       ++) {
    int inputChannelBlockIdxOffset;
    int inputScratchpadBufferBaseIdx;
    inputChannelBlockIdxOffset = inputChannelBlockIdx * 240;
    inputScratchpadBufferBaseIdx = inputChannelBlockIdx * 11760;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,outputBufferIdx_tmp,outputBufferIdx,weightsIdx,c_numInputChannelMiniblocksPerB,outputChannelTailCase,inputChannelMiniblockIdx)

    for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
         280; c_fusedOutputWidthAndChannelBlo++) {
      outputChannelBlockIdx = (int)((unsigned int)
        c_fusedOutputWidthAndChannelBlo / 14U);
      outputBufferIdx_tmp = c_fusedOutputWidthAndChannelBlo % 14 * 56;
      outputBufferIdx = outputBufferIdx_tmp + outputChannelBlockIdx * 2352;
      weightsIdx = outputChannelBlockIdx * 2784 + inputChannelBlockIdxOffset;
      outputBufferIdx_tmp += inputScratchpadBufferBaseIdx;
      if (inputChannelBlockIdx == 3) {
        c_numInputChannelMiniblocksPerB = 12;
      } else {
        c_numInputChannelMiniblocksPerB = 14;
      }

      outputChannelTailCase = (outputChannelBlockIdx == 19);
      for (inputChannelMiniblockIdx = 0; inputChannelMiniblockIdx <=
           c_numInputChannelMiniblocksPerB; inputChannelMiniblockIdx++) {
        d_convolutionKernel(&inputTensor[outputBufferIdx_tmp +
                            inputChannelMiniblockIdx * 784],
                            &outputTensor[outputBufferIdx],
                            &weightsTensor[weightsIdx +
                            (inputChannelMiniblockIdx << 4)],
                            outputChannelTailCase, (inputChannelBlockIdx == 0) &&
                            (inputChannelMiniblockIdx == 0),
                            (inputChannelBlockIdx == 3) &&
                            (inputChannelMiniblockIdx == 12),
                            &biasTensor[outputChannelBlockIdx * 12]);
      }
    }
  }
}

/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                const float *weightsBufferPtr
 *                bool c_canInitializeOutputRegistersW
 *                bool canApplyActivationOperation
 *                const float *biasBufferPtr
 * Return Type  : void
 */
static void h_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool
  c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const float
  *biasBufferPtr)
{
  float32x4_t b_outputRegister;
  float32x4_t c_outputRegister;
  float32x4_t e_outputRegister;
  float32x4_t f_outputRegister;
  float32x4_t g_outputRegister;
  float32x4_t inputRegister0_0;
  float32x4_t inputRegister0_1;
  float32x4_t outputRegister;
  float32x4_t reluZero;
  float32x4_t weightsRegister;
  int c_idxToStrideInputBufferAlongHe;
  int outputHeightBlockIdx;
  reluZero = vdupq_n_f32(0.0F);
  c_idxToStrideInputBufferAlongHe = 0;
  for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 18; outputHeightBlockIdx
       ++) {
    float32x4_t d_outputRegister;
    float32x4_t h_outputRegister;
    float32x4_t i_outputRegister;
    float32x4_t inputRegister0_2;
    if (c_canInitializeOutputRegistersW) {
      outputRegister = vld1q_f32(&biasBufferPtr[0]);
      b_outputRegister = vld1q_f32(&biasBufferPtr[0]);
      d_outputRegister = vld1q_f32(&biasBufferPtr[0]);
      c_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      e_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      h_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      f_outputRegister = vld1q_f32(&biasBufferPtr[8]);
      g_outputRegister = vld1q_f32(&biasBufferPtr[8]);
      i_outputRegister = vld1q_f32(&biasBufferPtr[8]);
    } else {
      outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12]);
      b_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        4]);
      d_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        8]);
      c_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        12544]);
      e_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        12548]);
      h_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        12552]);
      f_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        25088]);
      g_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        25092]);
      i_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        25096]);
    }

    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]);
    inputRegister0_2 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 8]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[96]);
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[192]);
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]);
    inputRegister0_2 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 9]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[100]);
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[196]);
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]);
    inputRegister0_2 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 10]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[104]);
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[200]);
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]);
    inputRegister0_2 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 11]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[108]);
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[204]);
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    if (canApplyActivationOperation) {
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], vmaxq_f32
                (outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4], vmaxq_f32
                (b_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8], vmaxq_f32
                (d_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 12544], vmaxq_f32
                (c_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 12548], vmaxq_f32
                (e_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 12552], vmaxq_f32
                (h_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 25088], vmaxq_f32
                (f_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 25092], vmaxq_f32
                (g_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 25096], vmaxq_f32
                (i_outputRegister, reluZero));
    } else {
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4],
                b_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8],
                d_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 12544],
                c_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 12548],
                e_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 12552],
                h_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 25088],
                f_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 25092],
                g_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 25096],
                i_outputRegister);
    }

    c_idxToStrideInputBufferAlongHe += 12;
  }

  if (c_canInitializeOutputRegistersW) {
    outputRegister = vld1q_f32(&biasBufferPtr[0]);
    b_outputRegister = vld1q_f32(&biasBufferPtr[0]);
    c_outputRegister = vld1q_f32(&biasBufferPtr[4]);
    e_outputRegister = vld1q_f32(&biasBufferPtr[4]);
    f_outputRegister = vld1q_f32(&biasBufferPtr[8]);
    g_outputRegister = vld1q_f32(&biasBufferPtr[8]);
  } else {
    outputRegister = vld1q_f32(&outputBufferPtr[216]);
    b_outputRegister = vld1q_f32(&outputBufferPtr[220]);
    c_outputRegister = vld1q_f32(&outputBufferPtr[12760]);
    e_outputRegister = vld1q_f32(&outputBufferPtr[12764]);
    f_outputRegister = vld1q_f32(&outputBufferPtr[25304]);
    g_outputRegister = vld1q_f32(&outputBufferPtr[25308]);
  }

  inputRegister0_0 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
  inputRegister0_1 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe
    + 4]);
  weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
  outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
    weightsRegister));
  b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
    weightsRegister));
  weightsRegister = vld1q_f32(&weightsBufferPtr[96]);
  c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
    weightsRegister));
  e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
    weightsRegister));
  weightsRegister = vld1q_f32(&weightsBufferPtr[192]);
  f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
    weightsRegister));
  g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
    weightsRegister));
  inputRegister0_0 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe
    + 1]);
  inputRegister0_1 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe
    + 5]);
  weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
  outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
    weightsRegister));
  b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
    weightsRegister));
  weightsRegister = vld1q_f32(&weightsBufferPtr[100]);
  c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
    weightsRegister));
  e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
    weightsRegister));
  weightsRegister = vld1q_f32(&weightsBufferPtr[196]);
  f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
    weightsRegister));
  g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
    weightsRegister));
  inputRegister0_0 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe
    + 2]);
  inputRegister0_1 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe
    + 6]);
  weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
  outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
    weightsRegister));
  b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
    weightsRegister));
  weightsRegister = vld1q_f32(&weightsBufferPtr[104]);
  c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
    weightsRegister));
  e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
    weightsRegister));
  weightsRegister = vld1q_f32(&weightsBufferPtr[200]);
  f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
    weightsRegister));
  g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
    weightsRegister));
  inputRegister0_0 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe
    + 3]);
  inputRegister0_1 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe
    + 7]);
  weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
  outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
    weightsRegister));
  b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_1,
    weightsRegister));
  weightsRegister = vld1q_f32(&weightsBufferPtr[108]);
  c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_0,
    weightsRegister));
  e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_1,
    weightsRegister));
  weightsRegister = vld1q_f32(&weightsBufferPtr[204]);
  f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_0,
    weightsRegister));
  g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_1,
    weightsRegister));
  if (canApplyActivationOperation) {
    vst1q_f32(&outputBufferPtr[216], vmaxq_f32(outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[220], vmaxq_f32(b_outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[12760], vmaxq_f32(c_outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[12764], vmaxq_f32(e_outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[25304], vmaxq_f32(f_outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[25308], vmaxq_f32(g_outputRegister, reluZero));
  } else {
    vst1q_f32(&outputBufferPtr[216], outputRegister);
    vst1q_f32(&outputBufferPtr[220], b_outputRegister);
    vst1q_f32(&outputBufferPtr[12760], c_outputRegister);
    vst1q_f32(&outputBufferPtr[12764], e_outputRegister);
    vst1q_f32(&outputBufferPtr[25304], f_outputRegister);
    vst1q_f32(&outputBufferPtr[25308], g_outputRegister);
  }
}

/*
 * Arguments    : const float *inputTensor
 *                float *outputTensor
 *                const float *weightsTensor
 *                const float *biasTensor
 * Return Type  : void
 */
static void i_convolution(const float *inputTensor, float *outputTensor, const
  float *weightsTensor, const float *biasTensor)
{
  int c_fusedOutputWidthAndChannelBlo;
  int inputChannelBlockIdx;
  int inputChannelMiniblockIdx;
  int outputBufferIdx;
  int outputBufferIdx_tmp;
  int outputChannelBlockIdx;
  int weightsIdx;
  bool outputChannelTailCase;
  for (inputChannelBlockIdx = 0; inputChannelBlockIdx < 4; inputChannelBlockIdx
       ++) {
    int inputChannelBlockIdxOffset;
    int inputScratchpadBufferBaseIdx;
    inputChannelBlockIdxOffset = inputChannelBlockIdx * 464;
    inputScratchpadBufferBaseIdx = inputChannelBlockIdx * 5684;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(outputChannelBlockIdx,outputBufferIdx_tmp,outputBufferIdx,weightsIdx,outputChannelTailCase,inputChannelMiniblockIdx)

    for (c_fusedOutputWidthAndChannelBlo = 0; c_fusedOutputWidthAndChannelBlo <
         602; c_fusedOutputWidthAndChannelBlo++) {
      outputChannelBlockIdx = (int)((unsigned int)
        c_fusedOutputWidthAndChannelBlo / 7U);
      outputBufferIdx_tmp = c_fusedOutputWidthAndChannelBlo % 7 * 28;
      outputBufferIdx = outputBufferIdx_tmp + outputChannelBlockIdx * 588;
      weightsIdx = outputChannelBlockIdx * 5568 + inputChannelBlockIdxOffset;
      outputBufferIdx_tmp += inputScratchpadBufferBaseIdx;
      outputChannelTailCase = (outputChannelBlockIdx == 85);
      for (inputChannelMiniblockIdx = 0; inputChannelMiniblockIdx < 29;
           inputChannelMiniblockIdx++) {
        e_convolutionKernel(&inputTensor[outputBufferIdx_tmp +
                            inputChannelMiniblockIdx * 196],
                            &outputTensor[outputBufferIdx],
                            &weightsTensor[weightsIdx +
                            (inputChannelMiniblockIdx << 4)],
                            outputChannelTailCase, (inputChannelBlockIdx == 0) &&
                            (inputChannelMiniblockIdx == 0),
                            (inputChannelBlockIdx == 3) &&
                            (inputChannelMiniblockIdx == 28),
                            &biasTensor[outputChannelBlockIdx * 12]);
      }
    }
  }
}

/*
 * Arguments    : const float *inputBufferPtr
 *                float *outputBufferPtr
 *                const float *weightsBufferPtr
 *                bool c_canInitializeOutputRegistersW
 *                bool canApplyActivationOperation
 *                const float *biasBufferPtr
 * Return Type  : void
 */
static void i_convolutionKernel(const float *inputBufferPtr, float
  *outputBufferPtr, const float *weightsBufferPtr, bool
  c_canInitializeOutputRegistersW, bool canApplyActivationOperation, const float
  *biasBufferPtr)
{
  float32x4_t b_outputRegister;
  float32x4_t d_outputRegister;
  float32x4_t inputRegister0_0;
  float32x4_t outputRegister;
  float32x4_t reluZero;
  int c_idxToStrideInputBufferAlongHe;
  int outputHeightBlockIdx;
  reluZero = vdupq_n_f32(0.0F);
  c_idxToStrideInputBufferAlongHe = 0;
  for (outputHeightBlockIdx = 0; outputHeightBlockIdx < 9; outputHeightBlockIdx
       ++) {
    float32x4_t c_outputRegister;
    float32x4_t e_outputRegister;
    float32x4_t f_outputRegister;
    float32x4_t g_outputRegister;
    float32x4_t h_outputRegister;
    float32x4_t i_outputRegister;
    float32x4_t inputRegister0_1;
    float32x4_t inputRegister0_2;
    float32x4_t weightsRegister;
    if (c_canInitializeOutputRegistersW) {
      outputRegister = vld1q_f32(&biasBufferPtr[0]);
      c_outputRegister = vld1q_f32(&biasBufferPtr[0]);
      e_outputRegister = vld1q_f32(&biasBufferPtr[0]);
      b_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      f_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      g_outputRegister = vld1q_f32(&biasBufferPtr[4]);
      d_outputRegister = vld1q_f32(&biasBufferPtr[8]);
      h_outputRegister = vld1q_f32(&biasBufferPtr[8]);
      i_outputRegister = vld1q_f32(&biasBufferPtr[8]);
    } else {
      outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12]);
      c_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        4]);
      e_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        8]);
      b_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        3136]);
      f_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        3140]);
      g_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        3144]);
      d_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        6272]);
      h_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        6276]);
      i_outputRegister = vld1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 +
        6280]);
    }

    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 4]);
    inputRegister0_2 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 8]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[0]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[240]);
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[480]);
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 1]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 5]);
    inputRegister0_2 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 9]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[4]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[244]);
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[484]);
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 2]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 6]);
    inputRegister0_2 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 10]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[8]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[248]);
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[488]);
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    inputRegister0_0 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 3]);
    inputRegister0_1 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 7]);
    inputRegister0_2 = vdupq_n_f32
      (inputBufferPtr[c_idxToStrideInputBufferAlongHe + 11]);
    weightsRegister = vld1q_f32(&weightsBufferPtr[12]);
    outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    c_outputRegister = vaddq_f32(c_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    e_outputRegister = vaddq_f32(e_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[252]);
    b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    f_outputRegister = vaddq_f32(f_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    g_outputRegister = vaddq_f32(g_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    weightsRegister = vld1q_f32(&weightsBufferPtr[492]);
    d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
      weightsRegister));
    h_outputRegister = vaddq_f32(h_outputRegister, vmulq_f32(inputRegister0_1,
      weightsRegister));
    i_outputRegister = vaddq_f32(i_outputRegister, vmulq_f32(inputRegister0_2,
      weightsRegister));
    if (canApplyActivationOperation) {
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], vmaxq_f32
                (outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4], vmaxq_f32
                (c_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8], vmaxq_f32
                (e_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3136], vmaxq_f32
                (b_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3140], vmaxq_f32
                (f_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3144], vmaxq_f32
                (g_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6272], vmaxq_f32
                (d_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6276], vmaxq_f32
                (h_outputRegister, reluZero));
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6280], vmaxq_f32
                (i_outputRegister, reluZero));
    } else {
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12], outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 4],
                c_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 8],
                e_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3136],
                b_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3140],
                f_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 3144],
                g_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6272],
                d_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6276],
                h_outputRegister);
      vst1q_f32(&outputBufferPtr[outputHeightBlockIdx * 12 + 6280],
                i_outputRegister);
    }

    c_idxToStrideInputBufferAlongHe += 12;
  }

  if (c_canInitializeOutputRegistersW) {
    outputRegister = vld1q_f32(&biasBufferPtr[0]);
    b_outputRegister = vld1q_f32(&biasBufferPtr[4]);
    d_outputRegister = vld1q_f32(&biasBufferPtr[8]);
  } else {
    outputRegister = vld1q_f32(&outputBufferPtr[108]);
    b_outputRegister = vld1q_f32(&outputBufferPtr[3244]);
    d_outputRegister = vld1q_f32(&outputBufferPtr[6380]);
  }

  inputRegister0_0 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe]);
  outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[0])));
  b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[240])));
  d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[480])));
  inputRegister0_0 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe
    + 1]);
  outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[4])));
  b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[244])));
  d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[484])));
  inputRegister0_0 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe
    + 2]);
  outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[8])));
  b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[248])));
  d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[488])));
  inputRegister0_0 = vdupq_n_f32(inputBufferPtr[c_idxToStrideInputBufferAlongHe
    + 3]);
  outputRegister = vaddq_f32(outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[12])));
  b_outputRegister = vaddq_f32(b_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[252])));
  d_outputRegister = vaddq_f32(d_outputRegister, vmulq_f32(inputRegister0_0,
    vld1q_f32(&weightsBufferPtr[492])));
  if (canApplyActivationOperation) {
    vst1q_f32(&outputBufferPtr[108], vmaxq_f32(outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[3244], vmaxq_f32(b_outputRegister, reluZero));
    vst1q_f32(&outputBufferPtr[6380], vmaxq_f32(d_outputRegister, reluZero));
  } else {
    vst1q_f32(&outputBufferPtr[108], outputRegister);
    vst1q_f32(&outputBufferPtr[3244], b_outputRegister);
    vst1q_f32(&outputBufferPtr[6380], d_outputRegister);
  }
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void ab_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13600108.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13600107.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[11368]
 *                float Z[11368]
 * Return Type  : void
 */
void ac_conv2dDirectOptimizedColMajo(const float X[11368], float Z[11368])
{
  static float reformattedAndTruncatedWeights[2088];
  static float biasReformatted[232];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13606341.bin", 2088);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13606340.bin", 232);
  }

  bufferInitialized = true;
  g_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[75264]
 *                float Z[18816]
 * Return Type  : void
 */
void b_conv2dDirectOptimizedColMajor(const float X[75264], float Z[18816])
{
  static float reformattedAndTruncatedWeights[216];
  static float biasReformatted[24];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13593242.bin", 216);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13593241.bin", 24);
  }

  bufferInitialized = true;
  groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                     &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void bb_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13600346.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13600345.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[11368]
 *                float Z[11368]
 * Return Type  : void
 */
void bc_conv2dDirectOptimizedColMajo(const float X[11368], float Z[11368])
{
  static float reformattedAndTruncatedWeights[53824];
  static float biasReformatted[232];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13606495.bin", 53824);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13606494.bin", 232);
  }

  bufferInitialized = true;
  g_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[18816]
 *                float Z[47040]
 * Return Type  : void
 */
void c_conv2dDirectOptimizedColMajor(const float X[18816], float Z[47040])
{
  static float reformattedAndTruncatedWeights[1440];
  static float biasReformatted[60];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13593396.bin", 1440);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13593395.bin", 60);
  }

  bufferInitialized = true;
  b_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void cb_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[1044];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13600584.bin", 1044);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13600583.bin", 116);
  }

  bufferInitialized = true;
  e_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[11368]
 *                float Z[11368]
 * Return Type  : void
 */
void cc_conv2dDirectOptimizedColMajo(const float X[11368], float Z[11368])
{
  static float reformattedAndTruncatedWeights[53824];
  static float biasReformatted[232];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13606733.bin", 53824);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13606732.bin", 232);
  }

  bufferInitialized = true;
  g_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[150528]
 *                float Z[301056]
 * Return Type  : void
 */
void conv2dDirectOptimizedColMajor(const float X[150528], float Z[301056])
{
  static float reformattedAndTruncatedWeights[648];
  static float biasReformatted[24];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13593004.bin", 648);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13593003.bin", 24);
  }

  bufferInitialized = true;
  convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
              &biasReformatted[0]);
}

/*
 * Arguments    : const float X[75264]
 *                float Z[188160]
 * Return Type  : void
 */
void d_conv2dDirectOptimizedColMajor(const float X[75264], float Z[188160])
{
  static float reformattedAndTruncatedWeights[1440];
  static float biasReformatted[60];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13593634.bin", 1440);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13593633.bin", 60);
  }

  bufferInitialized = true;
  c_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void db_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13600738.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13600737.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[11368]
 *                float Z[11368]
 * Return Type  : void
 */
void dc_conv2dDirectOptimizedColMajo(const float X[11368], float Z[11368])
{
  static float reformattedAndTruncatedWeights[2088];
  static float biasReformatted[232];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13606971.bin", 2088);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13606970.bin", 232);
  }

  bufferInitialized = true;
  g_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[188160]
 *                float Z[47040]
 * Return Type  : void
 */
void e_conv2dDirectOptimizedColMajor(const float X[188160], float Z[47040])
{
  static float reformattedAndTruncatedWeights[540];
  static float biasReformatted[60];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13593872.bin", 540);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13593871.bin", 60);
  }

  bufferInitialized = true;
  b_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void eb_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13600976.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13600975.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[11368]
 *                float Z[11368]
 * Return Type  : void
 */
void ec_conv2dDirectOptimizedColMajo(const float X[11368], float Z[11368])
{
  static float reformattedAndTruncatedWeights[53824];
  static float biasReformatted[232];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13607125.bin", 53824);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13607124.bin", 232);
  }

  bufferInitialized = true;
  g_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[47040]
 *                float Z[47040]
 * Return Type  : void
 */
void f_conv2dDirectOptimizedColMajor(const float X[47040], float Z[47040])
{
  static float reformattedAndTruncatedWeights[3600];
  static float biasReformatted[60];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13594026.bin", 3600);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13594025.bin", 60);
  }

  bufferInitialized = true;
  d_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void fb_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[1044];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13601214.bin", 1044);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13601213.bin", 116);
  }

  bufferInitialized = true;
  e_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[50176]
 * Return Type  : void
 */
void fc_conv2dDirectOptimizedColMajo(const float X[22736], float Z[50176])
{
  static float s_Weights[475136];
  static float biasReformatted[1024];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&s_Weights[0],
      "./embeddedDir//largeDnnConstants_13931770.bin", 475136);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13607292.bin", 1024);
  }

  bufferInitialized = true;
  i_convolution(&X[0], &Z[0], &s_Weights[0], &biasReformatted[0]);
}

/*
 * Arguments    : const float X[47040]
 *                float Z[47040]
 * Return Type  : void
 */
void g_conv2dDirectOptimizedColMajor(const float X[47040], float Z[47040])
{
  static float reformattedAndTruncatedWeights[3600];
  static float biasReformatted[60];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13595219.bin", 3600);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13595218.bin", 60);
  }

  bufferInitialized = true;
  d_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void gb_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13601368.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13601367.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[47040]
 *                float Z[47040]
 * Return Type  : void
 */
void h_conv2dDirectOptimizedColMajor(const float X[47040], float Z[47040])
{
  static float reformattedAndTruncatedWeights[540];
  static float biasReformatted[60];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13595457.bin", 540);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13595456.bin", 60);
  }

  bufferInitialized = true;
  c_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void hb_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13601606.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13601605.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[47040]
 *                float Z[47040]
 * Return Type  : void
 */
void i_conv2dDirectOptimizedColMajor(const float X[47040], float Z[47040])
{
  static float reformattedAndTruncatedWeights[3600];
  static float biasReformatted[60];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13595611.bin", 3600);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13595610.bin", 60);
  }

  bufferInitialized = true;
  d_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void ib_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[1044];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13601844.bin", 1044);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13601843.bin", 116);
  }

  bufferInitialized = true;
  e_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[47040]
 *                float Z[47040]
 * Return Type  : void
 */
void j_conv2dDirectOptimizedColMajor(const float X[47040], float Z[47040])
{
  static float reformattedAndTruncatedWeights[3600];
  static float biasReformatted[60];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13595849.bin", 3600);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13595848.bin", 60);
  }

  bufferInitialized = true;
  d_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void jb_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13601998.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13601997.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[47040]
 *                float Z[47040]
 * Return Type  : void
 */
void k_conv2dDirectOptimizedColMajor(const float X[47040], float Z[47040])
{
  static float reformattedAndTruncatedWeights[540];
  static float biasReformatted[60];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13596087.bin", 540);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13596086.bin", 60);
  }

  bufferInitialized = true;
  c_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void kb_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13602236.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13602235.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[47040]
 *                float Z[47040]
 * Return Type  : void
 */
void l_conv2dDirectOptimizedColMajor(const float X[47040], float Z[47040])
{
  static float reformattedAndTruncatedWeights[3600];
  static float biasReformatted[60];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13596241.bin", 3600);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13596240.bin", 60);
  }

  bufferInitialized = true;
  d_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void lb_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[1044];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13602474.bin", 1044);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13602473.bin", 116);
  }

  bufferInitialized = true;
  e_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[47040]
 *                float Z[47040]
 * Return Type  : void
 */
void m_conv2dDirectOptimizedColMajor(const float X[47040], float Z[47040])
{
  static float reformattedAndTruncatedWeights[3600];
  static float biasReformatted[60];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13596479.bin", 3600);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13596478.bin", 60);
  }

  bufferInitialized = true;
  d_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void mb_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13602628.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13602627.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[47040]
 *                float Z[47040]
 * Return Type  : void
 */
void n_conv2dDirectOptimizedColMajor(const float X[47040], float Z[47040])
{
  static float reformattedAndTruncatedWeights[540];
  static float biasReformatted[60];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13596717.bin", 540);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13596716.bin", 60);
  }

  bufferInitialized = true;
  c_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void nb_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13602866.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13602865.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[47040]
 *                float Z[47040]
 * Return Type  : void
 */
void o_conv2dDirectOptimizedColMajor(const float X[47040], float Z[47040])
{
  static float reformattedAndTruncatedWeights[3600];
  static float biasReformatted[60];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13596871.bin", 3600);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13596870.bin", 60);
  }

  bufferInitialized = true;
  d_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void ob_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[1044];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13603104.bin", 1044);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13603103.bin", 116);
  }

  bufferInitialized = true;
  e_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[90944]
 *                float Z[22736]
 * Return Type  : void
 */
void p_conv2dDirectOptimizedColMajor(const float X[90944], float Z[22736])
{
  static float reformattedAndTruncatedWeights[1044];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13597109.bin", 1044);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13597108.bin", 116);
  }

  bufferInitialized = true;
  d_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void pb_conv2dDirectOptimizedColMajo(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13603258.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13603257.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void q_conv2dDirectOptimizedColMajor(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13597263.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13597262.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[45472]
 *                float Z[11368]
 * Return Type  : void
 */
void qb_conv2dDirectOptimizedColMajo(const float X[45472], float Z[11368])
{
  static float reformattedAndTruncatedWeights[2088];
  static float biasReformatted[232];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13603496.bin", 2088);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13603495.bin", 232);
  }

  bufferInitialized = true;
  f_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[90944]
 *                float Z[90944]
 * Return Type  : void
 */
void r_conv2dDirectOptimizedColMajor(const float X[90944], float Z[90944])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13597501.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13597500.bin", 116);
  }

  bufferInitialized = true;
  f_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[11368]
 *                float Z[11368]
 * Return Type  : void
 */
void rb_conv2dDirectOptimizedColMajo(const float X[11368], float Z[11368])
{
  static float reformattedAndTruncatedWeights[53824];
  static float biasReformatted[232];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13603650.bin", 53824);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13603649.bin", 232);
  }

  bufferInitialized = true;
  g_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[90944]
 *                float Z[22736]
 * Return Type  : void
 */
void s_conv2dDirectOptimizedColMajor(const float X[90944], float Z[22736])
{
  static float reformattedAndTruncatedWeights[1044];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13597739.bin", 1044);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13597738.bin", 116);
  }

  bufferInitialized = true;
  d_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[45472]
 *                float Z[45472]
 * Return Type  : void
 */
void sb_conv2dDirectOptimizedColMajo(const float X[45472], float Z[45472])
{
  static float reformattedAndTruncatedWeights[53824];
  static float biasReformatted[232];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13603888.bin", 53824);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13603887.bin", 232);
  }

  bufferInitialized = true;
  h_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void t_conv2dDirectOptimizedColMajor(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13597893.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13597892.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[45472]
 *                float Z[11368]
 * Return Type  : void
 */
void tb_conv2dDirectOptimizedColMajo(const float X[45472], float Z[11368])
{
  static float reformattedAndTruncatedWeights[2088];
  static float biasReformatted[232];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13604126.bin", 2088);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13604125.bin", 232);
  }

  bufferInitialized = true;
  f_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void u_conv2dDirectOptimizedColMajor(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13599086.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13599085.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[11368]
 *                float Z[11368]
 * Return Type  : void
 */
void ub_conv2dDirectOptimizedColMajo(const float X[11368], float Z[11368])
{
  static float reformattedAndTruncatedWeights[53824];
  static float biasReformatted[232];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13604280.bin", 53824);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13604279.bin", 232);
  }

  bufferInitialized = true;
  g_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void v_conv2dDirectOptimizedColMajor(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[1044];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13599324.bin", 1044);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13599323.bin", 116);
  }

  bufferInitialized = true;
  e_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[11368]
 *                float Z[11368]
 * Return Type  : void
 */
void vb_conv2dDirectOptimizedColMajo(const float X[11368], float Z[11368])
{
  static float reformattedAndTruncatedWeights[53824];
  static float biasReformatted[232];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13605473.bin", 53824);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13605472.bin", 232);
  }

  bufferInitialized = true;
  g_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void w_conv2dDirectOptimizedColMajor(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13599478.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13599477.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[11368]
 *                float Z[11368]
 * Return Type  : void
 */
void wb_conv2dDirectOptimizedColMajo(const float X[11368], float Z[11368])
{
  static float reformattedAndTruncatedWeights[2088];
  static float biasReformatted[232];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13605711.bin", 2088);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13605710.bin", 232);
  }

  bufferInitialized = true;
  g_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void x_conv2dDirectOptimizedColMajor(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[13456];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13599716.bin", 13456);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13599715.bin", 116);
  }

  bufferInitialized = true;
  e_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[11368]
 *                float Z[11368]
 * Return Type  : void
 */
void xb_conv2dDirectOptimizedColMajo(const float X[11368], float Z[11368])
{
  static float reformattedAndTruncatedWeights[53824];
  static float biasReformatted[232];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13605865.bin", 53824);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13605864.bin", 232);
  }

  bufferInitialized = true;
  g_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * Arguments    : const float X[22736]
 *                float Z[22736]
 * Return Type  : void
 */
void y_conv2dDirectOptimizedColMajor(const float X[22736], float Z[22736])
{
  static float reformattedAndTruncatedWeights[1044];
  static float biasReformatted[116];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13599954.bin", 1044);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13599953.bin", 116);
  }

  bufferInitialized = true;
  e_groupedConvolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                       &biasReformatted[0]);
}

/*
 * Arguments    : const float X[11368]
 *                float Z[11368]
 * Return Type  : void
 */
void yb_conv2dDirectOptimizedColMajo(const float X[11368], float Z[11368])
{
  static float reformattedAndTruncatedWeights[53824];
  static float biasReformatted[232];
  static bool bufferInitialized;
  if (!bufferInitialized) {
    readDnnConstants_real32_T(&reformattedAndTruncatedWeights[0],
      "./embeddedDir//largeDnnConstants_13606103.bin", 53824);
    readDnnConstants_real32_T(&biasReformatted[0],
      "./embeddedDir//largeDnnConstants_13606102.bin", 232);
  }

  bufferInitialized = true;
  g_convolution(&X[0], &Z[0], &reformattedAndTruncatedWeights[0],
                &biasReformatted[0]);
}

/*
 * File trailer for conv2dDirectOptimizedColMajor.c
 *
 * [EOF]
 */
