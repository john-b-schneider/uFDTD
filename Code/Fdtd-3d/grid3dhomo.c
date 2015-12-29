#include "fdtd-macro.h"
#include "fdtd-alloc.h"
#include <math.h>

void gridInit(Grid *g) {
  double imp0 = 377.0;
  int mm, nn, pp;

  Type = threeDGrid;   /*@ \label{grid3dhomoA} @*/
  SizeX = 32; // size of domain
  SizeY = 31;
  SizeZ = 31;
  MaxTime = 300; // duration of simulation
  Cdtds = 1.0 / sqrt(3.0); // Courant number /*@ \label{grid3dhomoB} @*/

  /* memory allocation */
  ALLOC_3D(g->hx,   SizeX, SizeY - 1, SizeZ - 1, double); /*@ \label{grid3dhomoC} @*/
  ALLOC_3D(g->chxh, SizeX, SizeY - 1, SizeZ - 1, double);
  ALLOC_3D(g->chxe, SizeX, SizeY - 1, SizeZ - 1, double);
  ALLOC_3D(g->hy,   SizeX - 1, SizeY, SizeZ - 1, double);
  ALLOC_3D(g->chyh, SizeX - 1, SizeY, SizeZ - 1, double);
  ALLOC_3D(g->chye, SizeX - 1, SizeY, SizeZ - 1, double);
  ALLOC_3D(g->hz,   SizeX - 1, SizeY - 1, SizeZ, double);
  ALLOC_3D(g->chzh, SizeX - 1, SizeY - 1, SizeZ, double);
  ALLOC_3D(g->chze, SizeX - 1, SizeY - 1, SizeZ, double);

  ALLOC_3D(g->ex,   SizeX - 1, SizeY, SizeZ, double);
  ALLOC_3D(g->cexe, SizeX - 1, SizeY, SizeZ, double);
  ALLOC_3D(g->cexh, SizeX - 1, SizeY, SizeZ, double);
  ALLOC_3D(g->ey,   SizeX, SizeY - 1, SizeZ, double);
  ALLOC_3D(g->ceye, SizeX, SizeY - 1, SizeZ, double);
  ALLOC_3D(g->ceyh, SizeX, SizeY - 1, SizeZ, double);
  ALLOC_3D(g->ez,   SizeX, SizeY, SizeZ - 1, double);
  ALLOC_3D(g->ceze, SizeX, SizeY, SizeZ - 1, double);
  ALLOC_3D(g->cezh, SizeX, SizeY, SizeZ - 1, double); /*@ \label{grid3dhomoD} @*/
  
  /* set electric-field update coefficients */
  for (mm = 0; mm < SizeX - 1; mm++) /*@ \label{grid3dhomoE} @*/
    for (nn = 0; nn < SizeY; nn++) 
      for (pp = 0; pp < SizeZ; pp++) {
	Cexe(mm, nn, pp) = 1.0;
	Cexh(mm, nn, pp) = Cdtds * imp0;
      }

  for (mm = 0; mm < SizeX; mm++)
    for (nn = 0; nn < SizeY - 1; nn++) 
      for (pp = 0; pp < SizeZ; pp++) {
	Ceye(mm, nn, pp) = 1.0;
	Ceyh(mm, nn, pp) = Cdtds * imp0;
      }

  for (mm = 0; mm < SizeX; mm++)
    for (nn = 0; nn < SizeY; nn++) 
      for (pp = 0; pp < SizeZ - 1; pp++) {
	Ceze(mm, nn, pp) = 1.0;
	Cezh(mm, nn, pp) = Cdtds * imp0;
      }

  /* set magnetic-field update coefficients */
  for (mm = 0; mm < SizeX; mm++)
    for (nn = 0; nn < SizeY - 1; nn++) 
      for (pp = 0; pp < SizeZ - 1; pp++) {
	Chxh(mm, nn, pp) = 1.0;
	Chxe(mm, nn, pp) = Cdtds / imp0;
      }

  for (mm = 0; mm < SizeX - 1; mm++)
    for (nn = 0; nn < SizeY; nn++) 
      for (pp = 0; pp < SizeZ - 1; pp++) {
	Chyh(mm, nn, pp) = 1.0;
	Chye(mm, nn, pp) = Cdtds / imp0;
      }

  for (mm = 0; mm < SizeX - 1; mm++)
    for (nn = 0; nn < SizeY - 1; nn++) 
      for (pp = 0; pp < SizeZ; pp++) {
	Chzh(mm, nn, pp) = 1.0;
	Chze(mm, nn, pp) = Cdtds / imp0;
      } /*@ \label{grid3dhomoF} @*/

  return;
}  /* end gridInit() */
