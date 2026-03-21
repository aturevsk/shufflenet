/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: predict_shufflenet_v5_rtwutil.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 21-Mar-2026 02:18:26
 */

/* Include Files */
#include "predict_shufflenet_v5_rtwutil.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const char *unresolvedFilePath
 * Return Type  : char *
 */
char *computeFilePathUsingEnvVariable(const char *unresolvedFilePath)
{
  char *resolvedFilePath;
  char *stringDuplicate;
#if defined(MW_RUNTIME_DL_DATA_PATH)
  extern char *mwGetRuntimeDLDataPath(const char *);
  resolvedFilePath = mwGetRuntimeDLDataPath((char *)unresolvedFilePath);
#elif defined(MW_DL_DATA_PATH)
  resolvedFilePath = resolveBinaryFilePath(unresolvedFilePath);
#else
  char *coderDataPath;
  coderDataPath = getenv("CODER_DATA_PATH");
  if (coderDataPath != NULL) {
    resolvedFilePath = resolveBinaryFilePath(unresolvedFilePath);
  } else {
    size_t filePathLen;
    size_t sizeOfChar;
    filePathLen = strlen(unresolvedFilePath) + 1;
    sizeOfChar = 1;
    stringDuplicate = (char *)calloc(filePathLen, sizeOfChar);
    stringConcat(stringDuplicate, unresolvedFilePath, filePathLen);
    resolvedFilePath = stringDuplicate;
  }
#endif
  return resolvedFilePath;
}

/*
 * Arguments    : const char *unresolvedFilePath
 * Return Type  : char *
 */
char *getCustomUserDataPathEnvVar(const char *unresolvedFilePath)
{
  const char *fileName;
  char *coderDataPath;
  char *resolvedFilePath;
  coderDataPath = getenv("CODER_DATA_PATH");
  if (coderDataPath != NULL) {
    int posOfLastPathSeparator;
    size_t filePathLength;
    size_t sizeOfChar;
    posOfLastPathSeparator = getPositionOfLastFileSeparator(unresolvedFilePath);
    fileName = &unresolvedFilePath[posOfLastPathSeparator];
    filePathLength = (strlen(coderDataPath) + strlen(fileName)) + 1;
    sizeOfChar = 1;
    resolvedFilePath = (char *)calloc(filePathLength, sizeOfChar);
    stringConcat(resolvedFilePath, coderDataPath, filePathLength);
    stringConcat(resolvedFilePath, fileName, filePathLength);
  } else {
    resolvedFilePath = NULL;
  }
  return resolvedFilePath;
}

/*
 * Arguments    : const char *filePath
 * Return Type  : int
 */
int getPositionOfLastFileSeparator(const char *filePath)
{
  int lastPathSeparatorUnix;
  int posOfLastPathSeparator;
  const char *ptrToLastPathSeparator;
  lastPathSeparatorUnix = '/';
  ptrToLastPathSeparator = strrchr(filePath, lastPathSeparatorUnix);
  if (ptrToLastPathSeparator != NULL) {
    posOfLastPathSeparator = (int)(ptrToLastPathSeparator - filePath);
  } else {
    int lastPathSeparatorWindows;
    lastPathSeparatorWindows = '\\';
    ptrToLastPathSeparator = strrchr(filePath, lastPathSeparatorWindows);
    if (ptrToLastPathSeparator != NULL) {
      posOfLastPathSeparator = (int)(ptrToLastPathSeparator - filePath);
    } else {
      posOfLastPathSeparator = -1;
    }
  }
  return posOfLastPathSeparator;
}

/*
 * Arguments    : const char *filePath
 * Return Type  : char *
 */
char *getRelativePathToParentFolder(const char *filePath)
{
  int posOfLastPathSeparator;
  const char *fileName;
  const char *parentDir;
  char *resolvedFilePath;
  size_t filePathLength;
  size_t sizeOfChar;
  parentDir = "..";
  posOfLastPathSeparator = getPositionOfLastFileSeparator(filePath);
  fileName = &filePath[posOfLastPathSeparator];
  filePathLength = (strlen(parentDir) + strlen(fileName)) + 1;
  sizeOfChar = 1;
  resolvedFilePath = (char *)calloc(filePathLength, sizeOfChar);
  stringConcat(resolvedFilePath, parentDir, filePathLength);
  stringConcat(resolvedFilePath, fileName, filePathLength);
  return resolvedFilePath;
}

/*
 * Arguments    : const char *unresolvedFilePath
 * Return Type  : char *
 */
