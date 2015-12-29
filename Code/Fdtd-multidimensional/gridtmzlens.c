/* define a dielectric lens */

#include "fdtd-macro-tmz.h"
#include "fdtd-alloc1.h"

#ifndef _MATH_H
#include <math.h>
#endif

#define EPSR 2.0

void gridInit(Grid *g) {
  double imp0=377.0;
  /* lens geometry info */
  double radius=180, x12, x22, y2, r2, xCenter1=-130, xCenter2=200,
    yCenter=100;
  int mm, nn;

  SizeX   = 301; // size of domain
  SizeY   = 201;
  MaxTime = 500; // duration of simulation
  Cdtds   = 1.0/sqrt(2.0); // Courant number
  Type    = tmZGrid;

  ALLOC_2D(g->hx,  SizeX,  SizeY-1, double);
  ALLOC_2D(g->chxh,SizeX,  SizeY-1, double);
  ALLOC_2D(g->chxe,SizeX,  SizeY-1, double);
  ALLOC_2D(g->hy,  SizeX-1,SizeY, double);
  ALLOC_2D(g->chyh,SizeX-1,SizeY, double);
  ALLOC_2D(g->chye,SizeX-1,SizeY, double);
  ALLOC_2D(g->ez,  SizeX,  SizeY, double);
  ALLOC_2D(g->ceze,SizeX,  SizeY, double);
  ALLOC_2D(g->cezh,SizeX,  SizeY, double);
  
  /* set electric-field update coefficients */
  r2 = radius*radius;
  for (mm=0; mm<SizeX; mm++) {
    x12 = mm-xCenter1;
    x12 = x12*x12;
    x22 = mm-xCenter2;
    x22 = x22*x22;
    for (nn=0; nn<SizeY; nn++) {
      y2 = nn-yCenter;
      y2=y2*y2;
      if (x12+y2<r2 && x22+y2<r2 ) { 
	/* in lens */
	Ceze(mm,nn) = 1.0;
	Cezh(mm,nn) = Cdtds*imp0/sqrt(EPSR);
      } else {
        /* free space */
	Ceze(mm,nn) = 1.0;
	Cezh(mm,nn) = Cdtds*imp0;
      }
    }
  }

  /* set magnetic-field update coefficients */
  for (mm=0; mm<SizeX; mm++)
    for (nn=0; nn<SizeY-1; nn++) {
      Chxh(mm,nn) = 1.0;
      Chxe(mm,nn) = Cdtds/imp0;
    }

  for (mm=0; mm<SizeX-1; mm++)
    for (nn=0; nn<SizeY; nn++) {
      Chyh(mm,nn) = 1.0;
      Chye(mm,nn) = Cdtds/imp0;
    }

  return;
}
