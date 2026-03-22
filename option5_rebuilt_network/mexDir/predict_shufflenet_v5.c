/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * predict_shufflenet_v5.c
 *
 * Code generation for function 'predict_shufflenet_v5'
 *
 */

/* Include files */
#include "predict_shufflenet_v5.h"
#include "callPredict.h"
#include "predict_shufflenet_v5_data.h"
#include "predict_shufflenet_v5_types.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Variable Definitions */
static emlrtRSInfo emlrtRSI = {
    20,                      /* lineNo */
    "predict_shufflenet_v5", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/Claude/PyTorch_Import_2/Shufflenet/"
    "option5_rebuilt_network/predict_shufflenet_v5.m" /* pathName */
};

static emlrtRSInfo f_emlrtRSI = {
    1,                   /* lineNo */
    "dlnetwork/predict", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+ctarget/@dlnetwork/predict.p" /* pathName */
};

/* Function Definitions */
emlrtCTX emlrtGetRootTLSGlobal(void)
{
  return emlrtRootTLSGlobal;
}

void emlrtLockerFunction(EmlrtLockeeFunction aLockee, emlrtConstCTX aTLS,
                         void *aData)
{
  omp_set_lock(&emlrtLockGlobal);
  emlrtCallLockeeFunction(aLockee, aTLS, aData);
  omp_unset_lock(&emlrtLockGlobal);
}

void predict_shufflenet_v5(predict_shufflenet_v5StackData *SD,
                           const emlrtStack *sp, const real32_T in[150528],
                           real32_T out[1000])
{
  emlrtStack b_st;
  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  /* predict_shufflenet_v5  Codegen entry point for Option 5 rebuilt ShuffleNet
   * V2. */
  /*  */
  /*    out = predict_shufflenet_v5(in) */
  /*  */
  /*    Input:  in  - single-precision [224 x 224 x 3 x N] image (SSCB) */
  /*    Output: out - single-precision [1000 x N] class scores */
  /*  */
  /*    The persistent network is loaded once from the saved .mat file. */
  /*    All custom layers (ChannelShuffleLayer, ChannelSplitLayer) are */
  /*    codegen-compatible, inheriting from nnet.layer.Layer directly. */
  /*  Wrap input as dlarray with SSCB format for the network */
  st.site = &emlrtRSI;
  b_st.site = &f_emlrtRSI;
  predict(SD, &b_st, in, out);
}

/* End of code generation (predict_shufflenet_v5.c) */
