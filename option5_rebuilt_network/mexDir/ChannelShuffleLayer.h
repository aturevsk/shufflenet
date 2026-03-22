/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * ChannelShuffleLayer.h
 *
 * Code generation for function 'ChannelShuffleLayer'
 *
 */

#pragma once

/* Include files */
#include "rtwtypes.h"
#include "emlrt.h"
#include "mex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
void ChannelShuffleLayer_predict(const real32_T X_Data[90944],
                                 real32_T Z_Data[90944]);

void b_ChannelShuffleLayer_predict(const real32_T X_Data[45472],
                                   real32_T Z_Data[45472]);

void c_ChannelShuffleLayer_predict(const real32_T X_Data[22736],
                                   real32_T Z_Data[22736]);

/* End of code generation (ChannelShuffleLayer.h) */
