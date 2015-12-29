/* TMz simulation with a TFSF boundary and a second-order ABC. */

#include "fdtd-alloc1.h"
#include "fdtd-macro-tmz.h" 
/*b*/#include "fdtd-proto2.h" /*n*/

int main()
{
  Grid *g;

  ALLOC_1D(g, 1, Grid); // allocate memory for grid /*@ \label{tmzdemo2A} @*/
  gridInit(g);          // initialize 2D grid

  abcInit(g);           // initialize ABC
  tfsfInit(g);          // initialize TFSF boundary
  snapshotInit2d(g);    // initialize snapshots

  /* do time stepping */
  for (Time = 0; Time < MaxTime; Time++) { /*@ \label{tmzdemo2C} @*/
    updateH2d(g);       // update magnetic fields 
/*b*/    tfsfUpdate(g);      // apply TFSF boundary    /*n*/
    updateE2d(g);       // update electric fields 
/*b*/    abc(g);             // apply ABC              /*n*/
    snapshot2d(g);      // take a snapshot (if appropriate)
  } // end of time-stepping

  return 0;
}
