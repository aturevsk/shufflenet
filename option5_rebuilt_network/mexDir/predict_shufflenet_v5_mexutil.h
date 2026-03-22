/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * predict_shufflenet_v5_mexutil.h
 *
 * Code generation for function 'predict_shufflenet_v5_mexutil'
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
char_T *computeFilePathUsingEnvVariable(const char_T *unresolvedFilePath);

char_T *extractCodegenFolderName(const char_T *filePath);

char_T *getCustomUserDataPathEnvVar(const char_T *unresolvedFilePath);

int32_T getPositionOfLastFileSeparator(const char_T *filePath);

char_T *getRelativePathToParentFolder(const char_T *filePath);

char_T *getResolvedFilePath(const char_T *unresolvedFilePath);

void readDnnConstants_real32_T(real32_T *inputBufferPtr,
                               const char_T *unresolvedFilePath,
                               int32_T numElementsToRead);

char_T *resolveBinaryFilePath(const char_T *unresolvedFilePath);

char_T *sanitizeFilePathForHSP(const char_T *unSanitizedFilePath);

void stringConcat(char_T *destinationString, const char_T *sourceString,
                  size_t destBufferSize);

void throwFileNotFoundErrorMessage(const char_T *unresolvedFilePath,
                                   const char_T *sanitizedFilePath);

/* End of code generation (predict_shufflenet_v5_mexutil.h) */
