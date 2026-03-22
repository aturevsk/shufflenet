/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * ChannelSplitLayer.h
 *
 * Code generation for function 'ChannelSplitLayer'
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
void ChannelSplitLayer_predict(const real32_T X_Data[90944],
                               real32_T Z1_Data[45472],
                               real32_T Z2_Data[45472]);

void b_ChannelSplitLayer_predict(const real32_T X_Data[45472],
                                 real32_T Z1_Data[22736],
                                 real32_T Z2_Data[22736]);

void c_ChannelSplitLayer_predict(const real32_T X_Data[22736],
                                 real32_T Z1_Data[11368],
                                 real32_T Z2_Data[11368]);

/* End of code generation (ChannelSplitLayer.h) */
