/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * predict_shufflenet_v5_mexutil.c
 *
 * Code generation for function 'predict_shufflenet_v5_mexutil'
 *
 */

/* Include files */
#include "predict_shufflenet_v5_mexutil.h"
#include "rt_nonfinite.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Definitions */
char_T *computeFilePathUsingEnvVariable(const char_T *unresolvedFilePath)
{
  char_T *resolvedFilePath;
  char_T *stringDuplicate;
#if defined(MW_RUNTIME_DL_DATA_PATH)
  extern char *mwGetRuntimeDLDataPath(const char *);
  resolvedFilePath = mwGetRuntimeDLDataPath((char_T *)unresolvedFilePath);
#elif defined(MW_DL_DATA_PATH)
  resolvedFilePath = resolveBinaryFilePath(unresolvedFilePath);
#else
  char_T *coderDataPath;
  coderDataPath = getenv("CODER_DATA_PATH");
  if (coderDataPath != NULL) {
    resolvedFilePath = resolveBinaryFilePath(unresolvedFilePath);
  } else {
    size_t filePathLen;
    size_t sizeOfChar;
    filePathLen = strlen(unresolvedFilePath) + 1;
    sizeOfChar = 1;
    stringDuplicate = (char_T *)calloc(filePathLen, sizeOfChar);
    stringConcat(stringDuplicate, unresolvedFilePath, filePathLen);
    resolvedFilePath = stringDuplicate;
  }
#endif
  return resolvedFilePath;
}

char_T *extractCodegenFolderName(const char_T *filePath)
{
  int32_T posOfLastPathSeparator;
  char_T *codegenFolderName;
  size_t filePathLen;
  size_t sizeOfChar;
  /* this function allocates dynamic memory */
  filePathLen = strlen(filePath) + 1;
  sizeOfChar = 1;
  codegenFolderName = (char_T *)calloc(filePathLen, sizeOfChar);
  posOfLastPathSeparator = getPositionOfLastFileSeparator(filePath);
  if (posOfLastPathSeparator != -1) {
    strncpy(codegenFolderName, filePath, posOfLastPathSeparator);
    codegenFolderName[posOfLastPathSeparator] = '\x00';
  } else {
    codegenFolderName[0] = '.';
    codegenFolderName[1] = '\x00';
  }
  return codegenFolderName;
}

char_T *getCustomUserDataPathEnvVar(const char_T *unresolvedFilePath)
{
  const char_T *fileName;
  char_T *coderDataPath;
  char_T *resolvedFilePath;
  coderDataPath = getenv("CODER_DATA_PATH");
  if (coderDataPath != NULL) {
    int32_T posOfLastPathSeparator;
    size_t filePathLength;
    size_t sizeOfChar;
    posOfLastPathSeparator = getPositionOfLastFileSeparator(unresolvedFilePath);
    fileName = &unresolvedFilePath[posOfLastPathSeparator];
    filePathLength = (strlen(coderDataPath) + strlen(fileName)) + 1;
    sizeOfChar = 1;
    resolvedFilePath = (char_T *)calloc(filePathLength, sizeOfChar);
    stringConcat(resolvedFilePath, coderDataPath, filePathLength);
    stringConcat(resolvedFilePath, fileName, filePathLength);
  } else {
    resolvedFilePath = NULL;
  }
  return resolvedFilePath;
}

int32_T getPositionOfLastFileSeparator(const char_T *filePath)
{
  int32_T lastPathSeparatorUnix;
  int32_T posOfLastPathSeparator;
  const char_T *ptrToLastPathSeparator;
  lastPathSeparatorUnix = '/';
  ptrToLastPathSeparator = strrchr(filePath, lastPathSeparatorUnix);
  if (ptrToLastPathSeparator != NULL) {
    posOfLastPathSeparator = (int32_T)(ptrToLastPathSeparator - filePath);
  } else {
    int32_T lastPathSeparatorWindows;
    lastPathSeparatorWindows = '\\';
    ptrToLastPathSeparator = strrchr(filePath, lastPathSeparatorWindows);
    if (ptrToLastPathSeparator != NULL) {
      posOfLastPathSeparator = (int32_T)(ptrToLastPathSeparator - filePath);
    } else {
      posOfLastPathSeparator = -1;
    }
  }
  return posOfLastPathSeparator;
}

