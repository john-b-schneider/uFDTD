#include "fdtd-alloc.h"
#include "fdtd-macro.h"

/* Macros to access stored "old" value */
#define Eyx0(N,P) eyx0[(N)*(SizeZ)+(P)]
#define Ezx0(N,P) ezx0[(N)*(SizeZ-1)+(P)]
#define Eyx1(N,P) eyx1[(N)*(SizeZ)+(P)]
#define Ezx1(N,P) ezx1[(N)*(SizeZ-1)+(P)]

#define Exy0(M,P) exy0[(M)*(SizeZ)+(P)]
#define Ezy0(M,P) ezy0[(M)*(SizeZ-1)+(P)]
#define Exy1(M,P) exy1[(M)*(SizeZ)+(P)]
#define Ezy1(M,P) ezy1[(M)*(SizeZ-1)+(P)]

#define Exz0(M,N) exz0[(M)*(SizeY)+(N)]
#define Eyz0(M,N) eyz0[(M)*(SizeY-1)+(N)]
#define Exz1(M,N) exz1[(M)*(SizeY)+(N)]
#define Eyz1(M,N) eyz1[(M)*(SizeY-1)+(N)]

/* global variables not visible outside of this package */
static double abccoef=0.0;
static double *exy0, *exy1, *exz0, *exz1,
  *eyx0, *eyx1, *eyz0, *eyz1,
  *ezx0, *ezx1, *ezy0, *ezy1;

/* initialization function */
void abcInit(Grid *g)
{

  abccoef = (Cdtds-1.0)/(Cdtds+1.0);

  /* allocate memory for ABC arrays */
  ALLOC_2D(eyx0,SizeY-1,SizeZ,double);
  ALLOC_2D(ezx0,SizeY,SizeZ-1,double);
  ALLOC_2D(eyx1,SizeY-1,SizeZ,double);
  ALLOC_2D(ezx1,SizeY,SizeZ-1,double);

  ALLOC_2D(exy0,SizeX-1,SizeZ,double);
  ALLOC_2D(ezy0,SizeX,SizeZ-1,double);
  ALLOC_2D(exy1,SizeX-1,SizeZ,double);
  ALLOC_2D(ezy1,SizeX,SizeZ-1,double);

  ALLOC_2D(exz0,SizeX-1,SizeY,double);
  ALLOC_2D(eyz0,SizeX,SizeY-1,double);
  ALLOC_2D(exz1,SizeX-1,SizeY,double);
  ALLOC_2D(eyz1,SizeX,SizeY-1,double);

  return;
} /* end abcInit() */

/* function that applies ABC -- called once per time step */
void abc(Grid *g)
{
  int mm, nn, pp;

  if (abccoef==0.0) {
    fprintf(stderr,
	    "abc: abcInit must be called before abc.  Terminating...\n");
    exit(-1);
  }

  /* ABC at "x0" */
  mm=0;
  for (nn=0; nn<SizeY-1; nn++)
    for (pp=0; pp<SizeZ; pp++) {
      Ey(mm,nn,pp) = Eyx0(nn,pp) + abccoef*(Ey(mm+1,nn,pp)-Ey(mm,nn,pp));
      Eyx0(nn,pp) = Ey(mm+1,nn,pp);
    }
  for (nn=0; nn<SizeY; nn++)
    for (pp=0; pp<SizeZ-1; pp++) {
      Ez(mm,nn,pp) = Ezx0(nn,pp) + abccoef*(Ez(mm+1,nn,pp)-Ez(mm,nn,pp));
      Ezx0(nn,pp) = Ez(mm+1,nn,pp);
    }
  
  /* ABC at "x1" */
  mm=SizeX-1;
  for (nn=0; nn<SizeY-1; nn++)
    for (pp=0; pp<SizeZ; pp++) {
      Ey(mm,nn,pp) = Eyx1(nn,pp) + abccoef*(Ey(mm-1,nn,pp)-Ey(mm,nn,pp));
      Eyx1(nn,pp) = Ey(mm-1,nn,pp);
    }
  for (nn=0; nn<SizeY; nn++)
    for (pp=0; pp<SizeZ-1; pp++) {
      Ez(mm,nn,pp) = Ezx1(nn,pp) + abccoef*(Ez(mm-1,nn,pp)-Ez(mm,nn,pp));
      Ezx1(nn,pp) = Ez(mm-1,nn,pp);
    }
  
  /* ABC at "y0" */
  nn=0;
  for (mm=0; mm<SizeX-1; mm++)
    for (pp=0; pp<SizeZ; pp++) {
      Ex(mm,nn,pp) = Exy0(mm,pp) + abccoef*(Ex(mm,nn+1,pp)-Ex(mm,nn,pp));
      Exy0(mm,pp) = Ex(mm,nn+1,pp);
    }
  for (mm=0; mm<SizeX; mm++)
    for (pp=0; pp<SizeZ-1; pp++) {
      Ez(mm,nn,pp) = Ezy0(mm,pp) + abccoef*(Ez(mm,nn+1,pp)-Ez(mm,nn,pp));
      Ezy0(mm,pp) = Ez(mm,nn+1,pp);
    }

  /* ABC at "y1" */
  nn=SizeY-1;
  for (mm=0; mm<SizeX-1; mm++)
    for (pp=0; pp<SizeZ; pp++) {
      Ex(mm,nn,pp) = Exy1(mm,pp) + abccoef*(Ex(mm,nn-1,pp)-Ex(mm,nn,pp));
      Exy1(mm,pp) = Ex(mm,nn-1,pp);
    }
  for (mm=0; mm<SizeX; mm++)
    for (pp=0; pp<SizeZ-1; pp++) {
      Ez(mm,nn,pp) = Ezy1(mm,pp) + abccoef*(Ez(mm,nn-1,pp)-Ez(mm,nn,pp));
      Ezy1(mm,pp) = Ez(mm,nn-1,pp);
    }
  
  /* ABC at "z0" (bottomm) */
  pp=0;
  for (mm=0; mm<SizeX-1; mm++)
    for (nn=0; nn<SizeY; nn++) {
      Ex(mm,nn,pp) = Exz0(mm,nn) + abccoef*(Ex(mm,nn,pp+1)-Ex(mm,nn,pp));
      Exz0(mm,nn) = Ex(mm,nn,pp+1);
    }
  for (mm=0; mm<SizeX; mm++)
    for (nn=0; nn<SizeY-1; nn++) {
      Ey(mm,nn,pp) = Eyz0(mm,nn) + abccoef*(Ey(mm,nn,pp+1)-Ey(mm,nn,pp));
      Eyz0(mm,nn) = Ey(mm,nn,pp+1);
    }
  
  /* ABC at "z1" (topp) */
  pp=SizeZ-1;
  for (mm=0; mm<SizeX-1; mm++)
    for (nn=0; nn<SizeY; nn++) {
      Ex(mm,nn,pp) = Exz1(mm,nn) + abccoef*(Ex(mm,nn,pp-1)-Ex(mm,nn,pp));
      Exz1(mm,nn) = Ex(mm,nn,pp-1);
    }
  for (mm=0; mm<SizeX; mm++)
    for (nn=0; nn<SizeY-1; nn++) {
      Ey(mm,nn,pp) = Eyz1(mm,nn) + abccoef*(Ey(mm,nn,pp-1)-Ey(mm,nn,pp));
      Eyz1(mm,nn) = Ey(mm,nn,pp-1);
    }
  
  return;
} /* end abc_3d() */
