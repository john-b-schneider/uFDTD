/* Square-root test. */
#include <math.h>  // needed for sqrt()
#include <stdio.h>

#define COUNT 23

int main() {
  float a=2.0;
  int i;

  for (i=0; i<COUNT; i++)
    a = sqrt(a);  // square root of a

  for (i=0; i<COUNT; i++)
    a = a*a;      // a squared

  printf("%12g\n",a);

  return 0;
}
