/* package for applying a first-order ABC to a 3D grid. */
#include "fdtd-general.h"  // has the allocation macro

/* Macros to access field array. */
#define Ex(M,N,P) ex[((M)*(size_y)+(N))*(size_z)+(P)]
#define Ey(M,N,P) ey[((M)*(size_y-1)+(N))*(size_z)+(P)]
#define Ez(M,N,P) ez[((M)*(size_y)+(N))*(size_z-1)+(P)]

/* Macros to access stored "old" value */
#define Eyx0(N,P) eyx0[(N)*(size_z)+(P)]
#define Ezx0(N,P) ezx0[(N)*(size_z-1)+(P)]
#define Eyx1(N,P) eyx1[(N)*(size_z)+(P)]
#define Ezx1(N,P) ezx1[(N)*(size_z-1)+(P)]

#define Exy0(M,P) exy0[(M)*(size_z)+(P)]
#define Ezy0(M,P) ezy0[(M)*(size_z-1)+(P)]
#define Exy1(M,P) exy1[(M)*(size_z)+(P)]
#define Ezy1(M,P) ezy1[(M)*(size_z-1)+(P)]

#define Exz0(M,N) exz0[(M)*(size_y)+(N)]
#define Eyz0(M,N) eyz0[(M)*(size_y-1)+(N)]
#define Exz1(M,N) exz1[(M)*(size_y)+(N)]
#define Eyz1(M,N) eyz1[(M)*(size_y-1)+(N)]

/* global variables not visible outside of this package */
static int size_x, size_y, size_z; 
static double *ex, *ey, *ez, abccoef;
static double *exy0, *exy1, *exz0, *exz1,
  *eyx0, *eyx1, *eyz0, *eyz1,
  *ezx0, *ezx1, *ezy0, *ezy1;

/* initialization function */
void abc_3d_init(double *the_ex, double *the_ey, double *the_ez,
		int the_size_x, int the_size_y, int the_size_z, 
		double sc)
{
  /* record arguments in local static variables */
  ex = the_ex;
  ey = the_ey;
  ez = the_ez;
  size_x = the_size_x;
  size_y = the_size_y;
  size_z = the_size_z;
  abccoef = (sc-1.0)/(sc+1.0);

  /* allocate memory for ABC arrays */
  ALLOC_2D(eyx0,size_y-1,size_z,double);
  ALLOC_2D(ezx0,size_y,size_z-1,double);
  ALLOC_2D(eyx1,size_y-1,size_z,double);
  ALLOC_2D(ezx1,size_y,size_z-1,double);

  ALLOC_2D(exy0,size_x-1,size_z,double);
  ALLOC_2D(ezy0,size_x,size_z-1,double);
  ALLOC_2D(exy1,size_x-1,size_z,double);
  ALLOC_2D(ezy1,size_x,size_z-1,double);

  ALLOC_2D(exz0,size_x-1,size_y,double);
  ALLOC_2D(eyz0,size_x,size_y-1,double);
  ALLOC_2D(exz1,size_x-1,size_y,double);
  ALLOC_2D(eyz1,size_x,size_y-1,double);

  return;
} /* end abc_3d_init() */

/* function which applies ABC -- called once per time step */
void abc_3d()
{
  int m, n, p;

  /* ABC at "x0" */
  m=0;
  for (n=0; n<size_y-1; n++)
    for (p=0; p<size_z; p++) {
      Ey(m,n,p) = Eyx0(n,p) + abccoef*(Ey(m+1,n,p)-Ey(m,n,p));
      Eyx0(n,p) = Ey(m+1,n,p);
    }
  for (n=0; n<size_y; n++)
    for (p=0; p<size_z-1; p++) {
      Ez(m,n,p) = Ezx0(n,p) + abccoef*(Ez(m+1,n,p)-Ez(m,n,p));
      Ezx0(n,p) = Ez(m+1,n,p);
    }
  
  /* ABC at "x1" */
  m=size_x-1;
  for (n=0; n<size_y-1; n++)
    for (p=0; p<size_z; p++) {
      Ey(m,n,p) = Eyx1(n,p) + abccoef*(Ey(m-1,n,p)-Ey(m,n,p));
      Eyx1(n,p) = Ey(m-1,n,p);
    }
  for (n=0; n<size_y; n++)
    for (p=0; p<size_z-1; p++) {
      Ez(m,n,p) = Ezx1(n,p) + abccoef*(Ez(m-1,n,p)-Ez(m,n,p));
      Ezx1(n,p) = Ez(m-1,n,p);
    }
  
  /* ABC at "y0" */
  n=0;
  for (m=0; m<size_x-1; m++)
    for (p=0; p<size_z; p++) {
      Ex(m,n,p) = Exy0(m,p) + abccoef*(Ex(m,n+1,p)-Ex(m,n,p));
      Exy0(m,p) = Ex(m,n+1,p);
    }
  for (m=0; m<size_x; m++)
    for (p=0; p<size_z-1; p++) {
      Ez(m,n,p) = Ezy0(m,p) + abccoef*(Ez(m,n+1,p)-Ez(m,n,p));
      Ezy0(m,p) = Ez(m,n+1,p);
    }

  /* ABC at "y1" */
  n=size_y-1;
  for (m=0; m<size_x-1; m++)
    for (p=0; p<size_z; p++) {
      Ex(m,n,p) = Exy1(m,p) + abccoef*(Ex(m,n-1,p)-Ex(m,n,p));
      Exy1(m,p) = Ex(m,n-1,p);
    }
  for (m=0; m<size_x; m++)
    for (p=0; p<size_z-1; p++) {
      Ez(m,n,p) = Ezy1(m,p) + abccoef*(Ez(m,n-1,p)-Ez(m,n,p));
      Ezy1(m,p) = Ez(m,n-1,p);
    }
  
  /* ABC at "z0" (bottom) */
  p=0;
  for (m=0; m<size_x-1; m++)
    for (n=0; n<size_y; n++) {
      Ex(m,n,p) = Exz0(m,n) + abccoef*(Ex(m,n,p+1)-Ex(m,n,p));
      Exz0(m,n) = Ex(m,n,p+1);
    }
  for (m=0; m<size_x; m++)
    for (n=0; n<size_y-1; n++) {
      Ey(m,n,p) = Eyz0(m,n) + abccoef*(Ey(m,n,p+1)-Ey(m,n,p));
      Eyz0(m,n) = Ey(m,n,p+1);
    }
  
  /* ABC at "z1" (top) */
  p=size_z-1;
  for (m=0; m<size_x-1; m++)
    for (n=0; n<size_y; n++) {
      Ex(m,n,p) = Exz1(m,n) + abccoef*(Ex(m,n,p-1)-Ex(m,n,p));
      Exz1(m,n) = Ex(m,n,p-1);
    }
  for (m=0; m<size_x; m++)
    for (n=0; n<size_y-1; n++) {
      Ey(m,n,p) = Eyz1(m,n) + abccoef*(Ey(m,n,p-1)-Ey(m,n,p));
      Eyz1(m,n) = Ey(m,n,p-1);
    }
  
  return;
} /* end abc_3d() */
