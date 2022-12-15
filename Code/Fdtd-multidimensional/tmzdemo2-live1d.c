/* TMz simulation with a ricker source at the center of the grid */

#include "fdtd-grid1.h"
#include "fdtd-alloc1.h"
#include "fdtd-proto2-live.h"
#include "ezinc.h"

#include <string.h>  // for memcpy

int main()
{
  Grid *g1, *g2;

  ALLOC_1D(g2,1,Grid);  // allocate memory for 2D Grid
  gridInit(g2);         // initialize 2d grid

  ALLOC_1D(g1,1,Grid);  // allocate memory for 1D Grid
  memcpy(g1,g2,sizeof(Grid)); // copy information from 2D array
  gridInit1d(g1);       // initialize 1d grid

  tfsfInit(g1,g2);
  snapshotInit1d(g1);   // initialize snapshots
  snapshotInit2d(g2);   // initialize snapshots

  /* do time stepping */
  for (g2->time=0; g2->time<g2->maxTime; g2->time++) {
    updateH2d(g2);    // update 2d magnetic field
    tfsfUpdate(g1,g2);
    updateE2d(g2);    // update 2d electric field
    snapshot1d(g1);   // take a snapshot (if appropriate)
    snapshot2d(g2);   // take a snapshot (if appropriate)

  } /* end of time-stepping */

  return 0;
}
