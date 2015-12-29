/* 
 * harmonic-demo2.c: Functions to calculate a harmonic function of a
 * given amplitude and phase.  harmonicInit2() prompts the user for
 * the amplitude and phase and sets the global variables so these
 * values will be available for the harmonic2() function to use
 * whenever it is called.
 */

#include <math.h> // for cos() function

/* Global static variables that are visible only to functions inside
   this file. */
static double amp, phase;     /*@ \label{harmonicDemo2A} @*/

// initialization function
void harmonicInit2() {  /*@ \label{harmonicDemo2B} @*/

  printf("Enter the amplitude: ");               /*@ \label{harmonicDemo2C} @*/
  scanf(" %lf", &amp);
  printf("Enter the phase [in degrees]: ");
  scanf(" %lf", &phase);
  phase *= M_PI / 180.0;                    /*@ \label{harmonicDemo2D} @*/

  return;
}

// calculation function
double harmonic2(double x) {   /*@ \label{harmonicDemo2E} @*/
  return amp * cos(x + phase);
}
