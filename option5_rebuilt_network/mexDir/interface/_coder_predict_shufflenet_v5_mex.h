/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * _coder_predict_shufflenet_v5_mex.h
 *
 * Code generation for function '_coder_predict_shufflenet_v5_mex'
 *
 */

#pragma once

/* Include files */
#include "predict_shufflenet_v5_types.h"
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS(void);

void predict_shufflenet_v5_mexFunction(predict_shufflenet_v5StackData *SD,
                                       int32_T nlhs, mxArray *plhs[1],
                                       int32_T nrhs, const mxArray *prhs[1]);

/* End of code generation (_coder_predict_shufflenet_v5_mex.h) */
