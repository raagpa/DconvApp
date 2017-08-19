/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * repmat.cpp
 *
 * Code generation for function 'repmat'
 *
 */

/* Include files */
#include "dconvolution.h"
#include "repmat.h"
#include "dconvolution_emxutil.h"

/* Function Definitions */
void repmat(const double varargin_1[2], emxArray_real_T *b)
{
  int i1;
  int loop_ub;
  i1 = b->size[0] * b->size[1];
  b->size[0] = 1;
  b->size[1] = (int)varargin_1[1];
  emxEnsureCapacity((emxArray__common *)b, i1, sizeof(double));
  loop_ub = (int)varargin_1[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    b->data[i1] = 0.0;
  }
}

/* End of code generation (repmat.cpp) */
