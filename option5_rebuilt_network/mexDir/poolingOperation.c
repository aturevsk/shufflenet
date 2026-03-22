/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * poolingOperation.c
 *
 * Code generation for function 'poolingOperation'
 *
 */

/* Include files */
#include "poolingOperation.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include "omp.h"

/* Variable Definitions */
static emlrtBCInfo emlrtBCI = {
    1,                  /* iFirst */
    112,                /* iLast */
    1,                  /* lineNo */
    1,                  /* colNo */
    "",                 /* aName */
    "poolingOperation", /* fName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+layer/+poolingUtils/poolingOperation.p", /* pName
                                                                         */
    0 /* checkKind */
};

/* Function Definitions */
void c_iPoolingForColumnMajorWithOpe(const emlrtStack *sp,
                                     const real32_T X[301056],
                                     real32_T Z[75264])
{
  jmp_buf emlrtJBEnviron;
  jmp_buf *volatile emlrtJBStack;
  emlrtStack st;
  int32_T c_iPoolingForColumnMajorWithOpe_numThreads;
  int32_T filterHeightIdx;
  int32_T filterWidthIdx;
  int32_T inputHeightIdx;
  int32_T inputHeightIdx_tmp;
  int32_T inputWidthIdx;
  int32_T inputWidthIdx_tmp;
  int32_T prodOutDimsIdx;
  int32_T varargout_7;
  real32_T inputPixel;
  real32_T opValue;
  boolean_T emlrtHadParallelError = false;
  emlrtEnterParallelRegion((emlrtCTX)sp, omp_in_parallel());
  emlrtPushJmpBuf((emlrtCTX)sp, &emlrtJBStack);
  c_iPoolingForColumnMajorWithOpe_numThreads = emlrtAllocRegionTLSs(
      sp->tls, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs());
#pragma omp parallel                                                           \
num_threads(c_iPoolingForColumnMajorWithOpe_numThreads) private(               \
        inputPixel, inputHeightIdx, inputWidthIdx, opValue, st,                \
            emlrtJBEnviron, varargout_7, inputHeightIdx_tmp,                   \
            inputWidthIdx_tmp, filterWidthIdx, filterHeightIdx)                \
    firstprivate(emlrtHadParallelError)
  {
    if (setjmp(emlrtJBEnviron) == 0) {
      st.prev = sp;
      st.tls = emlrtAllocTLS((emlrtCTX)sp, omp_get_thread_num());
      st.site = NULL;
      emlrtSetJmpBuf(&st, &emlrtJBEnviron);
    } else {
      emlrtHadParallelError = true;
    }
#pragma omp for nowait
    for (prodOutDimsIdx = 0; prodOutDimsIdx < 75264; prodOutDimsIdx++) {
      if (emlrtHadParallelError) {
        continue;
      }
      if (setjmp(emlrtJBEnviron) == 0) {
        inputWidthIdx = (int32_T)((uint32_T)prodOutDimsIdx / 3136U);
        varargout_7 = inputWidthIdx;
        inputHeightIdx = prodOutDimsIdx - inputWidthIdx * 3136;
        inputWidthIdx = inputHeightIdx / 56;
        inputHeightIdx -= inputWidthIdx * 56;
        inputHeightIdx_tmp = inputHeightIdx << 1;
        inputWidthIdx_tmp = inputWidthIdx << 1;
        opValue = -3.402823466E+38F;
        if ((inputHeightIdx_tmp > 0) && (inputWidthIdx_tmp > 0) &&
            (inputHeightIdx_tmp + 3 <= 112) && (inputWidthIdx_tmp + 3 <= 112)) {
          for (filterWidthIdx = 0; filterWidthIdx < 3; filterWidthIdx++) {
            inputWidthIdx = filterWidthIdx + inputWidthIdx_tmp;
            if (inputHeightIdx_tmp > 112) {
              emlrtDynamicBoundsCheckR2012b(inputHeightIdx_tmp, 1, 112,
                                            &emlrtBCI, &st);
            }
            if (inputWidthIdx > 112) {
              emlrtDynamicBoundsCheckR2012b(inputWidthIdx, 1, 112, &emlrtBCI,
                                            &st);
            }
            inputHeightIdx = (inputHeightIdx_tmp + 112 * (inputWidthIdx - 1)) +
                             12544 * varargout_7;
            opValue = muSingleScalarMax(opValue, X[inputHeightIdx - 1]);
            if (inputHeightIdx_tmp + 1 > 112) {
              emlrtDynamicBoundsCheckR2012b(inputHeightIdx_tmp + 1, 1, 112,
                                            &emlrtBCI, &st);
            }
            opValue = muSingleScalarMax(opValue, X[inputHeightIdx]);
            if (inputHeightIdx_tmp + 2 > 112) {
              emlrtDynamicBoundsCheckR2012b(inputHeightIdx_tmp + 2, 1, 112,
                                            &emlrtBCI, &st);
            }
            opValue = muSingleScalarMax(opValue, X[inputHeightIdx + 1]);
          }
        } else {
          for (filterWidthIdx = 0; filterWidthIdx < 3; filterWidthIdx++) {
            inputWidthIdx = filterWidthIdx + inputWidthIdx_tmp;
            for (filterHeightIdx = 0; filterHeightIdx < 3; filterHeightIdx++) {
              inputHeightIdx = filterHeightIdx + inputHeightIdx_tmp;
              if ((inputHeightIdx > 0) && (inputWidthIdx > 0) &&
                  (inputHeightIdx <= 112) && (inputWidthIdx <= 112)) {
                inputPixel = X[((inputHeightIdx + 112 * (inputWidthIdx - 1)) +
                                12544 * varargout_7) -
                               1];
              } else {
                inputPixel = -3.402823466E+38F;
              }
              opValue = muSingleScalarMax(opValue, inputPixel);
            }
          }
        }
        Z[prodOutDimsIdx] = opValue;
      } else {
        emlrtHadParallelError = true;
      }
    }
  }
  emlrtPopJmpBuf((emlrtCTX)sp, &emlrtJBStack);
  emlrtExitParallelRegion((emlrtCTX)sp, omp_in_parallel());
}

