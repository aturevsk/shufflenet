/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: main.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 20-Mar-2026 21:31:49
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
#include "mInvoke_shufflenet.h"
#include "mInvoke_shufflenet_initialize.h"
#include "mInvoke_shufflenet_terminate.h"

/* Function Declarations */
static void argInit_1x3x224x224_real32_T(float result[150528]);

static float argInit_real32_T(void);

/* Function Definitions */
/*
 * Arguments    : float result[150528]
 * Return Type  : void
 */
static void argInit_1x3x224x224_real32_T(float result[150528])
{
  int idx1;
  int idx2;
  int idx3;
  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 3; idx1++) {
    for (idx2 = 0; idx2 < 224; idx2++) {
      for (idx3 = 0; idx3 < 224; idx3++) {
        /* Set the value of the array element.
Change this value to the value that the application requires. */
        result[(idx1 + 3 * idx2) + 672 * idx3] = argInit_real32_T();
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
  mInvoke_shufflenet_initialize();
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_mInvoke_shufflenet();
  /* Terminate the application.
You do not need to do this more than one time. */
  mInvoke_shufflenet_terminate();
  return 0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void main_mInvoke_shufflenet(void)
{
  static float fv[150528];
  float out[1000];
  /* Initialize function 'mInvoke_shufflenet' input arguments. */
  /* Initialize function input argument 'input'. */
  /* Call the entry-point 'mInvoke_shufflenet'. */
  argInit_1x3x224x224_real32_T(fv);
  mInvoke_shufflenet(fv, out);
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
