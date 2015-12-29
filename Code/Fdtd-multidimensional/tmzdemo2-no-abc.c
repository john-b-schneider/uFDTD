/* TMz simulation with a TFSF boundary and a second-order ABC */

#include "fdtd-macro-tmz.h"
#include "fdtd-alloc1.h"
#include "fdtd-proto2.h"

int main()
{
  Grid *g;

  ALLOC_1D(g,1,Grid); // allocate memory for grid
  gridInit(g);        // initialize 2D grid

  tfsfInit(g);        // initialize TFSF boundary
  snapshotInit2d(g);  // initialize snapshots

  /* do time stepping */
  for (Time=0; Time<MaxTime; Time++) {
    updateH2d(g);     // update magnetic fields
    tfsfUpdate(g);    // apply TFSF boundary
    updateE2d(g);     // update electric fields
    snapshot2d(g);    // take a snapshot (if appropriate)
  } // end of time-stepping

  return 0;
}