char_T *getRelativePathToParentFolder(const char_T *filePath)
{
  int32_T posOfLastPathSeparator;
  const char_T *fileName;
  const char_T *parentDir;
  char_T *resolvedFilePath;
  size_t filePathLength;
  size_t sizeOfChar;
  parentDir = "..";
  posOfLastPathSeparator = getPositionOfLastFileSeparator(filePath);
  fileName = &filePath[posOfLastPathSeparator];
  filePathLength = (strlen(parentDir) + strlen(fileName)) + 1;
  sizeOfChar = 1;
  resolvedFilePath = (char_T *)calloc(filePathLength, sizeOfChar);
  stringConcat(resolvedFilePath, parentDir, filePathLength);
  stringConcat(resolvedFilePath, fileName, filePathLength);
  return resolvedFilePath;
}

char_T *getResolvedFilePath(const char_T *unresolvedFilePath)
{
  const char_T *fileOpenMode;
  char_T *computedPathUsingEnvVars;
  char_T *pathUsingEnvVarAndSanitizedPath;
  char_T *relativePathToParent;
  char_T *resolvedFilePath;
  char_T *sanitizedFilePath;
  char_T *stringDuplicate;
  FILE *filePtr;
  resolvedFilePath = NULL;
  fileOpenMode = "rb";
  filePtr = fopen(unresolvedFilePath, fileOpenMode);
  if (filePtr) {
    size_t filePathLen;
    size_t sizeOfChar;
    filePathLen = strlen(unresolvedFilePath) + 1;
    sizeOfChar = 1;
    stringDuplicate = (char_T *)calloc(filePathLen, sizeOfChar);
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
            throwFileNotFoundErrorMessage(unresolvedFilePath,
                                          sanitizedFilePath);
          }
        }
      }
    }
  }
  return resolvedFilePath;
}

