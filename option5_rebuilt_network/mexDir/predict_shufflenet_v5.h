/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * predict_shufflenet_v5.h
 *
 * Code generation for function 'predict_shufflenet_v5'
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
emlrtCTX emlrtGetRootTLSGlobal(void);

void emlrtLockerFunction(EmlrtLockeeFunction aLockee, emlrtConstCTX aTLS,
                         void *aData);

void predict_shufflenet_v5(predict_shufflenet_v5StackData *SD,
                           const emlrtStack *sp, const real32_T in[150528],
                           real32_T out[1000]);

/* End of code generation (predict_shufflenet_v5.h) */
