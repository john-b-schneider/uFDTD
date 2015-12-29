/* Functions to update the electric and magnetic fields. */

#include "fdtd2.h"

/* characteristic impedance of free space */
static double imp0 = 377.0;  /*@ \label{update2A} @*/

/* update magnetic field */
void updateH2(Grid *g) {   /*@ \label{update2B} @*/
  int mm;

  for (mm = 0; mm < SizeX - 1; mm++)
    Hy(mm) = Hy(mm) + (Ez(mm + 1) - Ez(mm)) / imp0;

  return;
}                          /*@ \label{update2C} @*/

/* update electric field */
void updateE2(Grid *g) {   /*@ \label{update2D} @*/
  int mm;

  for (mm = 1; mm < SizeX - 1; mm++)
    Ez(mm) = Ez(mm) + (Hy(mm) - Hy(mm - 1)) * imp0;

  return;
}                          /*@ \label{update2F} @*/
