/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: predict_shufflenet_v5_rtwutil.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:41:39
 */

#ifndef PREDICT_SHUFFLENET_V5_RTWUTIL_H
#define PREDICT_SHUFFLENET_V5_RTWUTIL_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern char *computeFilePathUsingEnvVariable(const char *unresolvedFilePath);

extern char *getCustomUserDataPathEnvVar(const char *unresolvedFilePath);

extern int getPositionOfLastFileSeparator(const char *filePath);

extern char *getRelativePathToParentFolder(const char *filePath);

extern char *getResolvedFilePath(const char *unresolvedFilePath);

extern void readDnnConstants_real32_T(float *inputBufferPtr,
                                      const char *unresolvedFilePath,
                                      int numElementsToRead);

extern char *resolveBinaryFilePath(const char *unresolvedFilePath);

extern char *sanitizeFilePathForHSP(const char *unSanitizedFilePath);

extern void stringConcat(char *destinationString, const char *sourceString,
                         size_t destBufferSize);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for predict_shufflenet_v5_rtwutil.h
 *
 * [EOF]
 */
