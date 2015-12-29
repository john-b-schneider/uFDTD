/*b*/#ifndef _FDTD3_H
#define _FDTD3_H /*n*/

#include <stdio.h>
#include <stdlib.h>

struct Grid {
  double *ez, /*b*/*ceze, *cezh;/*n*/ /*@ \label{fdtd3hA} @*/
  double *hy, /*b*/*chyh, *chye;/*n*/ /*@ \label{fdtd3hB} @*/
  int sizeX;
  int time, maxTime;
  double cdtds;
};

typedef struct Grid Grid;

/* macros for accessing arrays and such */
#define Hy(MM)    g->hy[MM]
/*b*/#define Chyh(MM)  g->chyh[MM]
#define Chye(MM)  g->chye[MM]  /*n*/

#define Ez(MM)    g->ez[MM]
/*b*/#define Ceze(MM)  g->ceze[MM]
#define Cezh(MM)  g->cezh[MM]  /*n*/

#define SizeX     g->sizeX
#define Time      g->time
#define MaxTime   g->maxTime
#define Cdtds     g->cdtds

/* memory allocation macro */
#define ALLOC_1D(PNTR, NUM, TYPE)                               \
    PNTR = (TYPE *)calloc(NUM, sizeof(TYPE));                   \
    if (!PNTR) {                                                \
      perror("ALLOC_1D");                                       \
      fprintf(stderr,                                           \
          "Allocation failed for " #PNTR ".  Terminating...\n");\
      exit(-1);                                                 \
    }

/* Function prototypes */ /*b*/
void abcInit(Grid *g);
void abc(Grid *g);

void gridInit3(Grid *g);

void snapshotInit(Grid *g);
void snapshot(Grid *g);

void tfsfInit(Grid *g);
void tfsfUpdate(Grid *g);

void updateE3(Grid *g);
void updateH3(Grid *g); /*n*/

#endif  /* matches #ifndef _FDTD3_H */
