/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * addBiasApplyActivation.c
 *
 * Code generation for function 'addBiasApplyActivation'
 *
 */

/* Include files */
#include "addBiasApplyActivation.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
void addBiasApplyActivation(const emlrtStack *sp, real32_T X[1000],
                            const real32_T bias[1000])
{
  jmp_buf emlrtJBEnviron;
  jmp_buf *volatile emlrtJBStack;
  emlrtStack st;
  int32_T addBiasApplyActivation_numThreads;
  int32_T iElem;
  boolean_T emlrtHadParallelError = false;
  emlrtEnterParallelRegion((emlrtCTX)sp, omp_in_parallel());
  emlrtPushJmpBuf((emlrtCTX)sp, &emlrtJBStack);
  addBiasApplyActivation_numThreads = emlrtAllocRegionTLSs(
      sp->tls, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs());
#pragma omp parallel num_threads(addBiasApplyActivation_numThreads) private(   \
        st, emlrtJBEnviron) firstprivate(emlrtHadParallelError)
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
    for (iElem = 0; iElem < 1000; iElem++) {
      if (emlrtHadParallelError) {
        continue;
      }
      if (setjmp(emlrtJBEnviron) == 0) {
        X[iElem] += bias[iElem];
      } else {
        emlrtHadParallelError = true;
      }
    }
  }
  emlrtPopJmpBuf((emlrtCTX)sp, &emlrtJBStack);
  emlrtExitParallelRegion((emlrtCTX)sp, omp_in_parallel());
}

/* End of code generation (addBiasApplyActivation.c) */
