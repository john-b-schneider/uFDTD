/* Version 2 of the improved bare-bones 1D FDTD simulation. */

#include "fdtd2.h"
#include "ezinc2.h"

int main()
{
  Grid *g;                             /*@ \label{improved2A} @*/

  ALLOC_1D(g, 1, Grid);       // allocate memory for Grid  /*@ \label{improved2B} @*/
  gridInit2(g);               // initialize the grid      /*@ \label{improved2C} @*/

  ezIncInit(g);               // initialize source function /*@ \label{improved2H} @*/

  /* do time stepping */
  for (Time = 0; Time < MaxTime; Time++) { /*@ \label{improved2D} @*/
    updateH2(g);              // update magnetic field  /*@ \label{improved2E} @*/
    updateE2(g);              // update electric field  /*@ \label{improved2F} @*/
    Ez(0) = ezInc(Time, 0.0); // apply source function  /*@ \label{improved2Z} @*/
    printf("%g\n", Ez(50));   // print output /*@ \label{improved2G} @*/
  } // end of time-stepping

  return 0;
}
