/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * callPredict.c
 *
 * Code generation for function 'callPredict'
 *
 */

/* Include files */
#include "callPredict.h"
#include "ChannelShuffleLayer.h"
#include "ChannelSplitLayer.h"
#include "FullyConnectedLayer.h"
#include "cat.h"
#include "conv2dDirectOptimizedColMajor.h"
#include "poolingOperation.h"
#include "predict_shufflenet_v5_types.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
static emlrtRSInfo b_emlrtRSI = {
    1,                                          /* lineNo */
    "Convolution2DBatchNormActivation/predict", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+layer/Convolution2DBatchNormActivation.p" /* pathName
                                                                          */
};

static emlrtRSInfo c_emlrtRSI = {
    1,                    /* lineNo */
    "computeConvolution", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+layer/+convUtils/computeConvolution.p" /* pathName
                                                                       */
};

static emlrtRSInfo g_emlrtRSI = {
    1,                       /* lineNo */
    "dlnetwork/callPredict", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+ctarget/@dlnetwork/callPredict.p" /* pathName */
};

static emlrtRSInfo h_emlrtRSI = {
    61,               /* lineNo */
    "callActivation", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+ctarget/+networkUtils/callActivation.m" /* pathName
                                                                        */
};

static emlrtRSInfo i_emlrtRSI = {
    128,              /* lineNo */
    "getActivations", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+ctarget/+networkUtils/getActivations.m" /* pathName
                                                                        */
};

static emlrtRSInfo j_emlrtRSI = {
    91,               /* lineNo */
    "getActivations", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+ctarget/+networkUtils/getActivations.m" /* pathName
                                                                        */
};

static emlrtRSInfo k_emlrtRSI = {
    195,                       /* lineNo */
    "iInvokeLayerPredictCall", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+ctarget/+networkUtils/getActivations.m" /* pathName
                                                                        */
};

static emlrtRSInfo l_emlrtRSI = {
    199,                       /* lineNo */
    "iInvokeLayerPredictCall", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+ctarget/+networkUtils/getActivations.m" /* pathName
                                                                        */
};

static emlrtRSInfo m_emlrtRSI = {
    53,                  /* lineNo */
    "invokePredictCall", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+ctarget/+networkUtils/invokePredictCall.m" /* pathName
                                                                           */
};

static emlrtRSInfo n_emlrtRSI = {
    47,                  /* lineNo */
    "invokePredictCall", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+ctarget/+networkUtils/invokePredictCall.m" /* pathName
                                                                           */
};

static emlrtRSInfo o_emlrtRSI = {
    1,                                      /* lineNo */
    "coderNetworkUtils/customLayerPredict", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/@coderNetworkUtils/customLayerPredict.p" /* pathName
                                                                        */
};

static emlrtRSInfo p_emlrtRSI = {
    1,                        /* lineNo */
    "Pooling2DLayer/predict", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+layer/Pooling2DLayer.p" /* pathName */
};

static emlrtRSInfo q_emlrtRSI = {
    1,                     /* lineNo */
    "@(x)averageFactor*x", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+layer/+poolingUtils/poolingForward.p" /* pathName
                                                                      */
};

static emlrtRSInfo r_emlrtRSI = {
    1,                  /* lineNo */
    "poolingOperation", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+layer/+poolingUtils/poolingOperation.p" /* pathName
                                                                        */
};

static emlrtRSInfo w_emlrtRSI = {
    1,                                /* lineNo */
    "Convolution2DBatchNorm/predict", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+layer/Convolution2DBatchNorm.p" /* pathName */
};

static emlrtRSInfo x_emlrtRSI = {
    1,                       /* lineNo */
    "iCallLayerPredictImpl", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/@coderNetworkUtils/customLayerPredict.p" /* pathName
                                                                        */
};

static emlrtRSInfo bb_emlrtRSI = {
    1,                /* lineNo */
    "poolingForward", /* fcnName */
    "/Users/arkadiyturevskiy/Documents/MATLAB/SupportPackages/R2026aPrerelease/"
    "toolbox/shared/dlcoder_base/supportpackages/shared_dl_"
    "targets/+coder/+internal/+layer/+poolingUtils/poolingForward.p" /* pathName
                                                                      */
};

