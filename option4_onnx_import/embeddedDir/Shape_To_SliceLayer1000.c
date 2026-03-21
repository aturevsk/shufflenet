/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: Shape_To_SliceLayer1000.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 20-Mar-2026 21:50:48
 */

/* Include Files */
#include "Shape_To_SliceLayer1000.h"
#include "permute.h"

/* Function Definitions */
/*
 * Arguments    : const float x_stage2_stage2_0__5___Data[90944]
 *                float x_stage2_stage2_1_Sl_Data[45472]
 *                float x_stage2_stage2_1_61_Data[45472]
 * Return Type  : void
 */
void Shape_To_SliceLayer1000_predict(
    const float x_stage2_stage2_0__5___Data[90944],
    float x_stage2_stage2_1_Sl_Data[45472],
    float x_stage2_stage2_1_61_Data[45472])
{
  static float fv[90944];
  static float x_stage2_stage2_0_Tr[90944];
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
  permute(x_stage2_stage2_0__5___Data, fv);
  b_permute(fv, x_stage2_stage2_0_Tr);
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
  c_permute(&x_stage2_stage2_0_Tr[45472], x_stage2_stage2_1_Sl_Data);
  /*  Returns DLT ordering */
  /*    Copyright 2024 The MathWorks, Inc. */
  /*  ndims >= 2 */
  /*  Use the inverse of the user's permutation. This is not just the */
  /*  flip of the permutation vector. */
  c_permute(&x_stage2_stage2_0_Tr[0], x_stage2_stage2_1_61_Data);
}

/*
 * File trailer for Shape_To_SliceLayer1000.c
 *
 * [EOF]
 */
