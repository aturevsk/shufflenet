/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: predict_shufflenet_onnx.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:35:57
 */

/* Include Files */
#include "predict_shufflenet_onnx.h"
#include "callPredict.h"
#include "predict_shufflenet_onnx_data.h"
#include "predict_shufflenet_onnx_initialize.h"

/* Function Definitions */
/*
 * PREDICT_SHUFFLENET_ONNX Entry-point for ShuffleNet V2 inference (ONNX
 * import).
 *
 *    OUT = PREDICT_SHUFFLENET_ONNX(IN) runs inference on a pre-saved
 *    dlnetwork imported from ONNX.
 *
 *    Inputs:
 *        in  - Input image [224 x 224 x 3] single (HWC format)
 *
 *    Outputs:
 *        out - Network output class scores [1 x 1000]
 *
 * Arguments    : const float in[150528]
 *                float out[1000]
 * Return Type  : void
 */
void predict_shufflenet_onnx(const float in[150528], float out[1000])
{
  if (!isInitialized_predict_shufflenet_onnx) {
    predict_shufflenet_onnx_initialize();
  }
  /*    Copyright 2026. Generated for ARM Cortex-A embedded platform deployment.
   */
  /*  Wrap as dlarray for network that expects SSCB format */
  predict(in, out);
}

/*
 * File trailer for predict_shufflenet_onnx.c
 *
 * [EOF]
 */
