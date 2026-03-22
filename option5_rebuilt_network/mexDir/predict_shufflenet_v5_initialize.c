/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * predict_shufflenet_v5_initialize.c
 *
 * Code generation for function 'predict_shufflenet_v5_initialize'
 *
 */

/* Include files */
#include "predict_shufflenet_v5_initialize.h"
#include "_coder_predict_shufflenet_v5_mex.h"
#include "predict_shufflenet_v5_data.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void predict_shufflenet_v5_once(void);

/* Function Definitions */
static void predict_shufflenet_v5_once(void)
{
  mex_InitInfAndNan();
}

void predict_shufflenet_v5_initialize(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2022b(&st);
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtLicenseCheckR2022a(&st, "EMLRT:runTime:MexFunctionNeedsLicense",
                          "neural_network_toolbox", 2);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    predict_shufflenet_v5_once();
  }
}

/* End of code generation (predict_shufflenet_v5_initialize.c) */
