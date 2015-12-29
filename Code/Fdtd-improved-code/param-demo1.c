/* param-demo1.c:  Program that demonstrates the setting of
 * "persistent" parameters via the arguments of an initialization
 * function.  Here the parameters control the amplitude and phase of a
 * harmonic function f(x) = a cos(x + phi).  This program generates
 * num_points of the harmonic function with the "x" value of the
 * varying between zero and 2*pi.
 */

#include <stdio.h>
#include <math.h>  // To obtain M_PI, i.e., 3.14159...

void harmonicInit1(double amp, double phase);  /*@ \label{paramDemo1A} @*/
double harmonic1(double x);                    /*@ \label{paramDemo1B} @*/

int main() {
  double amp, phase, x;
  int mm, num_points = 100;

  printf("Enter the amplitude: ");       /*@ \label{paramDemo1C} @*/
  scanf(" %lf", &amp);
  printf("Enter the phase [in degrees]: ");
  scanf(" %lf", &phase);
  phase *= M_PI / 180.0;                 /*@ \label{paramDemo1D} @*/

  /* Set the amplitude and phase. */
  harmonicInit1(amp, phase);              /*@ \label{paramDemo1E} @*/

  for (mm = 0; mm < num_points; mm++) {   /*@ \label{paramDemo1F} @*/
    x = 2.0 * M_PI * mm / (float)(num_points - 1);
    printf("%f %f\n", x, harmonic1(x));  /*@ \label{paramDemo1G} @*/
  }

  return 0;
}
