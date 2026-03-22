/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * _coder_predict_shufflenet_v5_mex.c
 *
 * Code generation for function '_coder_predict_shufflenet_v5_mex'
 *
 */

/* Include files */
#include "_coder_predict_shufflenet_v5_mex.h"
#include "_coder_predict_shufflenet_v5_api.h"
#include "predict_shufflenet_v5.h"
#include "predict_shufflenet_v5_data.h"
#include "predict_shufflenet_v5_initialize.h"
#include "predict_shufflenet_v5_terminate.h"
#include "predict_shufflenet_v5_types.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  static jmp_buf emlrtJBEnviron;
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  predict_shufflenet_v5StackData *c_predict_shufflenet_v5StackDat = NULL;
  c_predict_shufflenet_v5StackDat =
      (predict_shufflenet_v5StackData *)emlrtMxCalloc(
          (size_t)1, (size_t)1U * sizeof(predict_shufflenet_v5StackData));
  mexAtExit(&predict_shufflenet_v5_atexit);
  /* Initialize the memory manager. */
  omp_init_lock(&emlrtLockGlobal);
  omp_init_nest_lock(&predict_shufflenet_v5_nestLockGlobal);
  predict_shufflenet_v5_initialize();
  st.tls = emlrtRootTLSGlobal;
  emlrtSetJmpBuf(&st, &emlrtJBEnviron);
  if (setjmp(emlrtJBEnviron) == 0) {
    predict_shufflenet_v5_mexFunction(c_predict_shufflenet_v5StackDat, nlhs,
                                      plhs, nrhs, prhs);
    predict_shufflenet_v5_terminate();
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&predict_shufflenet_v5_nestLockGlobal);
  } else {
    omp_destroy_lock(&emlrtLockGlobal);
    omp_destroy_nest_lock(&predict_shufflenet_v5_nestLockGlobal);
    emlrtReportParallelRunTimeError(&st);
  }
  emlrtMxFree(c_predict_shufflenet_v5StackDat);
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal,
                           &emlrtLockerFunction, omp_get_num_procs(), NULL,
                           "UTF-8", true);
  return emlrtRootTLSGlobal;
}

void predict_shufflenet_v5_mexFunction(predict_shufflenet_v5StackData *SD,
                                       int32_T nlhs, mxArray *plhs[1],
                                       int32_T nrhs, const mxArray *prhs[1])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  const mxArray *outputs;
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs != 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 1, 4,
                        21, "predict_shufflenet_v5");
  }
  if (nlhs > 1) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 21,
                        "predict_shufflenet_v5");
  }
  /* Call the function. */
  predict_shufflenet_v5_api(SD, prhs, &outputs);
  /* Copy over outputs to the caller. */
  emlrtReturnArrays(1, &plhs[0], &outputs);
}

/* End of code generation (_coder_predict_shufflenet_v5_mex.c) */
