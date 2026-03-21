/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: mean.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 20-Mar-2026 21:50:48
 */

/* Include Files */
#include "mean.h"

/* Function Definitions */
/*
 * Arguments    : const float x[50176]
 *                float y[1024]
 * Return Type  : void
 */
void mean(const float x[50176], float y[1024])
{
  int k;
  int xi;
  for (xi = 0; xi < 1024; xi++) {
    float f;
    int xpageoffset;
    xpageoffset = xi * 49;
    f = x[xpageoffset];
    for (k = 0; k < 48; k++) {
      f += x[(xpageoffset + k) + 1];
    }
    y[xi] = f / 49.0F;
  }
}

/*
 * File trailer for mean.c
 *
 * [EOF]
 */
