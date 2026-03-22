/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: main.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:41:39
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "predict_shufflenet_v5.h"
#include "predict_shufflenet_v5_initialize.h"
#include "predict_shufflenet_v5_terminate.h"

/* Function Declarations */
static void argInit_224x224x3_real32_T(float result[150528]);

static float argInit_real32_T(void);

/* Function Definitions */
/*
 * Arguments    : float result[150528]
 * Return Type  : void
 */
static void argInit_224x224x3_real32_T(float result[150528])
{
  int idx0;
  int idx1;
  int idx2;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 224; idx0++) {
    for (idx1 = 0; idx1 < 224; idx1++) {
      for (idx2 = 0; idx2 < 3; idx2++) {
        /* Set the value of the array element.
Change this value to the value that the application requires. */
        result[(idx0 + 224 * idx1) + 50176 * idx2] = argInit_real32_T();
      }
    }
  }
}

/*
 * Arguments    : void
 * Return Type  : float
 */
static float argInit_real32_T(void)
{
  return 0.0F;
}

/*
 * Arguments    : int argc
 *                char **argv
 * Return Type  : int
 */
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* Initialize the application.
You do not need to do this more than one time. */
  predict_shufflenet_v5_initialize();
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_predict_shufflenet_v5();
  /* Terminate the application.
You do not need to do this more than one time. */
  predict_shufflenet_v5_terminate();
  return 0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void main_predict_shufflenet_v5(void)
{
  static float fv[150528];
  float out[1000];
  /* Initialize function 'predict_shufflenet_v5' input arguments. */
  /* Initialize function input argument 'in'. */
  /* Call the entry-point 'predict_shufflenet_v5'. */
  argInit_224x224x3_real32_T(fv);
  predict_shufflenet_v5(fv, out);
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
