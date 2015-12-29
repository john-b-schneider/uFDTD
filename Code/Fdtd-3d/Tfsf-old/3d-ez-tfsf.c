/* 3D simulation of a spherical scatterer illuminated by
 *  a plane wave.
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "fdtd-general.h"
#include "abc-3d.h"
#include "tfsf-3d-ez.h"

#define size_x  35
#define size_y  35
#define size_z  35

#define TFSF_OFFSET 5

/* source function */
double ricker_wrapper(double time);
double ricker(double time, double cdtds, double ppw);
/* wrtraw function */
void wrtraw_y(int frame, char *basename);

double cdtds, ppw=20.0;

/* Field arrays */
double *ex, *ey, *ez, *hx, *hy, *hz;

/* Macros to access field array. */
#define Ex(M,N,P) ex[((M)*(size_y)+(N))*(size_z)+(P)]
#define Ey(M,N,P) ey[((M)*(size_y-1)+(N))*(size_z)+(P)]
#define Ez(M,N,P) ez[((M)*(size_y)+(N))*(size_z-1)+(P)]

#define Hx(M,N,P) hx[((M)*(size_y-1)+(N))*(size_z-1)+(P)]
#define Hy(M,N,P) hy[((M)*(size_y)+(N))*(size_z-1)+(P)]
#define Hz(M,N,P) hz[((M)*(size_y-1)+(N))*(size_z)+(P)]

int main() {
  double imp0=377.0, che, ceh;
  int m, n, p, qTime, ntmax=200, nframe=0;

  // sphere parameters
  int m_c=17, n_c=17, p_c=17;
  double m2, n2, p2, r2, rad=8;

  ALLOC_3D(ex,size_x-1,size_y,size_z,double);
  ALLOC_3D(ey,size_x,size_y-1,size_z,double);
  ALLOC_3D(ez,size_x,size_y,size_z-1,double);

  ALLOC_3D(hx,size_x,size_y-1,size_z-1,double);
  ALLOC_3D(hy,size_x-1,size_y,size_z-1,double);
  ALLOC_3D(hz,size_x-1,size_y-1,size_z,double);

  /* Run simulation close to Courant limit. */
  cdtds = 0.95/sqrt(3.1);
  che  = cdtds/imp0;
  ceh  = cdtds*imp0;

  /* Initialize ABC. */
  abc_3d_init(ex, ey, ez, size_x, size_y, size_z, cdtds);

  /* Initialize TFSF boundary. */
  tfsf_3d_ez_init(hx, hy, hz, 
       ex, ey, ez, 
       TFSF_OFFSET, TFSF_OFFSET, TFSF_OFFSET,
       size_x-TFSF_OFFSET,size_y-TFSF_OFFSET,size_z-TFSF_OFFSET,
       size_x, size_y, size_z,
       che, ceh,
       ricker_wrapper);

  for (qTime=0; qTime<ntmax; qTime++) {

    /************ Hx update. ************/
    for (m=0; m<size_x; m++)
     for (n=0; n<size_y-1; n++)
      for (p=0; p<size_z-1; p++)
       Hx(m,n,p) = Hx(m,n,p) +
	che*((Ey(m,n,p+1)-Ey(m,n,p)) - (Ez(m,n+1,p)-Ez(m,n,p)));
    
    /************ Hy update. ************/
    for (m=0; m<size_x-1; m++)
     for (n=0; n<size_y; n++)
      for (p=0; p<size_z-1; p++)
       Hy(m,n,p) = Hy(m,n,p) +
	che*((Ez(m+1,n,p)-Ez(m,n,p)) - (Ex(m,n,p+1)-Ex(m,n,p)));
    
    /************ Hz update. ************/
    for (m=0; m<size_x-1; m++)
     for (n=0; n<size_y-1; n++)
      for (p=0; p<size_z; p++)
       Hz(m,n,p) = Hz(m,n,p) +
	che*((Ex(m,n+1,p)-Ex(m,n,p)) - (Ey(m+1,n,p)-Ey(m,n,p)));
    
    /* apply correction on TFSF boundary */
    tfsf_3d_ez();

    /********** Ex update. *************/
    for (m=0; m<size_x-1; m++)
     for (n=1; n<size_y-1; n++)
      for (p=1; p<size_z-1; p++)
       Ex(m,n,p) = Ex(m,n,p) + 
	ceh*((Hz(m,n,p)-Hz(m,n-1,p)) - (Hy(m,n,p)-Hy(m,n,p-1)));

    /*********** Ey update. ***********/
    for (m=1; m<size_x-1; m++)
     for (n=0; n<size_y-1; n++)
      for (p=1; p<size_z-1; p++)
       Ey(m,n,p) = Ey(m,n,p) + 
	ceh*((Hx(m,n,p)-Hx(m,n,p-1)) - (Hz(m,n,p)-Hz(m-1,n,p)));

    /************ Ez update. *************/
    for (m=1; m<size_x-1; m++)
     for (n=1; n<size_y-1; n++)
      for (p=0; p<size_z-1; p++)
       Ez(m,n,p) = Ez(m,n,p) +
	ceh*((Hy(m,n,p)-Hy(m-1,n,p)) - (Hx(m,n,p)-Hx(m,n-1,p)));

    // zero the nodes associated with the PEC sphere
    r2 = rad*rad;
    for (m=2; m<size_x-2; m++) {
      m2 = (m+0.5-m_c)*(m+0.5-m_c);
      for (n=2; n<size_y-2; n++) {
	n2 = (n+0.5-n_c)*(n+0.5-n_c);
	for (p=2; p<size_z-2; p++) {
	  p2 = (p+0.5-p_c)*(p+0.5-p_c);
	  if (m2+n2+p2 < r2) {
	    // zero surrounding Ex nodes
	    Ex(m,n,p) = 0.0;
	    Ex(m,n+1,p) = 0.0;
	    Ex(m,n,p+1) = 0.0;
	    Ex(m,n+1,p+1) = 0.0;
	    // zero surrounding Ey nodes
	    Ey(m,n,p) = 0.0;
	    Ey(m+1,n,p) = 0.0;
	    Ey(m,n,p+1) = 0.0;
	    Ey(m+1,n,p+1) = 0.0;
	    // zero surrounding Ez nodes
	    Ez(m,n,p) = 0.0;
	    Ez(m+1,n,p) = 0.0;
	    Ez(m,n+1,p) = 0.0;
	    Ez(m+1,n+1,p) = 0.0;
	  }
	}
      }
    }

    /* Apply ABC. */
    abc_3d();

    /* dump raw data-file if time-step a multiple of 5 */
    if ((qTime+1) % 5 == 0) {
      wrtraw_y(nframe, "junk-y");
      nframe++;
    }

  }

  return 0;
}
/* ------------------------- end of main ------------------------- */


