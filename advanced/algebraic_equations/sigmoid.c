#include "../../util/util.h"
#include <stdlib.h>
#include <stdio.h>
#define EULER_NUMBER 2.71828
#define EULER_NUMBER_F 2.71828182846
#define EULER_NUMBER_L 2.71828182845904523536

typedef long double ld_t;

double sigmoid(double n) {
  return (1/1+pow(EULER_NUMBER,-n));
}


int main(int argc, char *argv[]) {
  if (argc != 2)
    printf("Only three arguments are passed");
  
  int r;

  r = atoi(argv[1]);
  //c = atoi(argv[2]);
  double *v = dvector(1,r);
 
  for (int i = 0; i<=r; ++i) {
    v[i]=sigmoid(i);
    printf("%lf\n", v[i]);
  } 


  return EXIT_SUCCESS;
}
