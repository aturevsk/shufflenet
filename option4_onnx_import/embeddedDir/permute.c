/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: permute.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 22-Mar-2026 12:35:57
 */

/* Include Files */
#include "permute.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const float a[90944]
 *                float b[90944]
 * Return Type  : void
 */
void b_permute(const float a[90944], float b[90944])
{
  int b_k;
  int c_k;
  int k;
  for (k = 0; k < 2; k++) {
    for (b_k = 0; b_k < 58; b_k++) {
      for (c_k = 0; c_k < 28; c_k++) {
        memcpy(&b[(k * 784 + b_k * 1568) + c_k * 28],
               &a[(k * 45472 + b_k * 784) + c_k * 28], 28U * sizeof(float));
      }
    }
  }
}

/*
 * Arguments    : const float a[45472]
 *                float b[45472]
 * Return Type  : void
 */
void c_permute(const float a[45472], float b[45472])
{
  int b_k;
  int c_k;
  int k;
  for (k = 0; k < 58; k++) {
    for (b_k = 0; b_k < 28; b_k++) {
      for (c_k = 0; c_k < 28; c_k++) {
        b[(b_k + 28 * c_k) + 784 * k] = a[(c_k + 28 * b_k) + 784 * k];
      }
    }
  }
}

/*
 * Arguments    : const float a[45472]
 *                float b[45472]
 * Return Type  : void
 */
void d_permute(const float a[45472], float b[45472])
{
  int b_k;
  int c_k;
  int k;
  for (k = 0; k < 232; k++) {
    for (b_k = 0; b_k < 14; b_k++) {
      for (c_k = 0; c_k < 14; c_k++) {
        b[(b_k + 14 * c_k) + 196 * k] = a[(c_k + 14 * b_k) + 196 * k];
      }
    }
  }
}

/*
 * Arguments    : const float a[45472]
 *                float b[45472]
 * Return Type  : void
 */
void e_permute(const float a[45472], float b[45472])
{
  int b_k;
  int c_k;
  int d_k;
  int k;
  for (k = 0; k < 2; k++) {
    for (b_k = 0; b_k < 116; b_k++) {
      for (c_k = 0; c_k < 14; c_k++) {
        for (d_k = 0; d_k < 14; d_k++) {
          int b_tmp;
          b_tmp = d_k + 14 * c_k;
          b[(b_tmp + 196 * k) + 392 * b_k] = a[(b_tmp + 196 * b_k) + 22736 * k];
        }
      }
    }
  }
}

/*
 * Arguments    : const float a[22736]
 *                float b[22736]
 * Return Type  : void
 */
void f_permute(const float a[22736], float b[22736])
{
  int b_k;
  int c_k;
  int k;
  for (k = 0; k < 116; k++) {
    for (b_k = 0; b_k < 14; b_k++) {
      for (c_k = 0; c_k < 14; c_k++) {
        b[(b_k + 14 * c_k) + 196 * k] = a[(c_k + 14 * b_k) + 196 * k];
      }
    }
  }
}

/*
 * Arguments    : const float a[22736]
 *                float b[22736]
 * Return Type  : void
 */
void g_permute(const float a[22736], float b[22736])
{
  int b_k;
  int c_k;
  int k;
  for (k = 0; k < 464; k++) {
    for (b_k = 0; b_k < 7; b_k++) {
      for (c_k = 0; c_k < 7; c_k++) {
        b[(b_k + 7 * c_k) + 49 * k] = a[(c_k + 7 * b_k) + 49 * k];
      }
    }
  }
}

/*
 * Arguments    : const float a[22736]
 *                float b[22736]
 * Return Type  : void
 */
void h_permute(const float a[22736], float b[22736])
{
  int b_k;
  int c_k;
  int d_k;
  int k;
  for (k = 0; k < 2; k++) {
    for (b_k = 0; b_k < 232; b_k++) {
      for (c_k = 0; c_k < 7; c_k++) {
        for (d_k = 0; d_k < 7; d_k++) {
          int b_tmp;
          b_tmp = d_k + 7 * c_k;
          b[(b_tmp + 49 * k) + 98 * b_k] = a[(b_tmp + 49 * b_k) + 11368 * k];
        }
      }
    }
  }
}

/*
 * Arguments    : const float a[11368]
 *                float b[11368]
 * Return Type  : void
 */
void i_permute(const float a[11368], float b[11368])
{
  int b_k;
  int c_k;
  int k;
  for (k = 0; k < 232; k++) {
    for (b_k = 0; b_k < 7; b_k++) {
      for (c_k = 0; c_k < 7; c_k++) {
        b[(b_k + 7 * c_k) + 49 * k] = a[(c_k + 7 * b_k) + 49 * k];
      }
    }
  }
}

/*
 * Arguments    : const float a[50176]
 *                float b[50176]
 * Return Type  : void
 */
void j_permute(const float a[50176], float b[50176])
{
  int b_k;
  int c_k;
  int k;
  for (k = 0; k < 1024; k++) {
    for (b_k = 0; b_k < 7; b_k++) {
      for (c_k = 0; c_k < 7; c_k++) {
        b[(b_k + 7 * c_k) + 49 * k] = a[(c_k + 7 * b_k) + 49 * k];
      }
    }
  }
}

/*
 * Arguments    : const float a[90944]
 *                float b[90944]
 * Return Type  : void
 */
void permute(const float a[90944], float b[90944])
{
  int b_k;
  int c_k;
  int k;
  for (k = 0; k < 116; k++) {
    for (b_k = 0; b_k < 28; b_k++) {
      for (c_k = 0; c_k < 28; c_k++) {
        b[(b_k + 28 * c_k) + 784 * k] = a[(c_k + 28 * b_k) + 784 * k];
      }
    }
  }
}

/*
 * File trailer for permute.c
 *
 * [EOF]
 */