/* ######################## ricker_wrapper() ####################### */
double ricker_wrapper(double time) 
{
  return ricker(time,cdtds,ppw);
}
/* --------------------- end of ricker_wrapper() ------------------- */


/* ############################ ricker() ########################### */
double ricker(double time,  // time step 
	      double cdtds, // Courant number
	      double ppw // points/wavelength at most energetic frequency
	      )
{
  double arg,
    argMax = 70.0, // arguments beyond this value are assumed to yield
                    //   zero this allows us to avoid calling exponential
                    //   when result will be effectively zero
    delay = 1.0;    // delay = multiple of inverse of most energetic
                    //         frequency

  arg = pow(M_PI*((cdtds*time)/ppw - delay),2);
  if (arg > argMax) {
    return 0.0;
  } else {
    return (1.0 - 2.0*arg) * exp(-arg);
  }
}
/* ------------------------- end of ricker() ----------------------- */


/* ############################ wrtraw_y() ########################### */
void wrtraw_y(int frame, char *basename)
{ 
  int m, n, p;
  float dim1=size_x, dim2=size_z-1, tmp;
  char filename[100];
  FILE *out;
  
  sprintf(filename,"%s.%d",basename,frame);
  out = fopen(filename,"wb");

  fwrite(&dim1,sizeof(float),1,out);
  fwrite(&dim2,sizeof(float),1,out);

  n=size_y/2;
  for (p=size_z-2; p>=0; p--)
    for (m=0; m<size_x; m++)  {
      tmp = Ez(m,n,p);
      fwrite(&tmp,sizeof(float),1,out);
    }

  fclose(out);
  return;
}
/* ------------------------ end of wrtraw_y ----------------------- */