char *getResolvedFilePath(const char *unresolvedFilePath)
{
  const char *fileOpenMode;
  char *computedPathUsingEnvVars;
  char *pathUsingEnvVarAndSanitizedPath;
  char *relativePathToParent;
  char *resolvedFilePath;
  char *sanitizedFilePath;
  char *stringDuplicate;
  FILE *filePtr;
  resolvedFilePath = NULL;
  fileOpenMode = "rb";
  filePtr = fopen(unresolvedFilePath, fileOpenMode);
  if (filePtr) {
    size_t filePathLen;
    size_t sizeOfChar;
    filePathLen = strlen(unresolvedFilePath) + 1;
    sizeOfChar = 1;
    stringDuplicate = (char *)calloc(filePathLen, sizeOfChar);
    stringConcat(stringDuplicate, unresolvedFilePath, filePathLen);
    resolvedFilePath = stringDuplicate;
    fclose(filePtr);
  } else {
    computedPathUsingEnvVars =
        computeFilePathUsingEnvVariable(unresolvedFilePath);
    filePtr = fopen(computedPathUsingEnvVars, fileOpenMode);
    if (filePtr) {
      resolvedFilePath = computedPathUsingEnvVars;
      fclose(filePtr);
    } else {
      free(computedPathUsingEnvVars);
      sanitizedFilePath = sanitizeFilePathForHSP(unresolvedFilePath);
      filePtr = fopen(sanitizedFilePath, fileOpenMode);
      if (filePtr) {
        resolvedFilePath = sanitizedFilePath;
        fclose(filePtr);
      } else {
        relativePathToParent =
            getRelativePathToParentFolder(unresolvedFilePath);
        filePtr = fopen(relativePathToParent, fileOpenMode);
        if (filePtr) {
          resolvedFilePath = relativePathToParent;
          fclose(filePtr);
        } else {
          free(relativePathToParent);
          pathUsingEnvVarAndSanitizedPath =
              computeFilePathUsingEnvVariable(sanitizedFilePath);
          filePtr = fopen(pathUsingEnvVarAndSanitizedPath, fileOpenMode);
          if (filePtr) {
            resolvedFilePath = pathUsingEnvVarAndSanitizedPath;
            fclose(filePtr);
          } else {
            free(pathUsingEnvVarAndSanitizedPath);
            exit(EXIT_FAILURE);
          }
        }
      }
    }
  }
  return resolvedFilePath;
}

/*
 * Arguments    : float *inputBufferPtr
 *                const char *unresolvedFilePath
 *                int numElementsToRead
 * Return Type  : void
 */
void readDnnConstants_real32_T(float *inputBufferPtr,
                               const char *unresolvedFilePath,
                               int numElementsToRead)
{
  int elementSizeInBytes;
  const char *fileOpenMode;
  char *resolvedFilePath;
  FILE *filePtr;
  void *dataBufferPtr;
  resolvedFilePath = getResolvedFilePath(unresolvedFilePath);
  fileOpenMode = "rb";
  filePtr = fopen(resolvedFilePath, fileOpenMode);
  dataBufferPtr = &inputBufferPtr[0];
  elementSizeInBytes = 4;
  fread(dataBufferPtr, elementSizeInBytes, numElementsToRead, filePtr);
  fclose(filePtr);
  free(resolvedFilePath);
}

/*
 * Arguments    : const char *unresolvedFilePath
 * Return Type  : char *
 */
