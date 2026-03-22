/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 *
 * predict_shufflenet_v5_data.c
 *
 * Code generation for function 'predict_shufflenet_v5_data'
 *
 */

/* Include files */
#include "predict_shufflenet_v5_data.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

const volatile char_T *emlrtBreakCheckR2012bFlagVar = NULL;

emlrtContext emlrtContextGlobal = {
    true,                                                /* bFirstTime */
    false,                                               /* bInitialized */
    131690U,                                             /* fVersionInfo */
    NULL,                                                /* fErrorFunction */
    "predict_shufflenet_v5",                             /* fFunctionName */
    NULL,                                                /* fRTCallStack */
    false,                                               /* bDebugMode */
    {925302475U, 3951113832U, 2887047743U, 3194870166U}, /* fSigWrd */
    NULL                                                 /* fSigMem */
};

omp_lock_t emlrtLockGlobal;

omp_nest_lock_t predict_shufflenet_v5_nestLockGlobal;

/* End of code generation (predict_shufflenet_v5_data.c) */
