/* 3D simulation with a TFSF boundary. */

#include "fdtd-alloc.h"
#include "fdtd-macro.h" 
#include "fdtd-proto.h"

int main()
{
  Grid *g;

  ALLOC_1D(g,1,Grid); // allocate memory for grid structure
  gridInit(g);        // initialize 3D grid

  tfsfInit(g);        // initialize TFSF boundary
  abcInit(g);         // initialize ABC
  snapshotInit3d(g);  // initialize snapshots

  /* do time stepping */
  for (Time=0; Time<MaxTime; Time++) {
    updateH(g);     // update magnetic fields 
    tfsf(g);        // apply correction to TFSF boundary
    updateE(g);     // update electric fields 
    abc(g);         // apply ABC
    snapshot3d(g);  // take a snapshot (if appropriate)
  } // end of time-stepping

  return 0;
}
