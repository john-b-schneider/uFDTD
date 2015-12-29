/* FDTD simulation where main() is primarily used to call other
 * functions that perform the necessary operations. */

#include "fdtd3.h"

int main()
{
  Grid *g;

  ALLOC_1D(g, 1, Grid);  // allocate memory for Grid

  gridInit3(g);        // initialize the grid  /*@ \label{improved3A} @*/
  abcInit(g);          // initialize ABC       /*@ \label{improved3C} @*/
  tfsfInit(g);         // initialize TFSF boundary
  snapshotInit(g);     // initialize snapshots /*@ \label{improved3B} @*/

  /* do time stepping */
  for (Time = 0; Time < MaxTime; Time++) {
    updateH3(g);   // update magnetic field
    tfsfUpdate(g); // correct field on TFSF boundary
    abc(g);        // apply ABC
    updateE3(g);   // update electric field
    snapshot(g);   // take a snapshot (if appropriate)
  } // end of time-stepping

  return 0;
}
