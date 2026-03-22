/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: Shape_To_SliceLayer1004.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:35:57
 */

/* Include Files */
#include "Shape_To_SliceLayer1004.h"
#include "permute.h"

/* Function Definitions */
/*
 * Arguments    : const float x_stage3_stage3_0__5___Data[45472]
 *                float x_stage3_stage3_1_Sl_Data[22736]
 *                float x_stage3_stage3_1_61_Data[22736]
 * Return Type  : void
 */
void Shape_To_SliceLayer1004_predict(
    const float x_stage3_stage3_0__5___Data[45472],
    float x_stage3_stage3_1_Sl_Data[22736],
    float x_stage3_stage3_1_61_Data[22736])
{
  static float fv[45472];
  static float x_stage3_stage3_0_Tr[45472];
  /*  Returns reverse-ONNX ordering numeric array */
  /*    Copyright 2024 The MathWorks, Inc.   */
  /*  Permute into reverse ONNX ordering */
  /*  Execute the operators: */
  /*  Shape: */
  /*  Gather: */
  /*  Shape: */
  /*  Gather: */
  /*  Shape: */
  /*  Gather: */
  /*  Shape: */
  /*  Gather: */
  /*  Div: */
  /*  Cast: */
  /*  Unsqueeze: */
  /*  Concat: */
  /*  Reshape: */
  /*  Transpose: */
  d_permute(x_stage3_stage3_0__5___Data, fv);
  e_permute(fv, x_stage3_stage3_0_Tr);
  /*  Unsqueeze: */
  /*  Concat: */
  /*  Reshape: */
  /*  Shape: */
  /*  Gather: */
  /*  Add: */
  /*  Div: */
  /*  Mul: */
  /*  Slice: */
  /*  Mul: */
  /*  Slice: */
  /*  Set graph output arguments */
  /*  Returns DLT ordering */
  /*    Copyright 2024 The MathWorks, Inc. */
  /*  ndims >= 2 */
  /*  Use the inverse of the user's permutation. This is not just the */
  /*  flip of the permutation vector. */
  f_permute(&x_stage3_stage3_0_Tr[22736], x_stage3_stage3_1_Sl_Data);
  /*  Returns DLT ordering */
  /*    Copyright 2024 The MathWorks, Inc. */
  /*  ndims >= 2 */
  /*  Use the inverse of the user's permutation. This is not just the */
  /*  flip of the permutation vector. */
  f_permute(&x_stage3_stage3_0_Tr[0], x_stage3_stage3_1_61_Data);
}

/*
 * File trailer for Shape_To_SliceLayer1004.c
 *
 * [EOF]
 */
