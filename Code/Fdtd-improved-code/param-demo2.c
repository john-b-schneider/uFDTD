/* param-demo2.c: Program that demonstrates the setting of
 * "persistent" parameters via an initialization function.  Here the
 * initialization function handles all the details of obtaining the
 * parameters associated with the harmonic function.
 */

#include <stdio.h>
#include <math.h>  // To obtain M_PI, i.e., 3.14159...

void harmonicInit2();        /*@ \label{paramDemo2A} @*/
double harmonic2(double x);  /*@ \label{paramDemo2B} @*/

int main() {
  double x;
  int mm, num_points = 100;

  /* Initialize the harmonic function. */
  harmonicInit2();            /*@ \label{paramDemo2E} @*/

  for (mm = 0; mm < num_points; mm++) {   /*@ \label{paramDemo2F} @*/
    x = 2.0 * M_PI * mm / (float)(num_points - 1);
    printf("%f %f\n", x, harmonic2(x));  /*@ \label{paramDemo2G} @*/
  }

  return 0;
}
