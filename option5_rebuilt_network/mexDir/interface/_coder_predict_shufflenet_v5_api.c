/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * _coder_predict_shufflenet_v5_api.c
 *
 * Code generation for function '_coder_predict_shufflenet_v5_api'
 *
 */

/* Include files */
#include "_coder_predict_shufflenet_v5_api.h"
#include "predict_shufflenet_v5.h"
#include "predict_shufflenet_v5_data.h"
#include "predict_shufflenet_v5_types.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static real32_T (
    *b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                        const emlrtMsgIdentifier *parentId))[150528];

static real32_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                     const emlrtMsgIdentifier *msgId))[150528];

static real32_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *nullptr,
                                   const char_T *identifier))[150528];

static const mxArray *emlrt_marshallOut(real32_T u[1000]);

/* Function Definitions */
static real32_T (
    *b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                        const emlrtMsgIdentifier *parentId))[150528]
{
  real32_T(*y)[150528];
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static real32_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                     const emlrtMsgIdentifier *msgId))[150528]
{
  static const int32_T dims[3] = {224, 224, 3};
  int32_T iv[3];
  real32_T(*ret)[150528];
  boolean_T bv[3] = {false, false, false};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "single", false, 3U,
                            (const void *)&dims[0], &bv[0], &iv[0]);
  ret = (real32_T(*)[150528])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real32_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *nullptr,
                                   const char_T *identifier))[150528]
{
  emlrtMsgIdentifier thisId;
  real32_T(*y)[150528];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(nullptr), &thisId);
  emlrtDestroyArray(&nullptr);
  return y;
}

static const mxArray *emlrt_marshallOut(real32_T u[1000])
{
  static const int32_T i = 0;
  static const int32_T i1 = 1000;
  const mxArray *m;
  const mxArray *y;
  void *existingData;
  y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxSINGLE_CLASS, mxREAL);
  existingData = emlrtMxGetData((mxArray *)m);
  if (existingData != (void *)&u[0]) {
    emlrtFreeMex(existingData);
  }
  emlrtMxSetData((mxArray *)m, &u[0]);
  emlrtSetDimensions((mxArray *)m, &i1, 1);
  emlrtAssign(&y, m);
  return y;
}

void predict_shufflenet_v5_api(predict_shufflenet_v5StackData *SD,
                               const mxArray *const prhs[1],
                               const mxArray **plhs)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  real32_T(*in)[150528];
  real32_T(*out)[1000];
  st.tls = emlrtRootTLSGlobal;
  out = (real32_T(*)[1000])mxMalloc(sizeof(real32_T[1000]));
  /* Marshall function inputs */
  in = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "in");
  /* Invoke the target function */
  predict_shufflenet_v5(SD, &st, *in, *out);
  /* Marshall function outputs */
  *plhs = emlrt_marshallOut(*out);
}

/* End of code generation (_coder_predict_shufflenet_v5_api.c) */
