/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * ChannelSplitLayer.c
 *
 * Code generation for function 'ChannelSplitLayer'
 *
 */

/* Include files */
#include "ChannelSplitLayer.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void ChannelSplitLayer_predict(const real32_T X_Data[90944],
                               real32_T Z1_Data[45472], real32_T Z2_Data[45472])
{
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&Z1_Data[0], &X_Data[0], 45472U * sizeof(real32_T));
  memcpy(&Z2_Data[0], &X_Data[45472], 45472U * sizeof(real32_T));
}

void b_ChannelSplitLayer_predict(const real32_T X_Data[45472],
                                 real32_T Z1_Data[22736],
                                 real32_T Z2_Data[22736])
{
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&Z1_Data[0], &X_Data[0], 22736U * sizeof(real32_T));
  memcpy(&Z2_Data[0], &X_Data[22736], 22736U * sizeof(real32_T));
}

void c_ChannelSplitLayer_predict(const real32_T X_Data[22736],
                                 real32_T Z1_Data[11368],
                                 real32_T Z2_Data[11368])
{
  /* predict  Forward pass: split channels in half. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Z1 is [H, W, C/2, N] (first half) */
  /*    Z2 is [H, W, C/2, N] (second half) */
  memcpy(&Z1_Data[0], &X_Data[0], 11368U * sizeof(real32_T));
  memcpy(&Z2_Data[0], &X_Data[11368], 11368U * sizeof(real32_T));
}

/* End of code generation (ChannelSplitLayer.c) */
