/* TFSF implementation for a TEz grid. */

#include <string.h>  // for memcpy
#include "fdtd-macro-tez.h"
#include "fdtd-proto2.h"
#include "fdtd-alloc1.h"
#include "ezinctez.h"    /*@\label{tfsftezF}@*/

static int firstX = 0, firstY, // indices for first point in TF region 
           lastX, lastY;     // indices for last point in TF region

static Grid *g1;  // 1D auxiliary grid

void tfsfInit(Grid *g) {

  ALLOC_1D(g1, 1, Grid);       // allocate memory for 1D Grid /*@\label{tfsftezA}@*/
  memcpy(g1, g, sizeof(Grid)); // copy information from 2D array
  gridInit1d(g1);            // initialize 1d grid /*@\label{tfsftezB}@*/

  printf("Grid is %d by %d cell.\n", SizeX, SizeY);
  printf("Enter indices for first point in TF region: ");
  scanf(" %d %d", &firstX, &firstY);
  printf("Enter indices for last point in TF region: ");
  scanf(" %d %d", &lastX, &lastY);

  ezIncInit(g); // initialize source function

  return;
}

void tfsfUpdate(Grid *g) { /*@\label{tfsftezC}@*/
  int mm, nn;

  // check if tfsfInit() has been called
  if (firstX <= 0) {
    fprintf(stderr,
      "tfsfUpdate: tfsfInit must be called before tfsfUpdate.\n"
      "            Boundary location must be set to positive value.\n");
    exit(-1);
  }

  // correct Hz along left edge
  mm = firstX - 1;
  for (nn = firstY; nn < lastY; nn++)
    Hz(mm, nn) += Chze(mm, nn) * Ey1G(g1, mm + 1);
  
  // correct Hz along right edge
  mm = lastX;
  for (nn = firstY; nn < lastY; nn++)
    Hz(mm, nn) -= Chze(mm, nn) * Ey1G(g1, mm);
  
  updateH2d(g1);    // update 1D magnetic field   /*@\label{tfsftezD}@*/
  updateE2d(g1);    // update 1D electric field
  Ey1G(g1, 0) = ezInc(TimeG(g1), 0.0); // set source node
  TimeG(g1)++;      // increment time in 1D grid

  // correct Ex along the bottom
  nn = firstY;   /*@\label{tfsftezE}@*/
  for (mm = firstX; mm < lastX; mm++)
    Ex(mm, nn) -= Cexh(mm, nn) * Hz1G(g1, mm);

  // correct Ex along the top
  nn = lastY;
  for (mm = firstX; mm < lastX; mm++)
    Ex(mm, nn) += Cexh(mm, nn) * Hz1G(g1, mm);

  // correct Ey field along left edge
  mm = firstX;
  for (nn = firstY; nn < lastY; nn++)
    Ey(mm, nn) += Ceyh(mm, nn) * Hz1G(g1, mm - 1);
  
  // correct Ey field along right edge
  mm = lastX;
  for (nn = firstY; nn < lastY; nn++)
    Ey(mm, nn) -= Ceyh(mm, nn) * Hz1G(g1, mm);
  
  // no need to correct Ex along top and bottom since
  // incident Ex is zero

  return;
}
