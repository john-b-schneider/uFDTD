#include "fdtd3.h"

void abc(Grid *g) {

  /* simple ABC for left side of grid */
  Ez(0) = Ez(1);

  return;
}

