/* Is 1./3.+1./3.+1./3. == 1.0? */ 
#include <stdio.h>

int main() {
  float a;

  a = 1.0/3.0;

  if ( a+a+a == 1.0 )
    printf("Equal.\n");
  else
    printf("Not equal.\n");

  return 0;
}
