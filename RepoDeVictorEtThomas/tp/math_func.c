/* Home Work */

# include <stdlib.h>

# include "math_func.h"


unsigned long fact(unsigned long n) {
  // FIX ME
  int i;
  unsigned long resultat = 1;
  for(i = 0; i <  n; i++)
  {
      resultat = resultat * (i+1);
  }
  return resultat;
}

unsigned long fibo(unsigned long n) {
  // FIX ME
  int  i;
  unsigned long f1 = 0;
  unsigned long f2 = 1;
  unsigned long t;
  for(i =0; i<n;i++)
  {
      t = f1 +f2;
      f1 = f2;
      f2 = t;
  }
  return f1;
}

unsigned long int_sqrt(unsigned long n) {
  // FIX ME
  unsigned long x = 1;
  int i;
  for(i=0; i< 5; i++)
  {
      x = (x + (n/x))/2;
  }
  return x;

}

unsigned long digit_number(unsigned long n) {
  // FIX ME
  unsigned long s = 0;
  while(n>0)
  {
      s+=1;
      n=n/10;
  }
  return s;
}

unsigned long binary_digit_number(unsigned long n) {
  // FIX ME
  unsigned long s = 1;
  while(n>1)
  {
      n = n/2;
      s = s+1;
  }
  return s;
}

unsigned long power_of_2(unsigned long n) {
  // FIX ME
  if(n>0)
  {
     return 2 *power_of_2(n-1);
  }
  return 1;
}

unsigned long divisor_sum(unsigned long n) {
  // FIX ME
  int i;
  unsigned long r =0;
  for(i = 0; i< n; i++)
  {
      if(n%i ==0)
      {
          r+= i;
      }
  }
}
