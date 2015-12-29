#include "fdtd-macro.h"
#include "fdtd-alloc.h"
#include <math.h>

void gridInit(Grid *g) {
  double imp0=377.0;
  int mm, nn, pp;

  // sphere parameters
  int m_c=17, n_c=17, p_c=17, isSpherePresent;
  double m2, n2, p2, r2, rad=8;

  Type    = threeDGrid;
  SizeX   = 35; // size of domain
  SizeY   = 35;
  SizeZ   = 35;
  MaxTime = 300; // duration of simulation
  Cdtds   = 1.0/sqrt(3.0); // Courant number

  printf("If the sphere present: (1=yes, 0=no) ");
  scanf(" %d",&isSpherePresent);

  /* memory allocation */
  ALLOC_3D(g->hx,  SizeX,  SizeY-1,SizeZ-1,double);
  ALLOC_3D(g->chxh,SizeX,  SizeY-1,SizeZ-1,double);
  ALLOC_3D(g->chxe,SizeX,  SizeY-1,SizeZ-1,double);
  ALLOC_3D(g->hy,  SizeX-1,SizeY,  SizeZ-1,double);
  ALLOC_3D(g->chyh,SizeX-1,SizeY,  SizeZ-1,double);
  ALLOC_3D(g->chye,SizeX-1,SizeY,  SizeZ-1,double);
  ALLOC_3D(g->hz,  SizeX-1,SizeY-1,SizeZ,  double);
  ALLOC_3D(g->chzh,SizeX-1,SizeY-1,SizeZ,  double);
  ALLOC_3D(g->chze,SizeX-1,SizeY-1,SizeZ,  double);

  ALLOC_3D(g->ex,  SizeX-1,SizeY,  SizeZ,  double);
  ALLOC_3D(g->cexe,SizeX-1,SizeY,  SizeZ,  double);
  ALLOC_3D(g->cexh,SizeX-1,SizeY,  SizeZ,  double);
  ALLOC_3D(g->ey,  SizeX,  SizeY-1,SizeZ,  double);
  ALLOC_3D(g->ceye,SizeX,  SizeY-1,SizeZ,  double);
  ALLOC_3D(g->ceyh,SizeX,  SizeY-1,SizeZ,  double);
  ALLOC_3D(g->ez,  SizeX,  SizeY,  SizeZ-1,double);
  ALLOC_3D(g->ceze,SizeX,  SizeY,  SizeZ-1,double);
  ALLOC_3D(g->cezh,SizeX,  SizeY,  SizeZ-1,double);
  
  /* set electric-field update coefficients */
  for (mm=0; mm<SizeX-1; mm++)
    for (nn=0; nn<SizeY; nn++) 
      for (pp=0; pp<SizeZ; pp++) {
	Cexe(mm,nn,pp) = 1.0;
	Cexh(mm,nn,pp) = Cdtds*imp0;
      }

  for (mm=0; mm<SizeX; mm++)
    for (nn=0; nn<SizeY-1; nn++) 
      for (pp=0; pp<SizeZ; pp++) {
	Ceye(mm,nn,pp) = 1.0;
	Ceyh(mm,nn,pp) = Cdtds*imp0;
      }

  for (mm=0; mm<SizeX; mm++)
    for (nn=0; nn<SizeY; nn++) 
      for (pp=0; pp<SizeZ-1; pp++) {
	Ceze(mm,nn,pp) = 1.0;
	Cezh(mm,nn,pp) = Cdtds*imp0;
      }

  // zero the nodes associated with the PEC sphere
  if (isSpherePresent) {
    r2 = rad*rad;
    for (mm=2; mm<SizeX-2; mm++) {
      m2 = (mm+0.5-m_c)*(mm+0.5-m_c);
      for (nn=2; nn<SizeY-2; nn++) {
	n2 = (nn+0.5-n_c)*(nn+0.5-n_c);
	for (pp=2; pp<SizeZ-2; pp++) {
	  p2 = (pp+0.5-p_c)*(pp+0.5-p_c);
	  // if center of a cube is within less than the radius to the
	  // center of the sphere, zero all the surrounding electric
	  // field nodes
	  if (m2+n2+p2 < r2) {
	    // zero surrounding Ex nodes
	    Cexe(mm,nn,  pp) = 0.0;
	    Cexe(mm,nn+1,pp) = 0.0;
	    Cexe(mm,nn,  pp+1) = 0.0;
	    Cexe(mm,nn+1,pp+1) = 0.0;
	    Cexh(mm,nn,  pp) = 0.0;
	    Cexh(mm,nn+1,pp) = 0.0;
	    Cexh(mm,nn,  pp+1) = 0.0;
	    Cexh(mm,nn+1,pp+1) = 0.0;
	    // zero surrounding Ey nodes
	    Ceye(mm,  nn,pp) = 0.0;
	    Ceye(mm+1,nn,pp) = 0.0;
	    Ceye(mm,  nn,pp+1) = 0.0;
	    Ceye(mm+1,nn,pp+1) = 0.0;
	    Ceyh(mm,  nn,pp) = 0.0;
	    Ceyh(mm+1,nn,pp) = 0.0;
	    Ceyh(mm,  nn,pp+1) = 0.0;
	    Ceyh(mm+1,nn,pp+1) = 0.0;
	    // zero surrounding Ez nodes
	    Ceze(mm,  nn,  pp) = 0.0;
	    Ceze(mm+1,nn,  pp) = 0.0;
	    Ceze(mm,  nn+1,pp) = 0.0;
	    Ceze(mm+1,nn+1,pp) = 0.0;
	    Cezh(mm,  nn,  pp) = 0.0;
	    Cezh(mm+1,nn,  pp) = 0.0;
	    Cezh(mm,  nn+1,pp) = 0.0;
	    Cezh(mm+1,nn+1,pp) = 0.0;
	  }
	}
      }
    }
  }


  /* set magnetic-field update coefficients */
  for (mm=0; mm<SizeX; mm++)
    for (nn=0; nn<SizeY-1; nn++) 
      for (pp=0; pp<SizeZ-1; pp++) {
	Chxh(mm,nn,pp) = 1.0;
	Chxe(mm,nn,pp) = Cdtds/imp0;
      }

  for (mm=0; mm<SizeX-1; mm++)
    for (nn=0; nn<SizeY; nn++) 
      for (pp=0; pp<SizeZ-1; pp++) {
	Chyh(mm,nn,pp) = 1.0;
	Chye(mm,nn,pp) = Cdtds/imp0;
      }

  for (mm=0; mm<SizeX-1; mm++)
    for (nn=0; nn<SizeY-1; nn++) 
      for (pp=0; pp<SizeZ; pp++) {
	Chzh(mm,nn,pp) = 1.0;
	Chze(mm,nn,pp) = Cdtds/imp0;
      }

  return;
}
