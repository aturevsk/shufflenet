/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: mInvoke_shufflenet_initialize.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:38:14
 */

/* Include Files */
#include "mInvoke_shufflenet_initialize.h"
#include "mInvoke_shufflenet.h"
#include "mInvoke_shufflenet_data.h"
#include "omp.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void mInvoke_shufflenet_initialize(void)
{
  omp_init_nest_lock(&mInvoke_shufflenet_nestLockGlobal);
  mInvoke_shufflenet_init();
  isInitialized_mInvoke_shufflenet = true;
}

/*
 * File trailer for mInvoke_shufflenet_initialize.c
 *
 * [EOF]
 */
