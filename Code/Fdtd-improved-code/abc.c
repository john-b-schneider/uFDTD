/* Functions to terminate left side of grid. */

#include "fdtd3.h"

// Initialize the ABC -- in this case, there is nothing to do.
void abcInit(Grid *g) {

  return;
}

// Apply the ABC -- in this case, only to the left side of grid.
void abc(Grid *g) {

  /* simple ABC for left side of grid */
  Ez(0) = Ez(1);

  return;
}
