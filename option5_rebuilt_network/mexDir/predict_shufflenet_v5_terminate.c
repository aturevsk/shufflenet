/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * predict_shufflenet_v5_terminate.c
 *
 * Code generation for function 'predict_shufflenet_v5_terminate'
 *
 */

/* Include files */
#include "predict_shufflenet_v5_terminate.h"
#include "_coder_predict_shufflenet_v5_mex.h"
#include "predict_shufflenet_v5_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Declarations */
static void emlrtExitTimeCleanupDtorFcn(const void *r);

/* Function Definitions */
static void emlrtExitTimeCleanupDtorFcn(const void *r)
{
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void predict_shufflenet_v5_atexit(void)
{
  static jmp_buf emlrtJBEnviron;
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  /* Initialize the memory manager. */
  omp_init_lock(&emlrtLockGlobal);
  omp_init_nest_lock(&predict_shufflenet_v5_nestLockGlobal);
  st.tls = emlrtRootTLSGlobal;
  emlrtSetJmpBuf(&st, &emlrtJBEnviron);
  if (setjmp(emlrtJBEnviron) == 0) {
    emlrtPushHeapReferenceStackR2021a(&st, false, NULL,
                                      (void *)&emlrtExitTimeCleanupDtorFcn,
                                      NULL, NULL, NULL);
    emlrtEnterRtStackR2012b(&st);
    emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
    emlrtExitTimeCleanup(&emlrtContextGlobal);
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&predict_shufflenet_v5_nestLockGlobal);
  } else {
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&predict_shufflenet_v5_nestLockGlobal);
    emlrtReportParallelRunTimeError(&st);
  }
}

void predict_shufflenet_v5_terminate(void)
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (predict_shufflenet_v5_terminate.c) */
