#include "fdtd-macro-tez.h"

/* update magnetic field */
void updateH2d(Grid *g) {
  int mm, nn;

  if (Type == oneDGrid) {

    for (mm = 0; mm < SizeX - 1; mm++)
      Hz1(mm) = Chzh1(mm) * Hz1(mm) 
	- Chze1(mm) * (Ey1(mm + 1) - Ey1(mm));

  } else { 

    for (mm = 0; mm < SizeX - 1; mm++)    /*@ \label{updatetezA} @*/
      for (nn = 0; nn < SizeY - 1; nn++)
	Hz(mm, nn) = Chzh(mm, nn) * Hz(mm, nn) +
	  Chze(mm, nn) * ((Ex(mm, nn + 1) - Ex(mm, nn))
			  - (Ey(mm + 1, nn) - Ey(mm, nn)));
  }

  return;
}

/* update electric field */
void updateE2d(Grid *g) {
  int mm, nn;

  if (Type == oneDGrid) {

    for (mm = 1; mm < SizeX - 1; mm++)
      Ey1(mm) = Ceye1(mm) * Ey1(mm) 
	- Ceyh1(mm) * (Hz1(mm) - Hz1(mm - 1));

  } else { 

    for (mm = 0; mm < SizeX - 1; mm++)    /*@ \label{updatetezB} @*/
      for (nn = 1; nn < SizeY - 1; nn++)
	Ex(mm, nn) = Cexe(mm, nn) * Ex(mm, nn) +
	  Cexh(mm, nn) * (Hz(mm, nn) - Hz(mm, nn - 1));

    for (mm = 1; mm < SizeX - 1; mm++)
      for (nn = 0; nn < SizeY - 1; nn++)
	Ey(mm, nn) = Ceye(mm, nn) * Ey(mm, nn) -
	  Ceyh(mm, nn) * (Hz(mm, nn) - Hz(mm - 1, nn));
  }

  return;
}
