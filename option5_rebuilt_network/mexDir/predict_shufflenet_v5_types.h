/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * predict_shufflenet_v5_types.h
 *
 * Code generation for function 'predict_shufflenet_v5'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef typedef_cell_wrap_19
#define typedef_cell_wrap_19
typedef struct {
  real32_T f1[45472];
} cell_wrap_19;
#endif /* typedef_cell_wrap_19 */

#ifndef typedef_cell_wrap_22
#define typedef_cell_wrap_22
typedef struct {
  real32_T f1[22736];
} cell_wrap_22;
#endif /* typedef_cell_wrap_22 */

#ifndef typedef_cell_wrap_24
#define typedef_cell_wrap_24
typedef struct {
  real32_T f1[11368];
} cell_wrap_24;
#endif /* typedef_cell_wrap_24 */

#ifndef typedef_b_predict
#define typedef_b_predict
typedef struct {
  real32_T X[301056];
  real32_T outT_f6_0_f1[181888];
  cell_wrap_19 outT_f11[2];
  real32_T tempData[90944];
  real32_T outT_f31_0_f1[90944];
  real32_T Z[75264];
  real32_T b_X[50176];
  real32_T outT_f8_0_f1[45472];
  cell_wrap_22 outT_f36[2];
  real32_T b_tempData[45472];
  real32_T outT_f5_0_f1[45472];
  real32_T outT_f30_0_f1[22736];
  real32_T outT_f33_0_f1[22736];
  real32_T outT_f29_0_f1[22736];
  cell_wrap_24 outT_f85[2];
  real32_T outT_f4_0_f1[18816];
} b_predict;
#endif /* typedef_b_predict */

#ifndef c_typedef_predict_shufflenet_v5
#define c_typedef_predict_shufflenet_v5
typedef struct {
  b_predict f0;
} predict_shufflenet_v5StackData;
#endif /* c_typedef_predict_shufflenet_v5 */

/* End of code generation (predict_shufflenet_v5_types.h) */
