/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: predict_shufflenet_onnx_terminate.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:35:57
 */

/* Include Files */
#include "predict_shufflenet_onnx_terminate.h"
#include "predict_shufflenet_onnx_data.h"
#include "omp.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void predict_shufflenet_onnx_terminate(void)
{
  omp_destroy_nest_lock(&predict_shufflenet_onnx_nestLockGlobal);
  isInitialized_predict_shufflenet_onnx = false;
}

/*
 * File trailer for predict_shufflenet_onnx_terminate.c
 *
 * [EOF]
 */
