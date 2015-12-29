#include "fdtd-macro.h"
#include <stdio.h>

/* update magnetic field */
void updateH(Grid *g) {
  int mm, nn, pp;

  if (Type == oneDGrid) {
    
    for (mm = 0; mm < SizeX - 1; mm++)
      Hy1(mm) = Chyh1(mm) * Hy1(mm) 
	+ Chye1(mm) * (Ez1(mm + 1) - Ez1(mm));
    
  } else if (Type == tmZGrid) { 
    
    for (mm = 0; mm < SizeX; mm++)
      for (nn = 0; nn < SizeY - 1; nn++)
	Hx2(mm, nn) = Chxh2(mm, nn) * Hx2(mm, nn) 
	  - Chxe2(mm, nn) * (Ez2(mm, nn + 1) - Ez2(mm, nn));
    
    for (mm = 0; mm < SizeX - 1; mm++)
      for (nn = 0; nn < SizeY; nn++)
	Hy2(mm, nn) = Chyh2(mm, nn) * Hy2(mm, nn) 
	  + Chye2(mm, nn) * (Ez2(mm + 1, nn) - Ez2(mm, nn));
    
  } else if (Type == teZGrid) {
    
    for(mm = 0; mm < SizeX - 1; mm++)
      for(nn = 0; nn < SizeY - 1; nn++)
	Hz2(mm, nn) = Chzh2(mm, nn) * Hz2(mm, nn) -
	  Chze2(mm, nn) * ((Ey2(mm + 1, nn) - Ey2(mm, nn)) -
			   (Ex2(mm, nn + 1) - Ex2(mm, nn)));

  } else if (Type == threeDGrid) {
    
    for (mm = 0; mm < SizeX; mm++)
      for (nn = 0; nn < SizeY - 1; nn++)
	for (pp = 0; pp < SizeZ - 1; pp++)
	  Hx(mm, nn, pp) = Chxh(mm, nn, pp) * Hx(mm, nn, pp) +
	    Chxe(mm, nn, pp) * ((Ey(mm, nn, pp + 1) - Ey(mm, nn, pp)) -
				(Ez(mm, nn + 1, pp) - Ez(mm, nn, pp)));
    
    for (mm = 0; mm < SizeX - 1; mm++)
      for (nn = 0; nn < SizeY; nn++)
	for (pp = 0; pp < SizeZ - 1; pp++)
	  Hy(mm, nn, pp) = Chyh(mm, nn, pp) * Hy(mm, nn, pp) +
	    Chye(mm, nn, pp) * ((Ez(mm + 1, nn, pp) - Ez(mm, nn, pp)) -
				(Ex(mm, nn, pp + 1) - Ex(mm, nn, pp)));
    
    for (mm = 0; mm < SizeX - 1; mm++)
      for (nn = 0; nn < SizeY - 1; nn++)
	for (pp = 0; pp < SizeZ; pp++)
	  Hz(mm, nn, pp) = Chzh(mm, nn, pp) * Hz(mm, nn, pp) +
	    Chze(mm, nn, pp) * ((Ex(mm, nn + 1, pp) - Ex(mm, nn, pp)) -
				(Ey(mm + 1, nn, pp) - Ey(mm, nn, pp))); 

  } else {
    fprintf(stderr, "updateH: Unknown grid type.  Terminating...\n");
  }
  
  return;
}  /* end updateH() */


/* update electric field */
void updateE(Grid *g) {
  int mm, nn, pp;
  
  if (Type == oneDGrid) {
    
    for (mm = 1; mm < SizeX - 1; mm++)
      Ez1(mm) = Ceze1(mm) * Ez1(mm) 
	+ Cezh1(mm) * (Hy1(mm) - Hy1(mm - 1));
    
  } else if (Type == tmZGrid) {
    
    for (mm = 1; mm < SizeX - 1; mm++)
      for (nn = 1; nn < SizeY - 1; nn++)
	Ez2(mm, nn) = Ceze2(mm, nn) * Ez2(mm, nn) +
	  Cezh2(mm, nn) * ((Hy2(mm, nn) - Hy2(mm - 1, nn)) -
			   (Hx2(mm, nn) - Hx2(mm, nn - 1)));

  } else if (Type == teZGrid) {
    
    for(mm = 1; mm < SizeX - 1; mm++)
      for(nn = 1; nn < SizeY - 1; nn++)
	Ex2(mm, nn) = Cexe2(mm, nn) * Ex2(mm, nn) +
	  Cexh2(mm, nn) * (Hz2(mm, nn) - Hz2(mm, nn - 1));
    
    for(mm = 1; mm < SizeX - 1; mm++)
      for(nn = 1; nn < SizeY - 1; nn++)
	Ey2(mm, nn) = Ceye2(mm, nn) * Ey2(mm, nn) -
	  Ceyh2(mm, nn) * (Hz2(mm, nn) - Hz2(mm - 1, nn));
    
  } else if (Type == threeDGrid) {
    
    for (mm = 0; mm < SizeX - 1; mm++)
      for (nn = 1; nn < SizeY - 1; nn++)
	for (pp = 1; pp < SizeZ - 1; pp++)
	  Ex(mm, nn, pp) = Cexe(mm, nn, pp) * Ex(mm, nn, pp) +
	    Cexh(mm, nn, pp) * ((Hz(mm, nn, pp) - Hz(mm, nn - 1, pp)) -
				(Hy(mm, nn, pp) - Hy(mm, nn, pp - 1)));
    
    for (mm = 1; mm < SizeX - 1; mm++)
      for (nn = 0; nn < SizeY - 1; nn++)
	for (pp = 1; pp < SizeZ - 1; pp++)
	  Ey(mm, nn, pp) = Ceye(mm, nn, pp) * Ey(mm, nn, pp) + 
	    Ceyh(mm, nn, pp) * ((Hx(mm, nn, pp) - Hx(mm, nn, pp - 1)) -
				(Hz(mm, nn, pp) - Hz(mm - 1, nn, pp)));
    
    for (mm = 1; mm < SizeX - 1; mm++)
      for (nn = 1; nn < SizeY - 1; nn++)
	for (pp = 0; pp < SizeZ - 1; pp++)
	  Ez(mm, nn, pp) = Ceze(mm, nn, pp) * Ez(mm, nn, pp) +
	    Cezh(mm, nn, pp) * ((Hy(mm, nn, pp) - Hy(mm - 1, nn, pp)) -
				(Hx(mm, nn, pp) - Hx(mm, nn - 1, pp)));

  } else {
    fprintf(stderr, "updateE: Unknown grid type.  Terminating...\n");
  }
  
  return;
}  /* end updateE() */
