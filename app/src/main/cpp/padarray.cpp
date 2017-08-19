/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * padarray.cpp
 *
 * Code generation for function 'padarray'
 *
 */

/* Include files */
#include "dconvolution.h"
#include "padarray.h"
#include "repmat.h"
#include "dconvolution_emxutil.h"
#include <android/log.h>

/* Function Definitions */
void b_padarray(const emxArray_real_T *varargin_1, const double varargin_2[2],
                emxArray_real_T *b)
{
  int j;
  double dv2[2];
  if (varargin_1->size[1] == 0) {
    dv2[0] = 1.0;
    dv2[1] = (double)varargin_1->size[1] + varargin_2[1];
    repmat(dv2, b);
    __android_log_print(ANDROID_LOG_ERROR,"padarray ", "%d\n", dv2[1]);

  } else {
    for (j = 0; j < 2; j++) {
      dv2[j] = (double)varargin_1->size[j] + varargin_2[j];
    }

    j = b->size[0] * b->size[1];
    b->size[0] = 1;
    b->size[1] = (int)dv2[1];
    emxEnsureCapacity((emxArray__common *)b, j, sizeof(double));
    for (j = 0; j < (int)varargin_2[1]; j++) {
      b->data[b->size[0] * j] = 0.0;
    }

    for (j = 0; j < varargin_1->size[1]; j++) {
      b->data[b->size[0] * (j + (int)varargin_2[1])] = varargin_1->
        data[varargin_1->size[0] * j];
    }
  }
}

void padarray(const emxArray_real_T *varargin_1, const double varargin_2[2],
              emxArray_real_T *b)
{
  int i0;
  double dv1[2];
  int j;
  if (varargin_1->size[1] == 0) {
    dv1[0] = 1.0;
    dv1[1] = (double)varargin_1->size[1] + varargin_2[1];
    repmat(dv1, b);
  } else {
    for (i0 = 0; i0 < 2; i0++) {
      dv1[i0] = (double)varargin_1->size[i0] + varargin_2[i0];
    }

    i0 = b->size[0] * b->size[1];
    b->size[0] = 1;
    b->size[1] = (int)dv1[1];
    emxEnsureCapacity((emxArray__common *)b, i0, sizeof(double));
    i0 = b->size[1];
    for (j = varargin_1->size[1]; j + 1 <= i0; j++) {
      b->data[b->size[0] * j] = 0.0;
    }

    for (j = 0; j < varargin_1->size[1]; j++) {
      b->data[b->size[0] * j] = varargin_1->data[varargin_1->size[0] * j];
    }
  }
}

/* End of code generation (padarray.cpp) */
