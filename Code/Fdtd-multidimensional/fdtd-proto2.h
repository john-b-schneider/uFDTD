/*b*/#ifndef _FDTD_PROTO2_H
#define _FDTD_PROTO2_H /*n*/

#include "fdtd-grid1.h"

/* Function prototypes */
/*b*/void abcInit(Grid *g);
void abc(Grid *g);

void gridInit1d(Grid *g); /*n*/
void gridInit(Grid *g);

void snapshotInit2d(Grid *g);
void snapshot2d(Grid *g);

/*b*/void tfsfInit(Grid *g);
void tfsfUpdate(Grid *g); /*n*/

void updateE2d(Grid *g);
void updateH2d(Grid *g);

#endif
