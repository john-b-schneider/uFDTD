/* Functions to update the electric and magnetic fields. */

#include "fdtd3.h"

/* update magnetic field */
void updateH3(Grid *g) {
  int mm;

  for (mm = 0; mm < SizeX - 1; mm++)
    Hy(mm) = Chyh(mm) * Hy(mm) +          /*@ \label{update3A} @*/
             Chye(mm) * (Ez(mm + 1) - Ez(mm));

  return;
}

/* update electric field */
void updateE3(Grid *g) {
  int mm;

  for (mm = 1; mm < SizeX - 1; mm++)
    Ez(mm) = Ceze(mm) * Ez(mm) +      /*@ \label{update3B} @*/
             Cezh(mm) * (Hy(mm) - Hy(mm - 1));

  return;
}
