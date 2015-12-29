#ifndef _FDTD_GRID1_H
#include "fdtd-grid1.h"
#endif

/* Function prototypes */
void updateE2d(Grid *g);
void updateH2d(Grid *g);

void gridInit1d(Grid *g);
void gridInit(Grid *g);

void tfsfInit(Grid *g1, Grid *g2);
void tfsfUpdate(Grid *g1, Grid *g2);

void snapshotInit1d(Grid *g);
void snapshot1d(Grid *g);

void snapshotInit2d(Grid *g);
void snapshot2d(Grid *g);
