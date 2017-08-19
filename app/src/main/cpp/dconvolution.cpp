/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * dconvolution.cpp
 *
 * Code generation for function 'dconvolution'
 *
 */

/* Include files */
#include "dconvolution.h"
#include "dconvolution_emxutil.h"
#include "repmat.h"
#include "padarray.h"

/* Function Definitions */
void dconvolution(const emxArray_real_T *x, const emxArray_real_T *h, double s,
                  emxArray_real_T *b, emxArray_real_T *e, emxArray_real_T *m,
                  double *i, emxArray_real_T *y)
{
  emxArray_real_T *a;
  double dv0[2];
  int b_j1;
  int nd2;
  emxArray_real_T *d;
  int nA;
  double xtmp;
  int nB;
  unsigned int padSize[2];
  unsigned int uv0[2];
  emxInit_real_T(&a, 2);

  /* adjusting original x */
  dv0[0] = 0.0;
  dv0[1] = h->size[1];
  padarray(x, dv0, a);
  dv0[0] = 0.0;
  dv0[1] = h->size[1];
  b_padarray(a, dv0, b);

  /*  b does not change further */
  /* adjusting original h */
  b_j1 = a->size[0] * a->size[1];
  a->size[0] = 1;
  a->size[1] = h->size[1];
  emxEnsureCapacity((emxArray__common *)a, b_j1, sizeof(double));
  nd2 = h->size[0] * h->size[1];
  for (b_j1 = 0; b_j1 < nd2; b_j1++) {
    a->data[b_j1] = h->data[b_j1];
  }

  nd2 = h->size[1] >> 1;
  for (b_j1 = 1; b_j1 <= nd2; b_j1++) {
    nA = h->size[1] - b_j1;
    xtmp = a->data[b_j1 - 1];
    a->data[b_j1 - 1] = a->data[nA];
    a->data[nA] = xtmp;
  }

  emxInit_real_T(&d, 2);
  dv0[0] = 0.0;
  dv0[1] = (double)((unsigned int)h->size[1] + x->size[1]) - s;
  padarray(a, dv0, d);
  dv0[0] = 0.0;
  dv0[1] = s;
  b_padarray(d, dv0, e);
  nA = x->size[1];
  nB = h->size[1];
  nd2 = x->size[1] + h->size[1];
  emxFree_real_T(&d);
  if ((x->size[1] == 0) || (h->size[1] == 0)) {
  } else {
    nd2--;
  }

  b_j1 = a->size[0] * a->size[1];
  a->size[0] = 1;
  a->size[1] = nd2;
  emxEnsureCapacity((emxArray__common *)a, b_j1, sizeof(double));
  for (b_j1 = 0; b_j1 < nd2; b_j1++) {
    a->data[b_j1] = 0.0;
  }

  if ((x->size[1] > 0) && (h->size[1] > 0)) {
    if (h->size[1] > x->size[1]) {
      for (nd2 = 0; nd2 + 1 <= nA; nd2++) {
        for (b_j1 = 0; b_j1 < nB; b_j1++) {
          a->data[nd2 + b_j1] += x->data[nd2] * h->data[b_j1];
        }
      }
    } else {
      for (nd2 = 0; nd2 + 1 <= nB; nd2++) {
        for (b_j1 = 0; b_j1 < nA; b_j1++) {
          a->data[nd2 + b_j1] += h->data[nd2] * x->data[b_j1];
        }
      }
    }
  }

  padSize[0] = 0U;
  padSize[1] = (unsigned int)h->size[1];
  if (a->size[1] == 0) {
    dv0[0] = 1.0;
    dv0[1] = a->size[1] + padSize[1];
    repmat(dv0, y);
  } else {
    for (b_j1 = 0; b_j1 < 2; b_j1++) {
      uv0[b_j1] = a->size[b_j1] + padSize[b_j1];
    }

    b_j1 = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)uv0[1];
    emxEnsureCapacity((emxArray__common *)y, b_j1, sizeof(double));
    for (nd2 = 0; nd2 < (int)padSize[1]; nd2++) {
      y->data[y->size[0] * nd2] = 0.0;
    }

    for (nd2 = 0; nd2 < a->size[1]; nd2++) {
      y->data[y->size[0] * (nd2 + (int)padSize[1])] = a->data[a->size[0] * nd2];
    }
  }

  emxFree_real_T(&a);

  /*  multiplication for the multiplication axis  */
  b_j1 = m->size[0] * m->size[1];
  m->size[0] = 1;
  m->size[1] = b->size[1];
  emxEnsureCapacity((emxArray__common *)m, b_j1, sizeof(double));
  nd2 = b->size[0] * b->size[1];
  for (b_j1 = 0; b_j1 < nd2; b_j1++) {
    m->data[b_j1] = b->data[b_j1] * e->data[b_j1];
  }

  *i = (double)h->size[1] + s;

  /* index of y  */
  /* y_dash(i)=sum(m); % show on the existing convolution with different color  */
  /*  plot y(i) on third plot */
}

/* End of code generation (dconvolution.cpp) */
