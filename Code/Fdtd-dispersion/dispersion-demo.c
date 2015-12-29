/* 1D FDTD simulation with a TF/SF source, hard-wired observation
 * points, the ability to take "snap shots" of the field over the
 * entire computational domain.  The dielectric region, when present,
 * extends to the right side of the grid and hence the ABC there does
 * not work properly.
 *
 * The user can select between having only free space or having a
 * dielectric slab present.
 */

#include <stdio.h>
#include <math.h>
#include <string.h>

#define SIZE       181   // size of computational domain

double ricker(double time, double position, double ppw, double cdtds);

int main()
{
  double ez[SIZE], hy[SIZE-1], imp0=377.0, cdtds, ez_old=0.0, sc_end, ppw;
  int qTime, m, maxTime;
  char basename[80], filename[100];
  int choice, nstart, nstep, istart, iend, istep, frame=0;
  FILE *snapshot, *point;

  printf("Enter the number of time steps: ");
  scanf("%d",&maxTime);

  printf("Enter Courant number: ");
  scanf("%lf",&cdtds);

  printf("Enter the points per wavelength: ");
  scanf("%lf",&ppw);

  sc_end = cdtds;

  /* Find out if user wants snapshots of the field and
   * find out the relevant information if so.
   */
  printf("Do you want snapshots of the field (1=y, 0=n)? ");
  scanf("%d",&choice);
  if (choice == 1) {
    printf("Ez nodes are between 0 and %d.\n"
           "For snapshots enter first and last nodes and stride: ",SIZE-1);
    scanf(" %d %d %d",&istart,&iend,&istep);
    printf("Enter start time and time steps between snapshots: ");
    scanf(" %d %d",&nstart,&nstep);
    printf("Enter the base name for the output files: ");
    scanf(" %s",basename);
  }

  printf("Enter the file name for the field at observation points: ");
  scanf("%s",filename);
  point = fopen(filename,"w");

  /* initialize electric and magnetic fields */
  for (m=0; m<SIZE; m++)
    ez[m] = 0.0;

  for (m=0; m<SIZE-1; m++)
    hy[m] = 0.0;

  /* do time stepping */
  for (qTime=0; qTime<maxTime; qTime++) {
    
    /* update magnetic field */
    for (m=0; m<SIZE-1; m++)
      hy[m] = hy[m] + (ez[m+1] - ez[m])*cdtds/imp0;

    /* correction for Hy adjacent to TFSF boundary */
    hy[19] -= ricker(qTime,0.0,ppw,cdtds)*cdtds/imp0;

    /* apply ABC at left */
    ez[0] = ez[1];  // BROKEN!

    /* update electric field */
    for (m=1; m<SIZE-1; m++)
      ez[m] = ez[m] + (hy[m] - hy[m-1])*cdtds*imp0;

    /* apply ABC at right */
    ez[SIZE-1] = ez_old +
      (sc_end-1.)/(sc_end+1.)*(ez[SIZE-2]-ez[SIZE-1]);
    ez_old=ez[SIZE-2];

    /* correction for Ez adjacent to TFSF boundary */
    ez[20] += ricker(qTime+0.5,-0.5,ppw,cdtds)*cdtds;

    /* printf field at desired observation points */
    fprintf(point,"%g %g\n",ez[80],ez[130]);

    /* generate snapshot if appropriate to do so */
    if (choice == 1 &&
	qTime>=nstart &&
	(qTime-nstart)%nstep==0) {
      sprintf(filename,"%s.%d",basename,frame++);
      snapshot = fopen(filename,"w");
      for(m=0; m<SIZE; m++)
	fprintf(snapshot,"%g\n",ez[m]);
      fclose(snapshot);
    }

  }
    
    return 0;
}
/* ------------------------- end of main() ------------------------- */

/* ############################ ricker() ########################### */
/* function to calculate the Ricker wavelet
 *   ntime    = current time step
 *   position = evaluation point
 *   courant  = Courant number = c*delta_time/delta_space
 *   ppw      = points per wavelength at the most energetic frequency
 */
double ricker(double qTime, double position, double ppw, double courant) {
  double arg;
  arg = pow(M_PI*((courant*qTime-position)/ppw - 1.0),2);
  return (1.0 - 2.0*arg) * exp(-arg);
} /* ------------------------ end of ricker() ----------------------- */

