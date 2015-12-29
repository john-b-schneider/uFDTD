/* 
 * harmonic-demo1.c: Functions to calculate a harmonic function of a
 * given amplitude and phase.  The desired amplitude and phase are
 * passed as arguments to harmonicInit1().  harmonicInit1() sets the
 * corresponding static global variables so that these values will be
 * available for the harmonic1() function to use whenever it is
 * called.
 */

#include <math.h> // for cos() function

/* Global static variables that are visible only to functions inside
   this file. */
static double amp, phase;     /*@ \label{harmonicDemo1A} @*/

// initialization function
void harmonicInit1(double the_amp, double the_phase) {  /*@ \label{harmonicDemo1B} @*/
  amp = the_amp;       /*@ \label{harmonicDemo1C} @*/
  phase = the_phase;   /*@ \label{harmonicDemo1D} @*/

  return;
}

// calculation function
double harmonic1(double x) {   /*@ \label{harmonicDemo1E} @*/
  return amp * cos(x + phase);
}
