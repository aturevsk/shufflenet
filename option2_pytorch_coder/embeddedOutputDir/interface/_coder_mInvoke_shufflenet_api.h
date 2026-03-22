/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: _coder_mInvoke_shufflenet_api.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:38:14
 */

#ifndef _CODER_MINVOKE_SHUFFLENET_API_H
#define _CODER_MINVOKE_SHUFFLENET_API_H

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
void mInvoke_shufflenet(const real32_T input[150528], real32_T out[1000]);

void mInvoke_shufflenet_api(const mxArray *const prhs[1], const mxArray **plhs);

void mInvoke_shufflenet_atexit(void);

void mInvoke_shufflenet_initialize(void);

void mInvoke_shufflenet_terminate(void);

void mInvoke_shufflenet_xil_shutdown(void);

void mInvoke_shufflenet_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_mInvoke_shufflenet_api.h
 *
 * [EOF]
 */
