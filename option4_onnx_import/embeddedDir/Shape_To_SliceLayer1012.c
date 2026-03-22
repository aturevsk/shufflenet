/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: Shape_To_SliceLayer1012.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:35:57
 */

/* Include Files */
#include "Shape_To_SliceLayer1012.h"
#include "permute.h"

/* Function Definitions */
/*
 * Arguments    : const float x_stage4_stage4_0__5___Data[22736]
 *                float x_stage4_stage4_1_Sl_Data[11368]
 *                float x_stage4_stage4_1_61_Data[11368]
 * Return Type  : void
 */
void Shape_To_SliceLayer1012_predict(
    const float x_stage4_stage4_0__5___Data[22736],
    float x_stage4_stage4_1_Sl_Data[11368],
    float x_stage4_stage4_1_61_Data[11368])
{
  static float fv[22736];
  static float x_stage4_stage4_0_Re[22736];
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
  /*  Unsqueeze: */
  /*  Concat: */
  /*  Reshape: */
  g_permute(x_stage4_stage4_0__5___Data, fv);
  h_permute(fv, x_stage4_stage4_0_Re);
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
  i_permute(&x_stage4_stage4_0_Re[11368], x_stage4_stage4_1_Sl_Data);
  /*  Returns DLT ordering */
  /*    Copyright 2024 The MathWorks, Inc. */
  /*  ndims >= 2 */
  /*  Use the inverse of the user's permutation. This is not just the */
  /*  flip of the permutation vector. */
  i_permute(&x_stage4_stage4_0_Re[0], x_stage4_stage4_1_61_Data);
}

/*
 * File trailer for Shape_To_SliceLayer1012.c
 *
 * [EOF]
 */
