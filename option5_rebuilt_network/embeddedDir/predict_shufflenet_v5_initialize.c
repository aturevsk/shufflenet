/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: predict_shufflenet_v5_initialize.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:41:39
 */

/* Include Files */
#include "predict_shufflenet_v5_initialize.h"
#include "predict_shufflenet_v5_data.h"
#include "omp.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void predict_shufflenet_v5_initialize(void)
{
  omp_init_nest_lock(&predict_shufflenet_v5_nestLockGlobal);
  isInitialized_predict_shufflenet_v5 = true;
}

/*
 * File trailer for predict_shufflenet_v5_initialize.c
 *
 * [EOF]
 */
