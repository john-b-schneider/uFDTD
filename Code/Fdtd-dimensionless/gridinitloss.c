#include "fdtd3.h"

#define LOSS 0.0253146
#define LOSS_LAYER 100
#define EPSR 4.0 

void gridInit3(Grid *g) {
  double imp0=377.0;
  int mm;

  SizeX   = 200; // size of domain
  MaxTime = 450; // duration of simulation
  Cdtds   = 1.0; // Courant number

  /* Allocate memory for arrays. */
  ALLOC_1D(g->ez,  SizeX,  double);
  ALLOC_1D(g->ceze,SizeX,  double);
  ALLOC_1D(g->cezh,SizeX,  double);
  ALLOC_1D(g->hy,  SizeX-1,double);
  ALLOC_1D(g->chyh,SizeX-1,double);
  ALLOC_1D(g->chye,SizeX-1,double);

  /* set electric-field update coefficients */
  for (mm=0; mm<SizeX; mm++)
    if (mm<100) {
      Ceze(mm) = 1.0;
      Cezh(mm) = imp0;
    } else {
      Ceze(mm) = (1.0-LOSS)/(1.0+LOSS);
      Cezh(mm) = imp0/EPSR/(1.0+LOSS);
    }

  /* set magnetic-field update coefficients */
  for (mm=0; mm<SizeX-1; mm++) {
    Chyh(mm) = 1.0;
    Chye(mm) = 1.0/imp0;
  }

  return;
}
