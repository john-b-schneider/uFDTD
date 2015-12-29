#include <math.h>
#include "fdtd-general.h"

#define NLOSS 20  // number of lossy cells at end of 1D grids

static double *hx, *hy, *hz, *ex, *ey, *ez;  // 3D arrays
static double *ez1d, *hy1d;   // local 1D arrays

static double ceh, che,
  ceze1d[NLOSS], cezh1d[NLOSS], chyh1d[NLOSS], chye1d[NLOSS];

// Source function -- takes a since argument representing time.
static double (*source)(double);

static int
  start_x, start_y, start_z, // indices of TF-region start
  last_x, last_y, last_z,    // indices of TF-region end
  size_x, size_y, size_z,
  qTime;

// function prototypes
static void step1d();

/* Macros to access field array. */
#define Ex(M,N,P) ex[((M)*(size_y)+(N))*(size_z)+(P)]
#define Ey(M,N,P) ey[((M)*(size_y-1)+(N))*(size_z)+(P)]
#define Ez(M,N,P) ez[((M)*(size_y)+(N))*(size_z-1)+(P)]

#define Hx(M,N,P) hx[((M)*(size_y-1)+(N))*(size_z-1)+(P)]
#define Hy(M,N,P) hy[((M)*(size_y)+(N))*(size_z-1)+(P)]
#define Hz(M,N,P) hz[((M)*(size_y-1)+(N))*(size_z)+(P)]

/* ##################### tfsf_3d_init() ##################### */
void tfsf_3d_ez_init(
	  double *the_hx,  double *the_hy, double *the_hz, 
	  double *the_ex,  double *the_ey,  double *the_ez, 
	  int the_start_x, int the_start_y, int the_start_z,
	  int the_last_x, int the_last_y, int the_last_z,
	  int the_size_x, int the_size_y, int the_size_z,
	  double the_che, double the_ceh,
	  double (*the_source)(double))
{
  int m;
  double loss_factor;

  // keep track of time locally within this package
  qTime=0;  

  // 3D field arrays
  hx = the_hx;
  hy = the_hy;
  hz = the_hz;
  ex = the_ex;
  ey = the_ey;
  ez = the_ez;

  // nominal size of 3D computational domain
  size_x = the_size_x;  
  size_y = the_size_y;
  size_z = the_size_z;

  // indices for "first" and "last" points in total-field region
  start_x = the_start_x;  
  start_y = the_start_y;
  start_z = the_start_z;
  last_x  = the_last_x;
  last_y  = the_last_y;
  last_z  = the_last_z;

  // update coefficients in 3D grid
  ceh = the_ceh;
  che = the_che;

  // update coefficients for lossy layer at end of 1D array
  for(m=0;m<NLOSS;m++) {
    loss_factor = 0.35*pow((m+0.5)/NLOSS,2);
    chyh1d[m] = (1.0 - loss_factor)/(1.0 + loss_factor);
    chye1d[m] = che/(1.0 + loss_factor);
    loss_factor = 0.35*pow((m+1.0)/NLOSS,2);
    ceze1d[m] = (1.0 - loss_factor)/(1.0 + loss_factor);
    cezh1d[m] = ceh/(1.0 + loss_factor);
  }

  // source function used to drive the system
  source = the_source;

  // allocate sufficient memory for 1D arrays
  ALLOC_1D(ez1d,size_x+NLOSS,double);
  ALLOC_1D(hy1d,size_x+NLOSS-1,double);

  return;
} /* ----------------- end of tfsf_3d_init() ----------------- */


/* ######################## step1d() ######################### */
/* step1d: Advance fields in the 1D grid. */
static void step1d()
{
  int m, mm;
  
  /* update magnetic field in "interior" */
  for(m=0;m<size_x-1;m++)
    hy1d[m] += che*(ez1d[m+1]-ez1d[m]);

  /* update magnetic field in lossy layer */
  for(mm=0;mm<NLOSS-1;mm++) {
    m = mm + size_x-1;
    hy1d[m] = chyh1d[mm]*hy1d[m]
      + chye1d[mm]*(ez1d[m+1]-ez1d[m]);
  }

  /* update electric field in "interior" */
  for(m=1;m<size_x;m++)
    ez1d[m] += ceh*(hy1d[m]-hy1d[m-1]);

  /* update electric field in lossy layer */
  for(mm=0;mm<NLOSS-1;mm++) {
    m = mm + size_x;
    ez1d[m] = ceze1d[mm]*ez1d[m]
      + cezh1d[mm]*(hy1d[m]-hy1d[m-1]);
  }

  /* apply hard source to first node in grid */
  ez1d[0] = source(qTime);

  qTime++;  // advance time one time-step

  return;
} /* -------------------- end of step_1d() ------------------ */


/* ######################## tfsf_3d() ####################### */
/* tfsf_3d: Correct the fields on the TFSF boundary.
 */
void tfsf_3d_ez(void) {

  int i, j, k;

  /****** constant x faces -- scattered-field nodes ******/

  // correct Hy at start_x-1/2 by subtracting Ez_inc
  i = start_x;
  for (j=start_y; j<=last_y; j++)
    for (k=start_z; k<last_z; k++)
      Hy(i-1,j,k) -= che*ez1d[i];

  // correct Hy at last_x+1/2 by adding Ez_inc
  i = last_x;
  for (j=start_y; j<=last_y; j++)
    for (k=start_z; k<last_z; k++)
      Hy(i,j,k) += che*ez1d[i];

  /**** constant y faces -- scattered-field nodes ****/

  // correct Hx at start_y-1/2 by adding Ez_inc
  j = start_y;
  for (i=start_x; i<=last_x; i++)
    for (k=start_z; k<last_z; k++)
      Hx(i,j-1,k) += che*ez1d[i];

  // correct Hx at last_y+1/2 by subtracting Ez_inc
  j = last_y;
  for (i=start_x; i<=last_x; i++)
    for (k=start_z; k<last_z; k++)
      Hx(i,j,k) -= che*ez1d[i];

  /**** constant z faces -- scattered-field nodes ****/

  // nothing to correct on this face

  /* advance fields in 1D array */
  step1d();

  /**** constant x faces -- total-field nodes ****/

  // correct Ez at start_x face by subtracting Hy_inc
  i = start_x;
  for (j=start_y; j<=last_y; j++)
    for (k=start_z; k<last_z; k++)
      Ez(i,j,k) -= ceh*hy1d[i-1];

  // correct Ez at last_x face by adding Hy_inc
  i = last_x;
  for (j=start_y; j<=last_y; j++)
    for (k=start_z; k<last_z; k++)
      Ez(i,j,k) += ceh*hy1d[i];

  /**** constant y faces -- total-field nodes ****/

  // nothing to correct on this face

  /**** constant z faces -- total-field nodes ****/

  // correct Ex at start_z face by adding Hy_inc
  k = start_z;
  for (i=start_x; i<last_x; i++)
    for (j=start_y; j<=last_y; j++)
      Ex(i,j,k) += ceh*hy1d[i];

  // correct Ex at last_z face by subtracting Hy_inc
  k = last_z;
  for (i=start_x; i<last_x; i++)
    for (j=start_y; j<=last_y; j++)
      Ex(i,j,k) -= ceh*hy1d[i];

  return;
} /* ------------------ end of tfsf_3d() ------------------ */
