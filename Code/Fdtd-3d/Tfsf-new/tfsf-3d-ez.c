/* TFSF boundary for a 3D grid.  A 1D auxiliary grid is used to
 * calculate the incident field which is assumed to be propagating in
 * the x direction and polarized in the z direction. */

#include <string.h>  // for memcpy
#include "fdtd-macro.h"
#include "fdtd-proto.h"
#include "fdtd-alloc.h"
#include "ezinc.h"

static int firstX=0, firstY, firstZ, // indices for first point in TF region
           lastX, lastY, lastZ;      // indices for last point in TF region

Grid *g1;  // 1D auxiliary grid

void tfsfInit(Grid *g) {

  ALLOC_1D(g1,1,Grid);       // allocate memory for 1D Grid
  memcpy(g1,g,sizeof(Grid)); // copy information from 3D array
  gridInit1d(g1);            // initialize 1d grid

  printf("Grid is %d by %d by %d.\n",SizeX,SizeY,SizeZ);
  printf("Enter indices for first point in TF region: ");
  scanf(" %d %d %d",&firstX,&firstY,&firstZ);
  printf("Enter indices for last point in TF region: ");
  scanf(" %d %d %d",&lastX,&lastY,&lastZ);

  ezIncInit(g); // initialize source function

  return;
}

void tfsf(Grid *g) {
  int mm, nn, pp;

  // check if tfsfInit() has been called
  if (firstX<=0) {
    fprintf(stderr,
      "tfsf: tfsfInit must be called before tfsfUpdate.\n"
      "      Boundary location must be set to positive value.\n");
    exit(-1);
  }

  /****** constant x faces -- scattered-field nodes ******/

  // correct Hy at firstX-1/2 by subtracting Ez_inc
  mm = firstX;
  for (nn=firstY; nn<=lastY; nn++)
    for (pp=firstZ; pp<lastZ; pp++)
      Hy(mm-1,nn,pp) -= Chye(mm,nn,pp)*Ez1G(g1,mm);

  // correct Hy at lastX+1/2 by adding Ez_inc
  mm = lastX;
  for (nn=firstY; nn<=lastY; nn++)
    for (pp=firstZ; pp<lastZ; pp++)
      Hy(mm,nn,pp) += Chye(mm,nn,pp)*Ez1G(g1,mm);

  /**** constant y faces -- scattered-field nodes ****/

  // correct Hx at firstY-1/2 by adding Ez_inc
  nn = firstY;
  for (mm=firstX; mm<=lastX; mm++)
    for (pp=firstZ; pp<lastZ; pp++)
      Hx(mm,nn-1,pp) += Chxe(mm,nn-1,pp)*Ez1G(g1,mm);

  // correct Hx at lastY+1/2 by subtracting Ez_inc
  nn = lastY;
  for (mm=firstX; mm<=lastX; mm++)
    for (pp=firstZ; pp<lastZ; pp++)
      Hx(mm,nn,pp) -= Chxe(mm,nn,pp)*Ez1G(g1,mm);

  /**** constant z faces -- scattered-field nodes ****/

  // nothing to correct on this face

  /**** update the fields in the auxiliary 1D grid ****/
  updateH(g1);    // update 1D magnetic field
  updateE(g1);    // update 1D electric field
  Ez1G(g1,0) = ezInc(TimeG(g1),0.0); // set source node
  TimeG(g1)++;    // increment time in 1D grid

  /**** constant x faces -- total-field nodes ****/

  // correct Ez at firstX face by subtracting Hy_inc
  mm = firstX;
  for (nn=firstY; nn<=lastY; nn++)
    for (pp=firstZ; pp<lastZ; pp++)
      Ez(mm,nn,pp) -= Cezh(mm,nn,pp)*Hy1G(g1,mm-1);

  // correct Ez at lastX face by adding Hy_inc
  mm = lastX;
  for (nn=firstY; nn<=lastY; nn++)
    for (pp=firstZ; pp<lastZ; pp++)
      Ez(mm,nn,pp) += Cezh(mm,nn,pp)*Hy1G(g1,mm);

  /**** constant y faces -- total-field nodes ****/

  // nothing to correct on this face

  /**** constant z faces -- total-field nodes ****/

  // correct Ex at firstZ face by adding Hy_inc
  pp = firstZ;
  for (mm=firstX; mm<lastX; mm++)
    for (nn=firstY; nn<=lastY; nn++)
      Ex(mm,nn,pp) += Cexh(mm,nn,pp)*Hy1G(g1,mm);

  // correct Ex at lastZ face by subtracting Hy_inc
  pp = lastZ;
  for (mm=firstX; mm<lastX; mm++)
    for (nn=firstY; nn<=lastY; nn++)
      Ex(mm,nn,pp) -= Cexh(mm,nn,pp)*Hy1G(g1,mm);

  return;
}
