/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: _coder_predict_shufflenet_v5_mex.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 21-Mar-2026 02:18:26
 */

#ifndef _CODER_PREDICT_SHUFFLENET_V5_MEX_H
#define _CODER_PREDICT_SHUFFLENET_V5_MEX_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS(void);

void unsafe_predict_shufflenet_v5_mexFunction(int32_T nlhs, mxArray *plhs[1],
                                              int32_T nrhs,
                                              const mxArray *prhs[1]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_predict_shufflenet_v5_mex.h
 *
 * [EOF]
 */
