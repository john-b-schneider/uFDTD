#ifndef _FDTD_PROTO1_H
#define _FDTD_PROTO1_H

#include "fdtd-grid1.h"  /*@ \label{fdtdproto1A} @*/

/* Function prototypes */
void gridInit(Grid *g);

void snapshotInit2d(Grid *g);
void snapshot2d(Grid *g);

void updateE2d(Grid *g);
void updateH2d(Grid *g);

#endif
