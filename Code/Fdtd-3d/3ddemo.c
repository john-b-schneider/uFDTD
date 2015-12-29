/* 3D simulation with dipole source at center of grid. */

#include "fdtd-alloc.h"
#include "fdtd-macro.h" 
#include "fdtd-proto.h"
#include "ezinc.h"

int main()
{
  Grid *g;

  ALLOC_1D(g, 1, Grid); // allocate memory for grid structure
  gridInit(g);        // initialize 3D grid

  abcInit(g);         // initialize ABC
  ezIncInit(g);
  snapshot3dInit(g);  // initialize snapshots

  /* do time stepping */
  for (Time = 0; Time < MaxTime; Time++) {
    updateH(g);       // update magnetic fields 
    updateE(g);       // update electric fields 
    Ex((SizeX - 1) / 2, SizeY / 2, SizeZ / 2) += ezInc(Time, 0.0);
    abc(g);           // apply ABC
    snapshot3d(g);    // take a snapshot (if appropriate)
  } // end of time-stepping

  return 0;
}
