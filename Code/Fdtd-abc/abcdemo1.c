/* FDTD simulation where main() is primarily used to call other
 * functions that perform the necessary operations. */

#include "fdtd3.h"

int main()
{
  Grid *g;

  ALLOC_1D(g, 1, Grid);  // allocate memory for Grid

  gridInit(g);         // initialize the grid
  abcInit(g);          // initialize ABC  /*@ \label{abcdemo1A} @*/
  tfsfInit(g);         // initialize TFSF boundary
  snapshotInit(g);     // initialize snapshots

  /* do time stepping */
  for (Time = 0; Time < MaxTime; Time++) {

    updateH3(g);   // update magnetic field
    tfsfUpdate(g); // correct field on TFSF boundary
    updateE3(g);   // update electric field
/*b*/    abc(g);/*n*/         // apply ABC -- after E-field update/*@ \label{abcdemo1B} @*/
    snapshot(g);   // take a snapshot (if appropriate)

  } /* end of time-stepping */

  return 0;
}
