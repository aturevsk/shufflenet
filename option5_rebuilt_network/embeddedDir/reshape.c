/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: reshape.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 21-Mar-2026 02:18:26
 */

/* Include Files */
#include "reshape.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const float objX_Data[45472]
 *                float objZ_Data[45472]
 * Return Type  : void
 */
void b_dlarray_reshape(const float objX_Data[45472], float objZ_Data[45472])
{
  int b_k;
  int c_k;
  int d_k;
  int k;
  for (k = 0; k < 2; k++) {
    for (b_k = 0; b_k < 116; b_k++) {
      for (c_k = 0; c_k < 14; c_k++) {
        for (d_k = 0; d_k < 14; d_k++) {
          int objZ_Data_tmp;
          objZ_Data_tmp = d_k + 14 * c_k;
          objZ_Data[(objZ_Data_tmp + 196 * k) + 392 * b_k] =
              objX_Data[(objZ_Data_tmp + 196 * b_k) + 22736 * k];
        }
      }
    }
  }
}

/*
 * Arguments    : const float objX_Data[22736]
 *                float objZ_Data[22736]
 * Return Type  : void
 */
void c_dlarray_reshape(const float objX_Data[22736], float objZ_Data[22736])
{
  int b_k;
  int c_k;
  int d_k;
  int k;
  for (k = 0; k < 2; k++) {
    for (b_k = 0; b_k < 232; b_k++) {
      for (c_k = 0; c_k < 7; c_k++) {
        for (d_k = 0; d_k < 7; d_k++) {
          int objZ_Data_tmp;
          objZ_Data_tmp = d_k + 7 * c_k;
          objZ_Data[(objZ_Data_tmp + 49 * k) + 98 * b_k] =
              objX_Data[(objZ_Data_tmp + 49 * b_k) + 11368 * k];
        }
      }
    }
  }
}

/*
 * Arguments    : const float objX_Data[90944]
 *                float objZ_Data[90944]
 * Return Type  : void
 */
void dlarray_reshape(const float objX_Data[90944], float objZ_Data[90944])
{
  int b_k;
  int c_k;
  int k;
  for (k = 0; k < 2; k++) {
    for (b_k = 0; b_k < 58; b_k++) {
      for (c_k = 0; c_k < 28; c_k++) {
        memcpy(&objZ_Data[(k * 784 + b_k * 1568) + c_k * 28],
               &objX_Data[(k * 45472 + b_k * 784) + c_k * 28],
               28U * sizeof(float));
      }
    }
  }
}

/*
 * File trailer for reshape.c
 *
 * [EOF]
 */
