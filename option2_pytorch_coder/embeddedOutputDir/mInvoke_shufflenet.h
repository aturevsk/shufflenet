/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: mInvoke_shufflenet.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 20-Mar-2026 21:31:49
 */

#ifndef MINVOKE_SHUFFLENET_H
#define MINVOKE_SHUFFLENET_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
char *extractCodegenFolderName(const char *filePath);

extern void mInvoke_shufflenet(const float input[150528], float out[1000]);

void mInvoke_shufflenet_init(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for mInvoke_shufflenet.h
 *
 * [EOF]
 */
