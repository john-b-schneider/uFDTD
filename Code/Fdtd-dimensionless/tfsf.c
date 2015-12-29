#ifndef _MATH_H
#include <math.h>
#endif

#include "fdtd3.h"
#include "ezinc3.h"

static int tfsfBoundary=0;

void tfsfInit(Grid *g) {    

  printf("Enter location of TFSF boundary: ");
  scanf(" %d",&tfsfBoundary);

  ezIncInit(g); // initialize source function 

  return;
}

void tfsfUpdate(Grid *g) {   
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
