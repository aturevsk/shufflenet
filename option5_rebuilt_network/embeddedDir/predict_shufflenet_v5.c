/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: predict_shufflenet_v5.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:41:39
 */

/* Include Files */
#include "predict_shufflenet_v5.h"
#include "callPredict.h"
#include "predict_shufflenet_v5_data.h"
#include "predict_shufflenet_v5_initialize.h"

/* Function Definitions */
/*
 * predict_shufflenet_v5  Codegen entry point for Option 5 rebuilt ShuffleNet
 * V2.
 *
 *    out = predict_shufflenet_v5(in)
 *
 *    Input:  in  - single-precision [224 x 224 x 3 x N] image (SSCB)
 *    Output: out - single-precision [1000 x N] class scores
 *
 *    The persistent network is loaded once from the saved .mat file.
 *    All custom layers (ChannelShuffleLayer, ChannelSplitLayer) are
 *    codegen-compatible, inheriting from nnet.layer.Layer directly.
 *
 * Arguments    : const float in[150528]
 *                float out[1000]
 * Return Type  : void
 */
void predict_shufflenet_v5(const float in[150528], float out[1000])
{
  if (!isInitialized_predict_shufflenet_v5) {
    predict_shufflenet_v5_initialize();
  }
  /*  Wrap input as dlarray with SSCB format for the network */
  predict(in, out);
}

/*
 * File trailer for predict_shufflenet_v5.c
 *
 * [EOF]
 */