char *resolveBinaryFilePath(const char *unresolvedFilePath)
{
  const char *c_filePathAfterSlicingRelativeP;
  const char *c_leadingPathSeparatorUnixAndWi;
  const char *lastDirName;
  const char *lastPathSeparator;
  const char *mwDLDataPath;
  char *codegenDir;
  char *coderDataPath;
  char *resolvedFilePath;
  char *updatedStartDir;
  size_t sizeOfChar;
#define XSTR(x) #x
#define STR(x) XSTR(x)
  coderDataPath = getenv("CODER_DATA_PATH");
  sizeOfChar = 1;
  if (coderDataPath != NULL) {
    resolvedFilePath = getCustomUserDataPathEnvVar(unresolvedFilePath);
  } else {
    int lastPathSeparatorWindows;
    size_t codegenDirLength;
    size_t posOfCodegenDir;
    size_t posOfLeadingPathSeparator;
    mwDLDataPath = STR(MW_DL_DATA_PATH);
    c_filePathAfterSlicingRelativeP = &unresolvedFilePath[2];
    c_leadingPathSeparatorUnixAndWi = "/\\";
    posOfLeadingPathSeparator = strcspn(c_filePathAfterSlicingRelativeP,
                                        c_leadingPathSeparatorUnixAndWi);
    codegenDirLength = posOfLeadingPathSeparator + 1;
    codegenDir = (char *)calloc(codegenDirLength, sizeOfChar);
    strncpy(codegenDir, c_filePathAfterSlicingRelativeP,
            posOfLeadingPathSeparator);
    lastPathSeparatorWindows = '\\';
    lastPathSeparator = strrchr(mwDLDataPath, lastPathSeparatorWindows);
    if (lastPathSeparator == NULL) {
      int lastPathSeparatorUnix;
      lastPathSeparatorUnix = '/';
      lastPathSeparator = strrchr(mwDLDataPath, lastPathSeparatorUnix);
    }
    if (lastPathSeparator == NULL) {
      lastDirName = mwDLDataPath;
    } else {
      lastDirName = lastPathSeparator + 1;
    }
    if (strcmp(lastDirName, codegenDir) == 0) {
      posOfCodegenDir = lastDirName - mwDLDataPath;
    } else {
      posOfCodegenDir = strlen(mwDLDataPath);
    }
    if (posOfCodegenDir == strlen(mwDLDataPath)) {
      size_t filePathLen_a;
      c_filePathAfterSlicingRelativeP = &unresolvedFilePath[1];
      filePathLen_a =
          (strlen(mwDLDataPath) + strlen(c_filePathAfterSlicingRelativeP)) + 1;
      resolvedFilePath = (char *)calloc(filePathLen_a, sizeOfChar);
      stringConcat(resolvedFilePath, mwDLDataPath, filePathLen_a);
      stringConcat(resolvedFilePath, c_filePathAfterSlicingRelativeP,
                   filePathLen_a);
    } else {
      size_t filePathLen_b;
      filePathLen_b = posOfCodegenDir + 1;
      updatedStartDir = (char *)calloc(filePathLen_b, sizeOfChar);
      strncpy(updatedStartDir, mwDLDataPath, posOfCodegenDir);
      filePathLen_b =
          (strlen(updatedStartDir) + strlen(c_filePathAfterSlicingRelativeP)) +
          1;
      resolvedFilePath = (char *)calloc(filePathLen_b, sizeOfChar);
      stringConcat(resolvedFilePath, updatedStartDir, filePathLen_b);
      stringConcat(resolvedFilePath, c_filePathAfterSlicingRelativeP,
                   filePathLen_b);
      free(updatedStartDir);
    }
    free(codegenDir);
  }
#undef XSTR
#undef STR
  return resolvedFilePath;
}

/*
 * Arguments    : const char *unSanitizedFilePath
 * Return Type  : char *
 */
char *sanitizeFilePathForHSP(const char *unSanitizedFilePath)
{
  char *sanitizedFilePath;
  char *stringDuplicate;
  size_t charIdx;
  size_t filePathLen;
  size_t sizeOfChar;
  filePathLen = strlen(unSanitizedFilePath) + 1;
  sizeOfChar = 1;
  stringDuplicate = (char *)calloc(filePathLen, sizeOfChar);
  stringConcat(stringDuplicate, unSanitizedFilePath, filePathLen);
  sanitizedFilePath = stringDuplicate;
  for (charIdx = 0; charIdx < strlen(unSanitizedFilePath); charIdx++) {
    char charToCheckFor;
    charToCheckFor = unSanitizedFilePath[charIdx];
    if (isspace(charToCheckFor)) {
      sanitizedFilePath[charIdx] = '_';
    }
  }
  return sanitizedFilePath;
}

/*
 * Arguments    : char *destinationString
 *                const char *sourceString
 *                size_t destBufferSize
 * Return Type  : void
 */
void stringConcat(char *destinationString, const char *sourceString,
                  size_t destBufferSize)
{
  size_t dstStringLen;
  size_t srcBuffIdx;
  dstStringLen = strlen(destinationString);
  srcBuffIdx = 0;
  while ((sourceString[srcBuffIdx] != '\x00') &&
         (dstStringLen < destBufferSize - 1)) {
    destinationString[dstStringLen] = sourceString[srcBuffIdx];
    dstStringLen++;
    srcBuffIdx++;
  }
  destinationString[dstStringLen] = '\x00';
}

/*
 * File trailer for predict_shufflenet_v5_rtwutil.c
 *
 * [EOF]
 */
