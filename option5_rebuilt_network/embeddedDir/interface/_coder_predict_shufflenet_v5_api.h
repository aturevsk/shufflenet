/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: _coder_predict_shufflenet_v5_api.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 21-Mar-2026 02:18:26
 */

#ifndef _CODER_PREDICT_SHUFFLENET_V5_API_H
#define _CODER_PREDICT_SHUFFLENET_V5_API_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void predict_shufflenet_v5(const real32_T in[150528], real32_T out[1000]);

void predict_shufflenet_v5_api(const mxArray *const prhs[1],
                               const mxArray **plhs);

void predict_shufflenet_v5_atexit(void);

void predict_shufflenet_v5_initialize(void);

void predict_shufflenet_v5_terminate(void);

void predict_shufflenet_v5_xil_shutdown(void);

void predict_shufflenet_v5_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_predict_shufflenet_v5_api.h
 *
 * [EOF]
 */
