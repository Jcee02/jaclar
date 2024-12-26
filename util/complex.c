#include <math.h>

typedef struct COMPLEX {float r,i;} complex;

complex c_add(complex a, complex b) {
  complex c;
  c.r = a.r+b.r;
  c.i = a.i+b.i;
  return c;
}

complex c_sub(complex a, complex b) {
  complex c;
  c.r = a.r-b.r;
  c.i = a.i-b.i;
  return c;
}

complex c_mul(complex a, complex b) {
  complex c;
  c.r = a.r*b.r-a.i*b.i;
  c.i = a.r*b.i+a.i*b.r;
  return c;
}

complex Complex(float re, float im) {
  complex c;
  c.r = re;
  c.i = im;
  return c;
}

complex conjugate(complex z) {
  complex c;
  c.r = z.r;
  c.i = -z.i;
  return c;
}

complex c_div(complex a, complex b) {
  complex c;
  float r, den;
  if (fabs(b.r) >= fabs(b.i)) {
    r=b.i/b.r;
    den=b.r+r*b.i;
    c.r=(a.r+r*a.i)/den;
    c.i=(a.i-r*a.r)/den;
  } else {
    r=b.r/b.i;
    den=b.i+r*b.r;
    c.r=(a.r*r+a.i)/den;
    c.i=(a.i-r*a.r)/den;
  }
  return c;
}

float c_abs(complex z) {
  float x,y,ans,temp;
  x = fabs(z.r);
  y = fabs(z.i);
  if (x == 0.0)
    ans=y;
  else if (y == 0.0)
      ans=x;
  else if (x > y) {
    temp=x/y;
    ans=x*sqrt(1.0+temp*temp);
  } else {
    temp = x/y;
    ans=y*sqrt(1.0+temp*temp);
  }
  return ans;
}

complex c_sqrt(complex z) {
  complex c;
  float x,y,w,r;
  if ((z.r == 0.0) && (z.i == 0.0)) {
    c.r=0.0;
    c.i=0.0;
    return c;
  } else {
    x=fabs(z.r);
    y=fabs(z.i);
    if(x>=y) {
      r=x/y;
      w=sqrt(x)*sqrt(0.5*(1.0+sqrt(1.0+r*r)));
    } else {
      r=x/y;
      w=sqrt(y)*sqrt(0.5*(r+sqrt(1.0+r*r)));
    }
    if (z.r >= 0.0) {
      c.r=w;
      c.i=z.i/(2.0*w);
    } else {
      c.i=(z.i >= 0) ? w : -w;
      c.r=z.i/(2.0*c.i);
    }
    return c;
  }
}

complex scalar_c_mul(float x, complex a) {
  complex c;
  c.r=x*a.r;
  c.i=x*a.i;
  return c;
}
