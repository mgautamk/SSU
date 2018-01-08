/*
 * addAndSubtract1.c
 * Reads two Integers from user, then performs the 
 * addition and subtraction
 * Mahesh Gautam - Oct 17 2014
 */

#include <stdio.h>

int main(void)
{
  int w,x,y,z,p;

  printf("Enter two Integers: ");
  scanf("%i %i", &w, &x);
  y = w;
  y += x;
  z = w;
  z -= x;
  p = w;
  p *= x;

  printf("sum = %i, difference = %i\n, product = %i", y, z, p);


  return 0;
}
