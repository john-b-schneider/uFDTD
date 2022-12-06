/* Create a 1D grid suitable for an auxiliary grid used as part of
 * the implementation of a TFSF boundary in a TEz simulations. */

#include <math.h>
#include "fdtd-macro-tez.h"
#include "fdtd-alloc1.h"

#define NLOSS     20   // number of lossy cells at end of 1D grid
#define MAX_LOSS  0.35 // maximum loss factor in lossy layer

void gridInit1d(Grid *g) {
  double imp0 = 377.0, depthInLayer = 0.0, lossFactor;
  int mm;

  SizeX += NLOSS;    // size of domain
  Type = oneDGrid;   // set grid type

  ALLOC_1D(g->hz,   SizeX - 1, double);
  ALLOC_1D(g->chzh, SizeX - 1, double);
  ALLOC_1D(g->chze, SizeX - 1, double);
  ALLOC_1D(g->ey,   SizeX, double);
  ALLOC_1D(g->ceye, SizeX, double);
  ALLOC_1D(g->ceyh, SizeX, double);
  
  /* set electric-field update coefficients */
  for (mm = 0; mm < SizeX - 1; mm++) {
    if (mm < SizeX - 1 - NLOSS) {
      Ceye1(mm) = 1.0;
      Ceyh1(mm) = Cdtds * imp0;
      Chzh1(mm) = 1.0;
      Chze1(mm) = Cdtds / imp0;
    } else {
      depthInLayer += 0.5;
      lossFactor = MAX_LOSS * pow(depthInLayer / NLOSS, 2);
      Ceye1(mm) = (1.0 - lossFactor) / (1.0 + lossFactor);
      Ceyh1(mm) = Cdtds * imp0 / (1.0 + lossFactor);
      depthInLayer += 0.5;
      lossFactor = MAX_LOSS * pow(depthInLayer / NLOSS, 2);
      Chzh1(mm) = (1.0 - lossFactor) / (1.0 + lossFactor);
      Chze1(mm) = Cdtds / imp0 / (1.0 + lossFactor);
    }
  }

  return;
}
