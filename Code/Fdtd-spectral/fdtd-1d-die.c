/* 1D FDTD simulation with a TF/SF source, 2nd-order ABC's,
   a hard-wired observation point, and the ability to take
   "snap shots" of the field over the entire computational
   domain. */
/* This version has a dielectric halfspace. */

#include <stdio.h>
#include <math.h>
#include <string.h>

#define SIZE       181   // size of computational domain
#define INTERFACE1 90    // start of slab
#define PPW        50.0  // points per wavelength

double ricker(double time, double position, double ppw, double cdtds);
char get_choice(char *prompt, char *choices);

int main()
{
  double ez[SIZE], epsR[SIZE], hy[SIZE-1], muR[SIZE-1], imp=377.0,
    ezLeft[3][2], ezRight[3][2],
    s, s_free, s_die, cdtds=1.0;
  int qTime, m, j, maxTime, iObs;
  char basename[80], filename[100], choice;
  int nstart, nstep, istart, iend, istep, frame=0;
  FILE *snapshot, *point;

  printf("Enter the number of time steps: ");
  scanf("%d",&maxTime);

  /* Find out if user wants snapshots of the field.
   * Find out the relevant information if so.
   */
  choice = 
    get_choice("Do you want snapshots of the field (y or n)? ","yn");
  if (choice == 'y') {
    printf("Ez nodes are between 0 and %d.\n"
           "Enter first and last nodes in snapshots and stride: ",SIZE-1);
    scanf(" %d %d %d",&istart,&iend,&istep);
    printf("Enter start time and time steps between snapshots: ");
    scanf(" %d %d",&nstart,&nstep);
    printf("Enter the base name for the output files: ");
    scanf(" %s",basename);
  }

  printf("Enter the file name for the field at observation point: ");
  scanf("%s",filename);
  point = fopen(filename,"w");

  printf("Enter the observation point index: ");
  scanf("%d",&iObs);

  /* initialize electric and magnetic fields */
  for (m=0; m<SIZE; m++)
    ez[m] = 0.0;

  for (m=0; m<SIZE-1; m++)
    hy[m] = 0.0;

  for (m=0; m<3; m++)
    for (j=0; j<2; j++) {
      ezLeft[m][j] = 0.;
      ezRight[m][j] = 0.;
    }
  
  /* set relative permittivity */
  for (m=0; m<SIZE; m++)
    if (m<INTERFACE1)
      epsR[m] = 1.0;
    else
      epsR[m] = 9.0;

  /* set relative permeability */
  for (m=0; m<SIZE-1; m++)
    if (m<INTERFACE1)
      muR[m] = 1.0;
    else
      muR[m] = 1.0;

  /* constants for the absorbing boundary condition in freespace and
     the dielectric */
  s_free = 1.;
  s_die = 1/(2.*sqrt(2.));
  
  /* do time stepping */
  for (qTime=0; qTime<maxTime; qTime++) {
    
    /* update magnetic field */
    for (m=0; m<SIZE-1; m++)
      hy[m] = hy[m] + (ez[m+1] - ez[m])/imp/muR[m];

    /* correction for Hy adjacent to TFSF boundary */
    hy[19] -= ricker(qTime,0.0,cdtds,PPW)/imp;

    /* update electric field */
    for (m=1; m<SIZE-1; m++)
      ez[m] = ez[m] + (hy[m] - hy[m-1])*imp/epsR[m];

    /* update fields on edge */
    /* left side */
    s = s_free;
    ez[0] = -((1./s-2.+s)*(ez[2]+ezLeft[0][0])
	      +2.*(s-1./s)*(ezLeft[0][1]+ezLeft[2][1]-ez[1]-ezLeft[1][0])
	      -4.*(1./s+s)*(ezLeft[1][1]))/(1./s+2.+s)-ezLeft[2][0];
    /* right side */
    s = s_die;
    ez[SIZE-1] = -((1./s-2.+s)*(ez[SIZE-3]+ezRight[0][0])
      +2.*(s-1./s)*(ezRight[0][1]+ezRight[2][1]-ez[SIZE-2]-ezRight[1][0])
      -4.*(1./s+s)*(ezRight[1][1]))/(1./s+2.+s)-ezRight[2][0];

    /* memorize old fields near edges */
    for (m=0; m<3; m++) {
      ezLeft[m][0]=ezLeft[m][1];
      ezLeft[m][1]=ez[m];

      ezRight[m][0]=ezRight[m][1];
      ezRight[m][1]=ez[SIZE-1-m];
    }

    /* printf field at fixed evaluation point */
    fprintf(point,"%f\n",ez[iObs]);

    /* correction for Ez adjacent to TFSF boundary */
    ez[20] += ricker(qTime+0.5,-0.5,cdtds,PPW);

    /* generate snapshot if appropriate to do so */
    if (choice == 'y' && qTime>=nstart && (qTime-nstart)%nstep==0) {
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


/* ######################### get_choice() ########################### */
/* This function is used when the user is supposed to enter a single
 * character as part of a selection process, e.g., if the user is
 * supposed to enter y or n to answer yes or no to some question.  The
 * function will accept upper or lower case responses and treat them
 * as the same thing.  The user is prompted for input with the string
 * prompt that is provided as an argument.  The input is compared to
 * possible values in the choices character array .  If there is no
 * match, the user is prompted again and the process repeated.  This
 * seems a cumbersome hack, but it works...
 */
char get_choice(char *prompt, char *choices) {
  int i, done=0, num_choices;
  char line[80], choice;

  num_choices = strlen(choices);
  do {
    if (prompt != NULL)
      printf("%s",prompt);
    fgets(line,79,stdin);
    /* Make sure there isn't a newline character sitting in input stream.
     * If so, read in another line. */
    if(line[0]=='\n')
      fgets(line,79,stdin);
    sscanf(line," %c",&choice);
    if (choice < 'a')
      choice+='a'-'A';
    for (i=0; i<num_choices; i++)
      if (choice == choices[i]) {
	done=1;
	break;
      }
  } while (done==0);

  return choice;
}
/* ----------------------- end of get_choice() --------------------- */


/* ############################ ricker() ########################### */
/* function to calculate the Ricker wavelet
 *   ntime    = current time step
 *   position = evaluation point
 *   courant  = Courant number = c*delta_time/delta_space
 *   ppw      = points per wavelength at the most energetic frequency
 */
double ricker(double qTime, double position, double courant, double ppw) {
  double arg;
  arg = pow(M_PI*((courant*qTime-position)/ppw - 1.0),2);
  return (1.0 - 2.0*arg) * exp(-arg);
} /* ------------------------ end of ricker() ----------------------- */

