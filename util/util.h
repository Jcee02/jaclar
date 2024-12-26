#ifndef _UTIL_H_ 
#define _UTIL_H_

#include <math.h>

//Function-like macros (easy to inline)
//Square functions for float and double data types


static float sqr_arg;
#define SQR(a) ((sqr_arg=(a)) == 0.0 ? 0.0 : sqr_arg*sqr_arg)

static double dsqr_arg;
#define DSQR(a) ((dsqr_arg=(a)) == 0.0 ? 0.0 : dsqr_arg*dsqr_arg)

//Max value functions for float, double, long and int data types

static float max_arg1, max_arg2;
#define FMAX(a,b) (max_arg1 = (a), max_arg2 = (b), (max_arg1) > (max_arg2) ? \
(max_arg1) : (max_arg2))

static double dmax_arg1, dmax_arg2;
#define DMAX(a,b) (dmax_arg1 = (a), dmax_arg2 = (b), (dmax_arg1) > (dmax_arg2) ? \
(dmax_arg1) : (dmax_arg2))

static long lmax_arg1, lmax_arg2;
#define LMAX(a,b) (lmax_arg1 = (a), lmax_arg2 = (b), (lmax_arg1) > (lmax_arg2) ? \
(lmax_arg1) : (lmax_arg2))

static int imax_arg1, imax_arg2;
#define IMAX(a,b) (imax_arg1 = (a), imax_arg2 = (b), (imax_arg1) > (imax_arg2) ? \
(imax_arg1) : (imax_arg2))

//Min value functions for float, double, long and int data types

static float min_arg1, min_arg2;
#define FMIN(a,b) (min_arg1 = (a), min_arg2 = (b), (min_arg1) < (min_arg2) ? \
(min_arg1) : (min_arg2))

static double dmin_arg1, dmin_arg2;
#define DMIN(a,b) (dmin_arg1 = (a), dmin_arg2 = (b), (dmin_arg1) < (dmin_arg2) ? \
(dmin_arg1) : (dmin_arg2))

static long lmin_arg1, lmin_arg2;
#define LMIN(a,b) (lmin_arg1 = (a), lmin_arg2 = (b), (lmin_arg1) < (lmin_arg2) ? \
(lmin_arg1) : (lmin_arg2))

static int imin_arg1, imin_arg2;
#define IMIN(a,b) (imin_arg1 = (a), imin_arg2 = (b), (imin_arg1) < (imin_arg2) ? \
(imin_arg1) : (imin_arg2))

#define SIGN(a,b) ((b) > 0.0 ? fabs(a) : -fabs(a))

//util functions for printing to stderr / allocating memory for algebraic data types

typedef unsigned long ul_t;
typedef unsigned char uc_t;

void error(char error[]);
float *vector(long nl, long nh);
int *ivector(long nl, long nh);
uc_t *cvector(long nl, long nh);
ul_t *lvector(long nl, long nh);
double *dvector(long nl, long nh);
float **matrix(long nrl, long nrh, long ncl, long nch);
double **dmatrix(long nrl, long nrh, long ncl, long nch);
int **imatrix(long nrl, long nrh, long ncl, long nch);
float **submatrix(float **a, long oldrl, long oldrh, long oldcl, long oldch, long newrl, long newcl);
float **convert_matrix(float *a, long nrl, long nrh, long ncl, long nch);
float ***f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh);
void free_vector(float *v, long nl, long nh);
void free_ivector(int *v, long nl, long nh);
void free_cvector(uc_t *v, long nl, long nh);
void free_lvector(ul_t *v, long nl, long nh);
void free_dvector(double *v, long nl, long nh);
void free_matrix(float **m, long nrl, long nrh, long ncl, long nch);
void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch);
void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch);
void free_submatrix(float **m, long nrl, long nrh, long ncl, long nch);
void free_convert_matrix(float **b, long nrl, long nrh, long ncl, long nch);
void free_f3tensor(float ***t, long nrl, long nrh, long ncl, long nch, long ndl, long ndh);

#endif
