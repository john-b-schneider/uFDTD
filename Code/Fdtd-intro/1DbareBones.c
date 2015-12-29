/* Bare-bones 1D FDTD simulation with a hard source. */

#include <stdio.h>
#include <math.h>

#define SIZE 200

int main()
{
  double ez[SIZE] = {0.}, hy[SIZE] = {0.}, imp0 = 377.0; /*@ \label{bareBonesA} @*/
  int qTime, maxTime = 250, mm;              /*@ \label{bareBonesB} @*/

  /* do time stepping */
  for (qTime = 0; qTime < maxTime; qTime++) {  /*@ \label{bareBonesC} @*/

    /* update magnetic field */
    for (mm = 0; mm < SIZE - 1; mm++)            /*@ \label{bareBonesD} @*/
      hy[mm] = hy[mm] + (ez[mm + 1] - ez[mm]) / imp0;

    /* update electric field */
    for (mm = 1; mm < SIZE; mm++)              /*@ \label{bareBonesE} @*/
      ez[mm] = ez[mm] + (hy[mm] - hy[mm - 1]) * imp0;

    /* hardwire a source node */
    ez[0] = exp(-(qTime - 30.) * (qTime - 30.) / 100.); /*@ \label{bareBonesF} @*/

    printf("%g\n", ez[50]); /*@ \label{bareBonesG} @*/
  } /* end of time-stepping */

  return 0;
}