void d_iPoolingForColumnMajorWithOpe(const emlrtStack *sp,
                                     const real32_T X[50176], real32_T Z[1024])
{
  jmp_buf emlrtJBEnviron;
  jmp_buf *volatile emlrtJBStack;
  emlrtStack st;
  int32_T d_iPoolingForColumnMajorWithOpe_numThreads;
  int32_T filterHeightIdx;
  int32_T filterWidthIdx;
  int32_T prodOutDimsIdx;
  real32_T inputPixel;
  real32_T opValue;
  boolean_T emlrtHadParallelError = false;
  emlrtEnterParallelRegion((emlrtCTX)sp, omp_in_parallel());
  emlrtPushJmpBuf((emlrtCTX)sp, &emlrtJBStack);
  d_iPoolingForColumnMajorWithOpe_numThreads = emlrtAllocRegionTLSs(
      sp->tls, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs());
#pragma omp parallel                                                           \
num_threads(d_iPoolingForColumnMajorWithOpe_numThreads) private(               \
        inputPixel, opValue, st, emlrtJBEnviron, filterWidthIdx,               \
            filterHeightIdx) firstprivate(emlrtHadParallelError)
  {
    if (setjmp(emlrtJBEnviron) == 0) {
      st.prev = sp;
      st.tls = emlrtAllocTLS((emlrtCTX)sp, omp_get_thread_num());
      st.site = NULL;
      emlrtSetJmpBuf(&st, &emlrtJBEnviron);
    } else {
      emlrtHadParallelError = true;
    }
#pragma omp for nowait
    for (prodOutDimsIdx = 0; prodOutDimsIdx < 1024; prodOutDimsIdx++) {
      if (emlrtHadParallelError) {
        continue;
      }
      if (setjmp(emlrtJBEnviron) == 0) {
        opValue = 0.0F;
        for (filterWidthIdx = 0; filterWidthIdx < 7; filterWidthIdx++) {
          for (filterHeightIdx = 0; filterHeightIdx < 7; filterHeightIdx++) {
            inputPixel =
                X[(filterHeightIdx + 7 * filterWidthIdx) + 49 * prodOutDimsIdx];
            opValue += inputPixel;
          }
        }
        Z[prodOutDimsIdx] = 0.020408163F * opValue;
      } else {
        emlrtHadParallelError = true;
      }
    }
  }
  emlrtPopJmpBuf((emlrtCTX)sp, &emlrtJBStack);
  emlrtExitParallelRegion((emlrtCTX)sp, omp_in_parallel());
}

/* End of code generation (poolingOperation.c) */
