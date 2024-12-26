#include <stdio.h>
#include <stdlib.h>
#include "util/util.h"
#include "advanced/algebraic_equations/gaussj.h"

int main(void) {

  float **a = matrix(1,3,1,3);    
  float **b = matrix(1,3,1,1);
  
  //ex1
  //coef. matrix
  a[1][1] = 2;
  a[1][2] = 3;
  a[1][3] = -4;

  a[2][1] = 3;
  a[2][2] = 4;
  a[2][3] = -5;


  a[3][1] = 4;
  a[3][2] = 5;
  a[3][3] = -6;

  //m right hand side vectors (m=1)
  b[1][1] = 5;
  b[2][1] = -6;
  b[3][1] = 7;
  
  printf("Original set of equations:\n");
  printf("%f*x + %f*y - %fz = %f\n", a[1][1], a[1][2], fabs(a[1][3]), b[1][1]);
  printf("%f*x + %f*y - %fz = %f\n", a[2][1], a[2][2], fabs(a[2][3]), b[2][1]);
  printf("%f*x + %f*y - %fz = %f\n", a[3][1], a[3][2], fabs(a[3][3]), b[3][1]);
  
  gauss_jordan(a, 3, b, 1);
  printf("Inverse a matrix:\n");
  for (int i=1;i<=3;i++)
    for(int j=1;j<=3;j++)
      printf("%f\t",a[i][j]);
  printf("\nSolution set (b):\n");
  for(int j=1;j<=3;j++)
    printf("%f\t",b[j][1]);

  return EXIT_SUCCESS;
}

