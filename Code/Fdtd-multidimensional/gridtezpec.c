#include "fdtd-macro-tez.h"
#include "fdtd-alloc1.h"
#include <math.h>

void gridInit(Grid *g) {
  double imp0 = 377.0;
  int mm, nn;

  /* terms for the PEC scatterer */
  double rad, r2, xLocation, yLocation, xCenter, yCenter;

  Type = teZGrid;
  SizeX = 92;      // size of domain
  SizeY = 82;
  MaxTime = 300;   // duration of simulation
  Cdtds = 1.0 / sqrt(2.0); // Courant number /*@ \label{gridtezpecA} @*/

  ALLOC_2D(g->hz,   SizeX - 1, SizeY - 1, double);
  ALLOC_2D(g->chzh, SizeX - 1, SizeY - 1, double);
  ALLOC_2D(g->chze, SizeX - 1, SizeY - 1, double);

  ALLOC_2D(g->ex,   SizeX - 1, SizeY, double);
  ALLOC_2D(g->cexh, SizeX - 1, SizeY, double);
  ALLOC_2D(g->cexe, SizeX - 1, SizeY, double);

  ALLOC_2D(g->ey,   SizeX, SizeY - 1, double);
  ALLOC_2D(g->ceye, SizeX, SizeY - 1, double);
  ALLOC_2D(g->ceyh, SizeX, SizeY - 1, double);
  
  /* set electric-field update coefficients */
  for (mm = 0; mm < SizeX - 1; mm++) /*@ \label{gridtezpecB} @*/
    for (nn = 0; nn < SizeY; nn++) {
      Cexe(mm, nn) = 1.0;
      Cexh(mm, nn) = Cdtds * imp0;
    }

  for (mm = 0; mm < SizeX; mm++)
    for (nn = 0; nn < SizeY - 1; nn++) {
      Ceye(mm, nn) = 1.0;
      Ceyh(mm, nn) = Cdtds * imp0;
    }                          /*@ \label{gridtezpecC} @*/

  /* Set to zero nodes associated with PEC scatterer.
   * Circular scatterer assumed centered on Hz node
   * at (xCenter, yCenter).  If an Hz node is less than
   * the radius away from this node, set to zero the
   * four electric fields that surround that node. 
   */
  rad = 12;  // radius of circle          /*@ \label{gridtezpecD} @*/
  xCenter = SizeX / 2;
  yCenter = SizeY / 2;
  r2 = rad * rad;  // square of radius
  for (mm = 1; mm < SizeX - 1; mm++) {
    xLocation = mm - xCenter;
    for (nn = 1; nn < SizeY - 1; nn++) {
      yLocation = nn - yCenter;
      if (xLocation * xLocation + yLocation * yLocation < r2) {
	Cexe(mm, nn) = 0.0;
	Cexh(mm, nn) = 0.0;
	Cexe(mm, nn + 1) = 0.0;
	Cexh(mm, nn + 1) = 0.0;
	Ceye(mm + 1, nn) = 0.0;
	Ceyh(mm + 1, nn) = 0.0;
	Ceye(mm, nn) = 0.0;
	Ceyh(mm, nn) = 0.0;
      }
    }
  }

  /* set magnetic-field update coefficients */
  for (mm = 0; mm < SizeX - 1; mm++)     /*@ \label{gridtezpecE} @*/
    for (nn = 0; nn < SizeY - 1; nn++) {
      Chzh(mm, nn) = 1.0;
      Chze(mm, nn) = Cdtds / imp0;
    }

  return;
}
