/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: _coder_mInvoke_shufflenet_api.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:38:14
 */

/* Include Files */
#include "_coder_mInvoke_shufflenet_api.h"
#include "_coder_mInvoke_shufflenet_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

emlrtContext emlrtContextGlobal = {
    true,                                                 /* bFirstTime */
    false,                                                /* bInitialized */
    131690U,                                              /* fVersionInfo */
    NULL,                                                 /* fErrorFunction */
    "mInvoke_shufflenet",                                 /* fFunctionName */
    NULL,                                                 /* fRTCallStack */
    false,                                                /* bDebugMode */
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, /* fSigWrd */
    NULL                                                  /* fSigMem */
};

/* Function Declarations */
static real32_T (
    *b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                        const emlrtMsgIdentifier *parentId))[150528];

static real32_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                     const emlrtMsgIdentifier *msgId))[150528];

static void emlrtExitTimeCleanupDtorFcn(const void *r);

static real32_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *nullptr,
                                   const char_T *identifier))[150528];

static const mxArray *emlrt_marshallOut(real32_T u[1000]);

/* Function Definitions */
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real32_T (*)[150528]
 */
static real32_T (
    *b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                        const emlrtMsgIdentifier *parentId))[150528]
{
  real32_T(*y)[150528];
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real32_T (*)[150528]
 */
static real32_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                     const emlrtMsgIdentifier *msgId))[150528]
{
  static const int32_T dims[4] = {1, 3, 224, 224};
  int32_T iv[4];
  real32_T(*ret)[150528];
  boolean_T bv[4] = {false, false, false, false};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "single", false, 4U,
                            (const void *)&dims[0], &bv[0], &iv[0]);
  ret = (real32_T(*)[150528])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const void *r
 * Return Type  : void
 */
static void emlrtExitTimeCleanupDtorFcn(const void *r)
{
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *nullptr
 *                const char_T *identifier
 * Return Type  : real32_T (*)[150528]
 */
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

/*
 * Arguments    : real32_T u[1000]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(real32_T u[1000])
{
  static const int32_T iv[2] = {0, 0};
  static const int32_T iv1[2] = {1, 1000};
  const mxArray *m;
  const mxArray *y;
  void *existingData;
  y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxSINGLE_CLASS, mxREAL);
  existingData = emlrtMxGetData((mxArray *)m);
  if (existingData != (void *)&u[0]) {
    emlrtFreeMex(existingData);
  }
  emlrtMxSetData((mxArray *)m, &u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const mxArray * const prhs[1]
 *                const mxArray **plhs
 * Return Type  : void
 */
void mInvoke_shufflenet_api(const mxArray *const prhs[1], const mxArray **plhs)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  real32_T(*input)[150528];
  real32_T(*out)[1000];
  st.tls = emlrtRootTLSGlobal;
  out = (real32_T(*)[1000])mxMalloc(sizeof(real32_T[1000]));
  /* Marshall function inputs */
  input = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "input");
  /* Invoke the target function */
  mInvoke_shufflenet(*input, *out);
  /* Marshall function outputs */
  *plhs = emlrt_marshallOut(*out);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void mInvoke_shufflenet_atexit(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtPushHeapReferenceStackR2021a(
      &st, false, NULL, (void *)&emlrtExitTimeCleanupDtorFcn, NULL, NULL, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  mInvoke_shufflenet_xil_terminate();
  mInvoke_shufflenet_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void mInvoke_shufflenet_initialize(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void mInvoke_shufflenet_terminate(void)
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_mInvoke_shufflenet_api.c
 *
 * [EOF]
 */
