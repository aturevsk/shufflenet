/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: cat.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:35:57
 */

/* Include Files */
#include "cat.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const float varargin_1[22736]
 *                const float varargin_2[22736]
 *                float y[45472]
 * Return Type  : void
 */
void cat(const float varargin_1[22736], const float varargin_2[22736],
         float y[45472])
{
  memcpy(&y[0], &varargin_1[0], 22736U * sizeof(float));
  memcpy(&y[22736], &varargin_2[0], 22736U * sizeof(float));
}

/*
 * File trailer for cat.c
 *
 * [EOF]
 */
