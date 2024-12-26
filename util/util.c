#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "util.h"
#define NR_END 1
#define FREE_ARG char*

//Error handler
void error(char error[]) {
  fprintf(stderr, "JACLAR runtime error...\n");
  fprintf(stderr, "%s\n", error);
  fprintf(stderr,"...exiting system\n");
  exit(1);
}

//alloc an fvector with range [nl..nh]
float *vector(long nl, long nh) {
  float *v;
  
  v = (float*)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(float)));
  if (!v) error("alloc failed -- vector()\n");
  return v-nl+NR_END;
}

//alloc an ivector with range [nl..nh]
int *ivector(long nl, long nh) {
  int *v;
  
  v = (int*)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(int)));
  if (!v) error("alloc failed -- ivector()\n");
  return v-nl+NR_END;
}

//alloc an cvector with range [nl..nh]
uc_t *cvector(long nl, long nh) {
  uc_t *v;

  v = (uc_t*)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(uc_t)));
  if (!v) error("alloc failed -- cvector()\n");
  return v-nl+NR_END;
}

//alloc an lvector with range [nl..nh]
ul_t *lvector(long nl, long nh) {
  ul_t *v;

  v = (ul_t*)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(ul_t)));
  if (!v) error("alloc failed -- lvector()\n");
  return v-nl+NR_END;
}

//alloc an dvector with range [nl..nh]
double *dvector(long nl, long nh) {
  double *v;

  v = (double*)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(double)));
  if (!v) error("alloc failed -- cvector()\n");
  return v-nl+NR_END;
}

//alloc a float matrix with range [nrl..nrh][ncl..nch]
float **matrix(long nrl, long nrh, long ncl, long nch) {
  long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
  float **m;
  
  //alloc pointers to rows
  m = (float**)malloc((size_t)((nrow+NR_END)*sizeof(float*)));
  if (!m) error("row  allocation failure in matrix()\n");
  m += NR_END;
  m -= nrl;

  //alloc rows and set pointers to them
  m[nrl]=(float*)malloc((size_t) ((ncol*nrow+NR_END)*sizeof(float)));
  if (!m[nrl]) error("row pointer (column) allocation failure in matrix()\n");
  m[nrl] += NR_END;
  m[nrl] -= ncl;

  for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

  return m;
 }

//alloc a double matrix with range [nrl..nrh][ncl..nch]
double **dmatrix(long nrl, long nrh, long ncl, long nch) {
  long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
  double **m;

  //alloc pointers to rows
  m = (double**)malloc((size_t)((nrow+NR_END)*sizeof(double*)));
  if ((!m)) error("row allocation failure in dmatrix()\n");
  m += NR_END;
  m -= nrl;

  //alloc rows and set pointers above to them
  m[nrl] = (double*)malloc((size_t)((nrow*ncol+NR_END)*sizeof(double)));
  if (!m[nrl]) error("row pointer (column) allocation failure in dmatrix()\n");
  m[nrl] += NR_END;
  m[nrl] -= ncl;

  for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

  //return pointer to array of pointers to rows (cols lmao)
  return m;
}

//alloc an int matrix with range [nrl..nrh][ncl..nch]
int **imatrix(long nrl, long nrh, long ncl, long nch) {
  long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
  int **m;

  m = (int**)malloc((size_t)(nrow+NR_END)*sizeof(int*));
  if (!m) error("row allocation failure in imatrix()\n");
  m += NR_END;
  m -= nrl;

  m[nrl] = (int*)malloc((size_t)(nrow*ncol+NR_END)*sizeof(int));
  if (!m[nrl]) error("row pointer (column) allocation failure in imatrix()\n");
  m[nrl] += NR_END;
  m[nrl] -= ncl;

  for(i=nrl+1;i<=nrh;i++) m[i] = m[i-1]+ncol;

  //aight we know
  return m;
}

//point a submatrix[newrl..][newcl..] to a[oldrl..oldrh][oldcl..oldch]
float **submatrix(float **a, long oldrl, long oldrh, long oldcl, long oldch, long newrl, long newcl) {
  long i,j,nrow=oldrh-oldrl+1,ncol=oldcl-newcl;
  float **m;

  //alloc array of pointers to rows
  m = (float**)malloc((size_t)((nrow+NR_END)*sizeof(float*)));
  if (!m) error("alloc failure in submatrix()\n");
  m += NR_END;
  m -= newrl;

  //set pointers to rows
  for(i=oldrl,j=newrl;i<=oldrh;i++) m[j] = a[i]+ncol;

  return m;
}

