/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * poolingOperation.h
 *
 * Code generation for function 'poolingOperation'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void c_iPoolingForColumnMajorWithOpe(const emlrtStack *sp,
                                     const real32_T X[301056],
                                     real32_T Z[75264]);

void d_iPoolingForColumnMajorWithOpe(const emlrtStack *sp,
                                     const real32_T X[50176], real32_T Z[1024]);

/* End of code generation (poolingOperation.h) */
