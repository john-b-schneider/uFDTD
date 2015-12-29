/* Second-order ABC for TEz grid. */
#include <math.h>
#include "fdtd-alloc1.h"
#include "fdtd-macro-tez.h"

/* Define macros for arrays that store the previous values of the
 * fields.  For each one of these arrays the three arguments are as
 * follows:
 *
 *   first argument:  spatial displacement from the boundary
 *   second argument: displacement back in time
 *   third argument:  distance from either the bottom (if EyLeft or
 *                    EyRight) or left (if ExTop or ExBottom) side
 *                    of grid
 *                    
 */
#define EyLeft(M, Q, N)    eyLeft[(N) * 6 + (Q) * 3 + (M)]
#define EyRight(M, Q, N)  eyRight[(N) * 6 + (Q) * 3 + (M)]
#define ExTop(N, Q, M)       exTop[(M) * 6 + (Q) * 3 + (N)]
#define ExBottom(N, Q, M) exBottom[(M) * 6 + (Q) * 3 + (N)]

static int initDone = 0;
static double coef0, coef1, coef2;
static double *eyLeft, *eyRight, *exTop, *exBottom;

void abcInit(Grid *g) {
  double temp1, temp2;
  
  initDone = 1;

  /* allocate memory for ABC arrays */
  ALLOC_1D(eyLeft, (SizeY - 1) * 6, double);
  ALLOC_1D(eyRight, (SizeY - 1) * 6, double);
  ALLOC_1D(exTop, (SizeX - 1) * 6, double);
  ALLOC_1D(exBottom, (SizeX - 1) * 6, double);

  /* calculate ABC coefficients */
  temp1  = sqrt(Cexh(0, 0) * Chze(0, 0));
  temp2 = 1.0 / temp1 + 2.0 + temp1;
  coef0 = -(1.0 / temp1 - 2.0 + temp1) / temp2;
  coef1 = -2.0 * (temp1 - 1.0 / temp1) / temp2;
  coef2 = 4.0 * (temp1 + 1.0 / temp1) / temp2;

  return;
} 

void abc(Grid *g)
{
  int mm, nn;

  /* ABC at left side of grid */
  for (nn = 0; nn < SizeY - 1; nn++) {
    Ey(0, nn) = coef0 * (Ey(2, nn) + EyLeft(0, 1, nn))
      + coef1 * (EyLeft(0, 0, nn) + EyLeft(2, 0, nn)
		 - Ey(1, nn) - EyLeft(1, 1, nn))
      + coef2 * EyLeft(1, 0, nn) - EyLeft(2, 1, nn);

    /* memorize old fields */ 
    for (mm = 0; mm < 3; mm++) {
      EyLeft(mm, 1, nn) = EyLeft(mm, 0, nn);
      EyLeft(mm, 0, nn) = Ey(mm, nn);
    }
  }
  
  /* ABC at right side of grid */
  for (nn = 0; nn < SizeY - 1; nn++) {
    Ey(SizeX - 1, nn) = coef0 * (Ey(SizeX - 3, nn) + EyRight(0, 1, nn))
      + coef1 * (EyRight(0, 0, nn) + EyRight(2, 0, nn)
		 - Ey(SizeX - 2, nn) - EyRight(1, 1, nn))
      + coef2 * EyRight(1, 0, nn) - EyRight(2, 1, nn);
    
    /* memorize old fields */
    for (mm = 0; mm < 3; mm++) {
      EyRight(mm, 1, nn) = EyRight(mm, 0, nn);
      EyRight(mm, 0, nn) = Ey(SizeX - 1 - mm, nn);
    }
  }

  /* ABC at bottom of grid */
  for (mm = 0; mm < SizeX - 1; mm++) {
    Ex(mm, 0) = coef0 * (Ex(mm, 2) + ExBottom(0, 1, mm))
      + coef1 * (ExBottom(0, 0, mm) + ExBottom(2, 0, mm)
		 - Ex(mm, 1) - ExBottom(1, 1, mm))
      + coef2 * ExBottom(1, 0, mm) - ExBottom(2, 1, mm);
    
    /* memorize old fields */ 
    for (nn = 0; nn < 3; nn++) {
      ExBottom(nn, 1, mm) = ExBottom(nn, 0, mm);
      ExBottom(nn, 0, mm) = Ex(mm, nn);
    }
  }
  
  /* ABC at top of grid */
  for (mm = 0; mm < SizeX - 1; mm++) {
    Ex(mm, SizeY - 1) = coef0 * (Ex(mm, SizeY - 3) + ExTop(0, 1, mm))
      + coef1 * (ExTop(0, 0, mm) + ExTop(2, 0, mm)
		 - Ex(mm, SizeY - 2) - ExTop(1, 1, mm))
      + coef2 * ExTop(1, 0, mm) - ExTop(2, 1, mm);
    
    /* memorize old fields */
    for (nn = 0; nn < 3; nn++) {
      ExTop(nn, 1, mm) = ExTop(nn, 0, mm);
      ExTop(nn, 0, mm) = Ex(mm, SizeY - 1-nn);
    }
  }
  
  return;
}
