/* Function to initialize the Grid structure. */

#include "fdtd2.h"

void gridInit2(Grid *g) {
  SizeX = 200;                    // set the size of the grid /*@ \label{gridinit2A} @*/
  MaxTime = 250;                  // set duration of simulation /*@ \label{gridinit2B} @*/
  Cdtds = 1.0;                    // set Courant number /*@ \label{gridinit2E} @*/

  ALLOC_1D(g->ez, SizeX, double); // allocate memory for Ez /*@ \label{gridinit2C} @*/
  ALLOC_1D(g->hy, SizeX, double); // allocate memory for Hy /*@ \label{gridinit2D} @*/

  return;
}