/* Function Definitions */
void predict(predict_shufflenet_v5StackData *SD, const emlrtStack *sp,
             const real32_T inputsT_0_f1[150528], real32_T outputs_0_f1[1000])
{
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  emlrtStack h_st;
  emlrtStack i_st;
  emlrtStack j_st;
  emlrtStack st;
  real32_T outT_f78_0_f1[11368];
  real32_T outT_f79_0_f1[11368];
  real32_T outT_f82_0_f1[11368];
  real32_T Z[1024];
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  g_st.prev = &f_st;
  g_st.tls = f_st.tls;
  h_st.prev = &g_st;
  h_st.tls = g_st.tls;
  i_st.prev = &h_st;
  i_st.tls = h_st.tls;
  j_st.prev = &i_st;
  j_st.tls = i_st.tls;
  st.site = &g_emlrtRSI;
  b_st.site = &h_emlrtRSI;
  c_st.site = &j_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  conv2dDirectOptimizedColMajor(&g_st, inputsT_0_f1, SD->f0.X);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  g_st.site = &o_emlrtRSI;
  h_st.site = &p_emlrtRSI;
  i_st.site = &q_emlrtRSI;
  j_st.site = &r_emlrtRSI;
  c_iPoolingForColumnMajorWithOpe(&j_st, SD->f0.X, SD->f0.Z);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  b_conv2dDirectOptimizedColMajor(&g_st, SD->f0.Z, SD->f0.outT_f4_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  c_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f4_0_f1,
                                  SD->f0.outT_f5_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  d_conv2dDirectOptimizedColMajor(&g_st, SD->f0.Z, SD->f0.outT_f6_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  e_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f6_0_f1,
                                  SD->f0.b_tempData);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  f_conv2dDirectOptimizedColMajor(&g_st, SD->f0.b_tempData,
                                  SD->f0.outT_f8_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  cat(SD->f0.outT_f5_0_f1, SD->f0.outT_f8_0_f1, SD->f0.outT_f31_0_f1);
  ChannelShuffleLayer_predict(SD->f0.outT_f31_0_f1, SD->f0.tempData);
  g_st.site = &x_emlrtRSI;
  ChannelSplitLayer_predict(SD->f0.tempData, SD->f0.outT_f11[0].f1,
                            SD->f0.outT_f11[1].f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  g_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f11[1].f1,
                                  SD->f0.outT_f5_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  h_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f5_0_f1,
                                  SD->f0.b_tempData);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  i_conv2dDirectOptimizedColMajor(&g_st, SD->f0.b_tempData,
                                  SD->f0.outT_f5_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  cat(SD->f0.outT_f11[0].f1, SD->f0.outT_f5_0_f1, SD->f0.outT_f31_0_f1);
  ChannelShuffleLayer_predict(SD->f0.outT_f31_0_f1, SD->f0.tempData);
  g_st.site = &x_emlrtRSI;
  ChannelSplitLayer_predict(SD->f0.tempData, SD->f0.outT_f11[0].f1,
                            SD->f0.outT_f11[1].f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  j_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f11[1].f1,
                                  SD->f0.outT_f5_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  k_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f5_0_f1,
                                  SD->f0.b_tempData);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  l_conv2dDirectOptimizedColMajor(&g_st, SD->f0.b_tempData,
                                  SD->f0.outT_f5_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  cat(SD->f0.outT_f11[0].f1, SD->f0.outT_f5_0_f1, SD->f0.outT_f31_0_f1);
  ChannelShuffleLayer_predict(SD->f0.outT_f31_0_f1, SD->f0.tempData);
  g_st.site = &x_emlrtRSI;
  ChannelSplitLayer_predict(SD->f0.tempData, SD->f0.outT_f11[0].f1,
                            SD->f0.outT_f11[1].f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  m_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f11[1].f1,
                                  SD->f0.outT_f5_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  n_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f5_0_f1,
                                  SD->f0.b_tempData);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  o_conv2dDirectOptimizedColMajor(&g_st, SD->f0.b_tempData,
                                  SD->f0.outT_f5_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  cat(SD->f0.outT_f11[0].f1, SD->f0.outT_f5_0_f1, SD->f0.outT_f31_0_f1);
  ChannelShuffleLayer_predict(SD->f0.outT_f31_0_f1, SD->f0.tempData);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  p_conv2dDirectOptimizedColMajor(&g_st, SD->f0.tempData, SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  q_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f29_0_f1,
                                  SD->f0.outT_f30_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  r_conv2dDirectOptimizedColMajor(&g_st, SD->f0.tempData, SD->f0.outT_f31_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  s_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f31_0_f1,
                                  SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  t_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f29_0_f1,
                                  SD->f0.outT_f33_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  b_cat(SD->f0.outT_f30_0_f1, SD->f0.outT_f33_0_f1, SD->f0.outT_f8_0_f1);
  b_ChannelShuffleLayer_predict(SD->f0.outT_f8_0_f1, SD->f0.outT_f5_0_f1);
  g_st.site = &x_emlrtRSI;
  b_ChannelSplitLayer_predict(SD->f0.outT_f5_0_f1, SD->f0.outT_f36[0].f1,
                              SD->f0.outT_f36[1].f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  u_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f36[1].f1,
                                  SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  v_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f29_0_f1,
                                  SD->f0.outT_f33_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  w_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f33_0_f1,
                                  SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  b_cat(SD->f0.outT_f36[0].f1, SD->f0.outT_f29_0_f1, SD->f0.outT_f8_0_f1);
  b_ChannelShuffleLayer_predict(SD->f0.outT_f8_0_f1, SD->f0.outT_f5_0_f1);
  g_st.site = &x_emlrtRSI;
  b_ChannelSplitLayer_predict(SD->f0.outT_f5_0_f1, SD->f0.outT_f36[0].f1,
                              SD->f0.outT_f36[1].f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  x_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f36[1].f1,
                                  SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  y_conv2dDirectOptimizedColMajor(&g_st, SD->f0.outT_f29_0_f1,
                                  SD->f0.outT_f33_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  ab_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f33_0_f1,
                                  SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  b_cat(SD->f0.outT_f36[0].f1, SD->f0.outT_f29_0_f1, SD->f0.outT_f8_0_f1);
  b_ChannelShuffleLayer_predict(SD->f0.outT_f8_0_f1, SD->f0.outT_f5_0_f1);
  g_st.site = &x_emlrtRSI;
  b_ChannelSplitLayer_predict(SD->f0.outT_f5_0_f1, SD->f0.outT_f36[0].f1,
                              SD->f0.outT_f36[1].f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  bb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f36[1].f1,
                                  SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  cb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f29_0_f1,
                                  SD->f0.outT_f33_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  db_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f33_0_f1,
                                  SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  b_cat(SD->f0.outT_f36[0].f1, SD->f0.outT_f29_0_f1, SD->f0.outT_f8_0_f1);
  b_ChannelShuffleLayer_predict(SD->f0.outT_f8_0_f1, SD->f0.outT_f5_0_f1);
  g_st.site = &x_emlrtRSI;
  b_ChannelSplitLayer_predict(SD->f0.outT_f5_0_f1, SD->f0.outT_f36[0].f1,
                              SD->f0.outT_f36[1].f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  eb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f36[1].f1,
                                  SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  fb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f29_0_f1,
                                  SD->f0.outT_f33_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  gb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f33_0_f1,
                                  SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  b_cat(SD->f0.outT_f36[0].f1, SD->f0.outT_f29_0_f1, SD->f0.outT_f8_0_f1);
  b_ChannelShuffleLayer_predict(SD->f0.outT_f8_0_f1, SD->f0.outT_f5_0_f1);
  g_st.site = &x_emlrtRSI;
  b_ChannelSplitLayer_predict(SD->f0.outT_f5_0_f1, SD->f0.outT_f36[0].f1,
                              SD->f0.outT_f36[1].f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  hb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f36[1].f1,
                                  SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  ib_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f29_0_f1,
                                  SD->f0.outT_f33_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  jb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f33_0_f1,
                                  SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  b_cat(SD->f0.outT_f36[0].f1, SD->f0.outT_f29_0_f1, SD->f0.outT_f8_0_f1);
  b_ChannelShuffleLayer_predict(SD->f0.outT_f8_0_f1, SD->f0.outT_f5_0_f1);
  g_st.site = &x_emlrtRSI;
  b_ChannelSplitLayer_predict(SD->f0.outT_f5_0_f1, SD->f0.outT_f36[0].f1,
                              SD->f0.outT_f36[1].f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  kb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f36[1].f1,
                                  SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  lb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f29_0_f1,
                                  SD->f0.outT_f33_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  mb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f33_0_f1,
                                  SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  b_cat(SD->f0.outT_f36[0].f1, SD->f0.outT_f29_0_f1, SD->f0.outT_f8_0_f1);
  b_ChannelShuffleLayer_predict(SD->f0.outT_f8_0_f1, SD->f0.outT_f5_0_f1);
  g_st.site = &x_emlrtRSI;
  b_ChannelSplitLayer_predict(SD->f0.outT_f5_0_f1, SD->f0.outT_f36[0].f1,
                              SD->f0.outT_f36[1].f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  nb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f36[1].f1,
                                  SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  ob_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f29_0_f1,
                                  SD->f0.outT_f33_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  pb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f33_0_f1,
                                  SD->f0.outT_f29_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  b_cat(SD->f0.outT_f36[0].f1, SD->f0.outT_f29_0_f1, SD->f0.outT_f8_0_f1);
  b_ChannelShuffleLayer_predict(SD->f0.outT_f8_0_f1, SD->f0.b_tempData);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  qb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.b_tempData, outT_f78_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  rb_conv2dDirectOptimizedColMajo(&g_st, outT_f78_0_f1, outT_f79_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  sb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.b_tempData,
                                  SD->f0.outT_f5_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  tb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f5_0_f1, outT_f78_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  ub_conv2dDirectOptimizedColMajo(&g_st, outT_f78_0_f1, outT_f82_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  c_cat(outT_f79_0_f1, outT_f82_0_f1, SD->f0.outT_f30_0_f1);
  c_ChannelShuffleLayer_predict(SD->f0.outT_f30_0_f1, SD->f0.outT_f33_0_f1);
  g_st.site = &x_emlrtRSI;
  c_ChannelSplitLayer_predict(SD->f0.outT_f33_0_f1, SD->f0.outT_f85[0].f1,
                              SD->f0.outT_f85[1].f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  vb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f85[1].f1, outT_f78_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  wb_conv2dDirectOptimizedColMajo(&g_st, outT_f78_0_f1, outT_f82_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  xb_conv2dDirectOptimizedColMajo(&g_st, outT_f82_0_f1, outT_f78_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  c_cat(SD->f0.outT_f85[0].f1, outT_f78_0_f1, SD->f0.outT_f30_0_f1);
  c_ChannelShuffleLayer_predict(SD->f0.outT_f30_0_f1, SD->f0.outT_f33_0_f1);
  g_st.site = &x_emlrtRSI;
  c_ChannelSplitLayer_predict(SD->f0.outT_f33_0_f1, SD->f0.outT_f85[0].f1,
                              SD->f0.outT_f85[1].f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  yb_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f85[1].f1, outT_f78_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  ac_conv2dDirectOptimizedColMajo(&g_st, outT_f78_0_f1, outT_f82_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  bc_conv2dDirectOptimizedColMajo(&g_st, outT_f82_0_f1, outT_f78_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  c_cat(SD->f0.outT_f85[0].f1, outT_f78_0_f1, SD->f0.outT_f30_0_f1);
  c_ChannelShuffleLayer_predict(SD->f0.outT_f30_0_f1, SD->f0.outT_f33_0_f1);
  g_st.site = &x_emlrtRSI;
  c_ChannelSplitLayer_predict(SD->f0.outT_f33_0_f1, SD->f0.outT_f85[0].f1,
                              SD->f0.outT_f85[1].f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  cc_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f85[1].f1, outT_f78_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &w_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  dc_conv2dDirectOptimizedColMajo(&g_st, outT_f78_0_f1, outT_f82_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  g_st.site = &c_emlrtRSI;
  ec_conv2dDirectOptimizedColMajo(&g_st, outT_f82_0_f1, outT_f78_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &m_emlrtRSI;
  f_st.site = &b_emlrtRSI;
  c_cat(SD->f0.outT_f85[0].f1, outT_f78_0_f1, SD->f0.outT_f30_0_f1);
  c_ChannelShuffleLayer_predict(SD->f0.outT_f30_0_f1, SD->f0.outT_f33_0_f1);
  g_st.site = &c_emlrtRSI;
  fc_conv2dDirectOptimizedColMajo(&g_st, SD->f0.outT_f33_0_f1, SD->f0.b_X);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  g_st.site = &x_emlrtRSI;
  h_st.site = &p_emlrtRSI;
  i_st.site = &bb_emlrtRSI;
  j_st.site = &r_emlrtRSI;
  d_iPoolingForColumnMajorWithOpe(&j_st, SD->f0.b_X, Z);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
  d_st.site = &l_emlrtRSI;
  e_st.site = &n_emlrtRSI;
  f_st.site = &o_emlrtRSI;
  g_st.site = &x_emlrtRSI;
  FullyConnectedLayer_predict(&g_st, Z, outputs_0_f1);
  c_st.site = &i_emlrtRSI;
  d_st.site = &k_emlrtRSI;
}

/* End of code generation (callPredict.c) */
