/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * callPredict.h
 *
 * Code generation for function 'callPredict'
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
void predict(predict_shufflenet_v5StackData *SD, const emlrtStack *sp,
             const real32_T inputsT_0_f1[150528], real32_T outputs_0_f1[1000]);

/* End of code generation (callPredict.h) */
