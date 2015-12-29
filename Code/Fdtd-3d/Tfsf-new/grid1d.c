#include <math.h>
#include "fdtd-macro.h"
#include "fdtd-alloc.h"

#define NLOSS 20  // number of lossy cells at end of 1D grid

void gridInit1d(Grid *g) {
  double imp0=377.0, depthInLayer=0.0, lossFactor;
  int mm;

  SizeX += NLOSS;    // size of domain
  Type   = oneDGrid; // set grid type

  ALLOC_1D(g->hy,  SizeX-1, double);
  ALLOC_1D(g->chyh,SizeX-1, double);
  ALLOC_1D(g->chye,SizeX-1, double);
  ALLOC_1D(g->ez,  SizeX,   double);
  ALLOC_1D(g->ceze,SizeX,   double);
  ALLOC_1D(g->cezh,SizeX,   double);
  
  /* set electric-field update coefficients */
  for (mm=0; mm<SizeX-1; mm++) {
    if (mm<SizeX-1-NLOSS) {
      Ceze1(mm) = 1.0;
      Cezh1(mm) = Cdtds*imp0;
      Chyh1(mm) = 1.0;
      Chye1(mm) = Cdtds/imp0;
    } else {
      depthInLayer += 0.5;
      lossFactor = 0.35*pow(depthInLayer/NLOSS,2);
      Ceze1(mm) = (1.0 - lossFactor)/(1.0 + lossFactor);
      Cezh1(mm) = Cdtds*imp0/(1.0 + lossFactor);
      depthInLayer += 0.5;
      lossFactor = 0.35*pow(depthInLayer/NLOSS,2);
      Chyh1(mm) = (1.0 - lossFactor)/(1.0 + lossFactor);
      Chye1(mm) = Cdtds/imp0/(1.0 + lossFactor);
    }
  }

  return;
}
