/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * ChannelShuffleLayer.c
 *
 * Code generation for function 'ChannelShuffleLayer'
 *
 */

/* Include files */
#include "ChannelShuffleLayer.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void ChannelShuffleLayer_predict(const real32_T X_Data[90944],
                                 real32_T Z_Data[90944])
{
  int32_T b_k;
  int32_T c_k;
  int32_T k;
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  for (k = 0; k < 2; k++) {
    for (b_k = 0; b_k < 58; b_k++) {
      for (c_k = 0; c_k < 28; c_k++) {
        memcpy(&Z_Data[(k * 784 + b_k * 1568) + c_k * 28],
               &X_Data[(k * 45472 + b_k * 784) + c_k * 28],
               28U * sizeof(real32_T));
      }
    }
  }
}

void b_ChannelShuffleLayer_predict(const real32_T X_Data[45472],
                                   real32_T Z_Data[45472])
{
  int32_T b_k;
  int32_T c_k;
  int32_T d_k;
  int32_T k;
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  for (k = 0; k < 2; k++) {
    for (b_k = 0; b_k < 116; b_k++) {
      for (c_k = 0; c_k < 14; c_k++) {
        for (d_k = 0; d_k < 14; d_k++) {
          int32_T Z_Data_tmp;
          Z_Data_tmp = d_k + 14 * c_k;
          Z_Data[(Z_Data_tmp + 196 * k) + 392 * b_k] =
              X_Data[(Z_Data_tmp + 196 * b_k) + 22736 * k];
        }
      }
    }
  }
}

void c_ChannelShuffleLayer_predict(const real32_T X_Data[22736],
                                   real32_T Z_Data[22736])
{
  int32_T b_k;
  int32_T c_k;
  int32_T d_k;
  int32_T k;
  /* predict  Forward pass: channel shuffle. */
  /*    X is [H, W, C, N] (unformatted inside dlnetwork). */
  /*    Output Z is [H, W, C, N] with channels interleaved. */
  /*  Reshape: [H, W, C, N] -> [H, W, CperG, G, N] */
  /*  Permute: swap G and CperG dims -> [H, W, G, CperG, N] */
  /*  Flatten back: [H, W, G, CperG, N] -> [H, W, C, N] */
  for (k = 0; k < 2; k++) {
    for (b_k = 0; b_k < 232; b_k++) {
      for (c_k = 0; c_k < 7; c_k++) {
        for (d_k = 0; d_k < 7; d_k++) {
          int32_T Z_Data_tmp;
          Z_Data_tmp = d_k + 7 * c_k;
          Z_Data[(Z_Data_tmp + 49 * k) + 98 * b_k] =
              X_Data[(Z_Data_tmp + 49 * b_k) + 11368 * k];
        }
      }
    }
  }
}

/* End of code generation (ChannelShuffleLayer.c) */
