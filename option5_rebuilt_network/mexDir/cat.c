/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * cat.c
 *
 * Code generation for function 'cat'
 *
 */

/* Include files */
#include "cat.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void b_cat(const real32_T varargin_1[22736], const real32_T varargin_2[22736],
           real32_T y[45472])
{
  memcpy(&y[0], &varargin_1[0], 22736U * sizeof(real32_T));
  memcpy(&y[22736], &varargin_2[0], 22736U * sizeof(real32_T));
}

void c_cat(const real32_T varargin_1[11368], const real32_T varargin_2[11368],
           real32_T y[22736])
{
  memcpy(&y[0], &varargin_1[0], 11368U * sizeof(real32_T));
  memcpy(&y[11368], &varargin_2[0], 11368U * sizeof(real32_T));
}

void cat(const real32_T varargin_1[45472], const real32_T varargin_2[45472],
         real32_T y[90944])
{
  memcpy(&y[0], &varargin_1[0], 45472U * sizeof(real32_T));
  memcpy(&y[45472], &varargin_2[0], 45472U * sizeof(real32_T));
}

/* End of code generation (cat.c) */
