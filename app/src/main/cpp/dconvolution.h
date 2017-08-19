/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * dconvolution.h
 *
 * Code generation for function 'dconvolution'
 *
 */

#ifndef DCONVOLUTION_H
#define DCONVOLUTION_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "dconvolution_types.h"

/* Function Declarations */
extern void dconvolution(const emxArray_real_T *x, const emxArray_real_T *h,
  double s, emxArray_real_T *b, emxArray_real_T *e, emxArray_real_T *m, double
  *i, emxArray_real_T *y);

#endif

/* End of code generation (dconvolution.h) */
