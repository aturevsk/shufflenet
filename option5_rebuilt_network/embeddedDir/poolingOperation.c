/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: poolingOperation.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 21-Mar-2026 02:18:26
 */

/* Include Files */
#include "poolingOperation.h"
#include "omp.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const float X[301056]
 *                float Z[75264]
 * Return Type  : void
 */
void c_iPoolingForColumnMajorWithOpe(const float X[301056], float Z[75264])
{
  float inputPixel;
  float opValue;
  int filterHeightIdx;
  int filterWidthIdx;
  int inputHeightIdx;
  int inputHeightIdx_tmp;
  int inputWidthIdx;
  int inputWidthIdx_tmp;
  int prodOutDimsIdx;
  int varargout_7;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        inputPixel, inputHeightIdx, inputWidthIdx, opValue, varargout_7,       \
            inputHeightIdx_tmp, inputWidthIdx_tmp, filterWidthIdx,             \
            filterHeightIdx)

  for (prodOutDimsIdx = 0; prodOutDimsIdx < 75264; prodOutDimsIdx++) {
    inputWidthIdx = (int)((unsigned int)prodOutDimsIdx / 3136U);
    varargout_7 = inputWidthIdx;
    inputHeightIdx = prodOutDimsIdx - inputWidthIdx * 3136;
    inputWidthIdx = inputHeightIdx / 56;
    inputHeightIdx -= inputWidthIdx * 56;
    inputHeightIdx_tmp = inputHeightIdx << 1;
    inputWidthIdx_tmp = inputWidthIdx << 1;
    opValue = -3.402823466E+38F;
    if ((inputHeightIdx_tmp > 0) && (inputWidthIdx_tmp > 0) &&
        (inputHeightIdx_tmp + 3 <= 112) && (inputWidthIdx_tmp + 3 <= 112)) {
      for (filterWidthIdx = 0; filterWidthIdx < 3; filterWidthIdx++) {
        inputWidthIdx = filterWidthIdx + inputWidthIdx_tmp;
        inputHeightIdx = (inputHeightIdx_tmp + 112 * (inputWidthIdx - 1)) +
                         12544 * varargout_7;
        opValue = fmaxf(opValue, X[inputHeightIdx - 1]);
        opValue = fmaxf(opValue, X[inputHeightIdx]);
        opValue = fmaxf(opValue, X[inputHeightIdx + 1]);
      }
    } else {
      for (filterWidthIdx = 0; filterWidthIdx < 3; filterWidthIdx++) {
        inputWidthIdx = filterWidthIdx + inputWidthIdx_tmp;
        for (filterHeightIdx = 0; filterHeightIdx < 3; filterHeightIdx++) {
          inputHeightIdx = filterHeightIdx + inputHeightIdx_tmp;
          if ((inputHeightIdx > 0) && (inputWidthIdx > 0) &&
              (inputHeightIdx <= 112) && (inputWidthIdx <= 112)) {
            inputPixel = X[((inputHeightIdx + 112 * (inputWidthIdx - 1)) +
                            12544 * varargout_7) -
                           1];
          } else {
            inputPixel = -3.402823466E+38F;
          }
          opValue = fmaxf(opValue, inputPixel);
        }
      }
    }
    Z[prodOutDimsIdx] = opValue;
  }
}

/*
 * Arguments    : const float X[50176]
 *                float Z[1024]
 * Return Type  : void
 */
void d_iPoolingForColumnMajorWithOpe(const float X[50176], float Z[1024])
{
  float inputPixel;
  float opValue;
  int filterHeightIdx;
  int filterWidthIdx;
  int prodOutDimsIdx;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        inputPixel, opValue, filterWidthIdx, filterHeightIdx)

  for (prodOutDimsIdx = 0; prodOutDimsIdx < 1024; prodOutDimsIdx++) {
    opValue = 0.0F;
    for (filterWidthIdx = 0; filterWidthIdx < 7; filterWidthIdx++) {
      for (filterHeightIdx = 0; filterHeightIdx < 7; filterHeightIdx++) {
        inputPixel =
            X[(filterHeightIdx + 7 * filterWidthIdx) + 49 * prodOutDimsIdx];
        opValue += inputPixel;
      }
    }
    Z[prodOutDimsIdx] = 0.020408163F * opValue;
  }
}

/*
 * File trailer for poolingOperation.c
 *
 * [EOF]
 */