void readDnnConstants_real32_T(real32_T *inputBufferPtr,
                               const char_T *unresolvedFilePath,
                               int32_T numElementsToRead)
{
  int32_T elementSizeInBytes;
  const char_T *fileOpenMode;
  char_T *resolvedFilePath;
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

char_T *resolveBinaryFilePath(const char_T *unresolvedFilePath)
{
  const char_T *c_filePathAfterSlicingRelativeP;
  const char_T *c_leadingPathSeparatorUnixAndWi;
  const char_T *lastDirName;
  const char_T *lastPathSeparator;
  const char_T *mwDLDataPath;
  char_T *codegenDir;
  char_T *coderDataPath;
  char_T *resolvedFilePath;
  char_T *updatedStartDir;
  size_t sizeOfChar;
#define XSTR(x) #x
#define STR(x) XSTR(x)
  coderDataPath = getenv("CODER_DATA_PATH");
  sizeOfChar = 1;
  if (coderDataPath != NULL) {
    resolvedFilePath = getCustomUserDataPathEnvVar(unresolvedFilePath);
  } else {
    int32_T lastPathSeparatorWindows;
    size_t codegenDirLength;
    size_t posOfCodegenDir;
    size_t posOfLeadingPathSeparator;
    mwDLDataPath = STR(MW_DL_DATA_PATH);
    c_filePathAfterSlicingRelativeP = &unresolvedFilePath[2];
    c_leadingPathSeparatorUnixAndWi = "/\\";
    posOfLeadingPathSeparator = strcspn(c_filePathAfterSlicingRelativeP,
                                        c_leadingPathSeparatorUnixAndWi);
    codegenDirLength = posOfLeadingPathSeparator + 1;
    codegenDir = (char_T *)calloc(codegenDirLength, sizeOfChar);
    strncpy(codegenDir, c_filePathAfterSlicingRelativeP,
            posOfLeadingPathSeparator);
    lastPathSeparatorWindows = '\\';
    lastPathSeparator = strrchr(mwDLDataPath, lastPathSeparatorWindows);
    if (lastPathSeparator == NULL) {
      int32_T lastPathSeparatorUnix;
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
      resolvedFilePath = (char_T *)calloc(filePathLen_a, sizeOfChar);
      stringConcat(resolvedFilePath, mwDLDataPath, filePathLen_a);
      stringConcat(resolvedFilePath, c_filePathAfterSlicingRelativeP,
                   filePathLen_a);
    } else {
      size_t filePathLen_b;
      filePathLen_b = posOfCodegenDir + 1;
      updatedStartDir = (char_T *)calloc(filePathLen_b, sizeOfChar);
      strncpy(updatedStartDir, mwDLDataPath, posOfCodegenDir);
      filePathLen_b =
          (strlen(updatedStartDir) + strlen(c_filePathAfterSlicingRelativeP)) +
          1;
      resolvedFilePath = (char_T *)calloc(filePathLen_b, sizeOfChar);
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

char_T *sanitizeFilePathForHSP(const char_T *unSanitizedFilePath)
{
  char_T *sanitizedFilePath;
  char_T *stringDuplicate;
  size_t charIdx;
  size_t filePathLen;
  size_t sizeOfChar;
  filePathLen = strlen(unSanitizedFilePath) + 1;
  sizeOfChar = 1;
  stringDuplicate = (char_T *)calloc(filePathLen, sizeOfChar);
  stringConcat(stringDuplicate, unSanitizedFilePath, filePathLen);
  sanitizedFilePath = stringDuplicate;
  for (charIdx = 0; charIdx < strlen(unSanitizedFilePath); charIdx++) {
    char_T charToCheckFor;
    charToCheckFor = unSanitizedFilePath[charIdx];
    if (isspace(charToCheckFor)) {
      sanitizedFilePath[charIdx] = '_';
    }
  }
  return sanitizedFilePath;
}

void stringConcat(char_T *destinationString, const char_T *sourceString,
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

void throwFileNotFoundErrorMessage(const char_T *unresolvedFilePath,
                                   const char_T *sanitizedFilePath)
{
  char_T errorMessage[4096];
  const char_T *stringToConcat1;
  const char_T *stringToConcat2;
  const char_T *stringToConcat3;
  const char_T *stringToConcat4;
  char_T *b_codegenFolderName;
  char_T *codegenFolderName;
  memset(&errorMessage[0], '\x00', 4096U);
  codegenFolderName = extractCodegenFolderName(unresolvedFilePath);
  stringToConcat1 = "Unable to find the ";
  stringConcat(errorMessage, stringToConcat1, 4096U);
  stringConcat(errorMessage, unresolvedFilePath, 4096U);
  stringToConcat2 = " binary file in ";
  stringConcat(errorMessage, stringToConcat2, 4096U);
  stringConcat(errorMessage, codegenFolderName, 4096U);
  if (strcmp(unresolvedFilePath, sanitizedFilePath) != 0) {
    b_codegenFolderName = extractCodegenFolderName(sanitizedFilePath);
    stringToConcat3 = " or in ";
    stringConcat(errorMessage, stringToConcat3, 4096U);
    stringConcat(errorMessage, unresolvedFilePath, 4096U);
    free(b_codegenFolderName);
  }
  stringToConcat4 = ".";
  stringConcat(errorMessage, stringToConcat4, 4096U);
  free(codegenFolderName);
  mexErrMsgTxt(errorMessage);
}

/* End of code generation (predict_shufflenet_v5_mexutil.c) */