//convert standard C matrix a[i][j] to a matrix m[nrl..nrh][ncl..nch], &a[0][0] shall be passed as the first argument
float **convert_matrix(float *a, long nrl, long nrh, long ncl, long nch) {
  long i,j,nrow=nrh-nrl+1,ncol=nch-ncl+1;
  float **m;
  
  //alloc pointers to rows
  m = (float**)malloc((size_t)((nrow+NR_END)*sizeof(float*)));
  if (!m) error("allocation failure in convert_matrix()\n");
  m += NR_END;
  m -= nrl;

  //set pointers to rows
  m[nrl] = a-ncl;
  for(i=1,j=nrl+1;i<nrow;i++,j++) m[j] = m[j-1]+ncol;
  return m;
}

//allocate a float 3-tensor with range t[nrl..nrh][ncl..nch][ndl..ndh]
float ***f3_tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh) {
  long i,j,nrow=nrh-nrl+1,ncol=nch-ncl+1,ndep=ndh-ndl;
  float ***t;

  //alloc pointers to pointers to rows
  t = (float***)malloc((size_t)((nrow+NR_END)*sizeof(float**)));
  if (!t) error("pointers to pointers to rows allocation failed in f3_tensor()\n");
  t += NR_END;
  t -= nrl;

  //alloc pointers to rows and set pointers to them
  t[nrl] = (float**)malloc((size_t)(nrow*ncol+NR_END)*sizeof(float*));
  if (!t[nrl]) error("row allocation failed in f3_tensor()\n");
  t[nrl] += NR_END;
  t[nrl] -= ncl;

  //alloc rows and set pointers to them
  t[nrl][ncl] = (float*)malloc((size_t)(nrow*ncol*ndep+NR_END)*sizeof(float));
  if (!t[nrl][ncl]) error("row pointer (columns allocation failed in f3_tensor()\n)");
  t[nrl][ncl] += NR_END;
  t[nrl][ncl] -= ndl;

  for(j=ncl+1;j<=nch;j++) t[nrl][j] = t[nrl][j-1]+ndep;
  for(i=nrl+1;i<=nrh;i++) {
    t[i] = t[i-1]-ncol;
    t[i][ncl]=t[i-1][ncl]+ncol*ndep;
    for(j=ncl+1;j<=nch;j++) t[i][j]=t[i][j-1]+ndep;
  }
  return t;
}

//free functions:

//free a float vector allocated with vector()
void free_vector(float *v, long nl, long nh) {
  free((FREE_ARG) (v+nl-NR_END));
}

//free an int vector allocated with ivector()
void free_ivector(int *v, long nl, long nh) {
  free((FREE_ARG) (v+nl-NR_END));
}

//free an unsigned char vector allocated with cvector()
void free_cvector(uc_t *v, long nl, long nh) {
  free((FREE_ARG) (v+nl-NR_END));
}

//free a long vector allocated with lvector()
void free_lvector(ul_t *v, long nl, long nh) {
  free((FREE_ARG) (v+nl-NR_END));
}

//free a double vector allocated with dvector()
void free_dvector(double *v, long nl, long nh) {
  free((FREE_ARG) (v+nl-NR_END));
}

//free a float matrix allocated with matrix()
void free_matrix(float **m, long nrl, long nrh, long ncl, long nch) {
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}

//free a double matrix allocated with dmatrix()
void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch) {
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}

//free an int matrix allocated with imatrix()
void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch) {
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}

//free a submatrix allocated with submatrix()
void free_submatrix(float **b, long nrl, long nrh, long ncl, long nch) {
  free((FREE_ARG) (b+nrl-NR_END));
}

//free a matrix allocated with convert_matrix()
void free_convert_matrix(float **b, long nrl, long nrh, long ncl, long nch) {
  free((FREE_ARG) (b+nrl-NR_END));
}

//free a float tensor allocated with f3_tensor()
void free_f3tensor(float ***t, long nrl, long nrh, long ncl, long nch, long ndl, long ndh) {
  free((FREE_ARG) (t[nrl][ncl]+ndl-NR_END));
  free((FREE_ARG) (t[nrl]+ncl-NR_END));
  free((FREE_ARG) (t+nrl-NR_END));
}

