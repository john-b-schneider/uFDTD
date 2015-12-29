/* Can a+b=a for a non-zero b? */ 
#include <stdio.h>

  float a=1.0, b=0.5, c;

  c = a+b;

  while(c!=a) { /*@ \label{fragCompareA} @*/
    b = b/2.0;
    c = a+b;
  }

  printf("%12g %12g %12g\n",a,b,c); /*@ \label{fragCompareB} @*/

  return 0;
}
