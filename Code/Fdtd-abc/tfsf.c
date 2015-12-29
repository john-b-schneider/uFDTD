#ifndef _MATH_H
#include <math.h>
#endif

#include "fdtd4.h"
#include "ezinc.h"

static int tfsfBoundary=0;  /*@ \label{tfsfTrivA} @*/

void tfsfInit(Grid *g) {    /*@ \label{tfsfTrivB} @*/

  printf("Enter location of TFSF boundary: ");
  scanf(" %d",&tfsfBoundary);

  ezIncInit(g); // initialize source function /*@ \label{tfsfTrivD} @*/

  return;
}

void tfsfUpdate(Grid *g) {   /*@ \label{tfsfTrivE} @*/
  /* check if tfsfInit() has been called */
  if (tfsfBoundary<=0) {
    fprintf(stderr,
      "tfsfUpdate: tfsfInit must be called before tfsfUpdate.\n"
      "            Boundary location must be set to positive value.\n");
    exit(-1);
  }

  /* correct Hy adjacent to TFSF boundary */
  Hy(tfsfBoundary) -= ezInc(Time,0.0)*Chye(tfsfBoundary);
    
  /* correct Ez adjacent to TFSF boundary */
  Ez(tfsfBoundary+1) += ezInc(Time+0.5,-0.5);
  
  return;
}
