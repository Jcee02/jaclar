#define SWAP(a,b) {temp=(a);(a)=(b);(b)=temp;}

#include "../../util/util.h"
#include "gaussj.h"

void gauss_jordan(float **a, int n, float **b, int m) {
  /*Linear equation solution by Gauss-Jordan elimination
   *above, a[1..n][1..m] is the input matrix. b[1..n][1..n]
   *is input containing the right-hand side vectors. On output,
   *a is replaced by its matrix inverse, and b is replaced by the
   *corresponding set of solutions.*/

  int *indxc,*indxr,*ipiv;
  int i,icol,irow,j,k,l,ll;
  float big,dum,pivinv,temp;
  
  //These things are used to store results of computations while pivoting 
  indxc=ivector(1,n);
  indxr=ivector(1,n);
  ipiv=ivector(1,n);

  for (j=1;j<=n;j++) ipiv[j]=0;
  //This is main loop over columns to be reduced
  for (i=1;i<=n;i++) {
    big=0.0;
    //This is the outer loop to look for a pivot element
    for (j=1;j<=n;j++) {
      if (ipiv[j] != 1) {
        for (k=1;k<=n;k++) {
          if (ipiv[k] == 0) {
            if (fabs(a[j][k]) >= big) {
              big=fabs(a[j][k]);
              irow=j;
              icol=k;
            }
          } else if (ipiv[k] > 1) error("gauss_jordan: Degenerate Matrix, Singular Matrix-1");
        }
      }
    }
    ++(ipiv[icol]);
  /*We have now the pivot element, so we interchange rows (if needed), to store pivot in diagonal
   * Columns are not really interchanged, only relabeled:
   * indxc[i] is the column of the ith pivot element (ith column that is reduced)
   * while indxr[i] is the row in which the pivot element was stored originally.
   * if indxr[i] != indxc[i] there is an implied column interchange
   * With this form of bookkeeping the solution b's will end up in the correct order.
   * and the inverse matrix will be scrambled by columns*/
    if (irow != icol) {
      for (l=1;l<=n;l++) SWAP(a[irow][l],a[icol][l]);
      for (l=1;l<=m;l++) SWAP(b[irow][l],b[icol][l]);
    }
  //We are ready now to divide the pivot row by the pivot element!!!
  //that thing is located at irow and icol
    indxr[i]=irow;
    indxc[i]=icol;
    if (a[icol][icol] == 0.0) error("gauss_jordan: Degenerate Matrix ,Singular Matrix-2");
    pivinv=1.0/a[icol][icol];
    for (l=1;l<=n;l++) a[icol][l] *= pivinv;
    for (l=1;l<=m;l++) b[icol][l] *= pivinv;
  //now reduce rows, but not pivot rows dummy
    for (ll=1;ll<=n;ll++){
      if(ll != icol) {
        dum=a[ll][icol];
        a[ll][icol]=0.0;
        for (l=1;l<=n;l++) a[ll][l] -= a[icol][l]*dum;
        for (l=1;l<=m;l++) b[ll][l] -= b[icol][l]*dum;
      }
  }
}
  //Main loop over columns end
  //Now unscramble solutions by interchanging pairs of columns in reverse order 
  //that the permutation was built up
  for(l=n;l>=1;l--) {
    if (indxr[l] != indxc[l])
      for(k=1;k<=n;k++)
        SWAP(a[k][indxr[l]],a[k][indxc[l]]);
  }

  //free stuff
  free_ivector(ipiv,1,n);
  free_ivector(indxc,1,n);
  free_ivector(indxr,1,n);
}



