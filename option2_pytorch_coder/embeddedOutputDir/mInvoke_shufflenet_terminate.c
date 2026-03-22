/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: mInvoke_shufflenet_terminate.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:38:14
 */

/* Include Files */
#include "mInvoke_shufflenet_terminate.h"
#include "mInvoke_shufflenet_data.h"
#include "omp.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void mInvoke_shufflenet_terminate(void)
{
  omp_destroy_nest_lock(&mInvoke_shufflenet_nestLockGlobal);
  isInitialized_mInvoke_shufflenet = false;
}

/*
 * File trailer for mInvoke_shufflenet_terminate.c
 *
 * [EOF]
 */
