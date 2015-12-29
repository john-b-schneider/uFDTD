/*b*/#ifndef _FDTD2_H
#define _FDTD2_H /*n*/

#include <stdio.h>
#include <stdlib.h>

struct Grid {
  double *ez;
  double *hy;
  int sizeX;
  int time, maxTime;
  double cdtds;
};

typedef struct Grid Grid;

/* memory allocation macro */
#define ALLOC_1D(PNTR, NUM, TYPE)                               \
    PNTR = (TYPE *)calloc(NUM, sizeof(TYPE));                   \
    if (!PNTR) {                                                \
      perror("ALLOC_1D");                                       \
      fprintf(stderr,                                           \
          "Allocation failed for " #PNTR ".  Terminating...\n");\
      exit(-1);                                                 \
    }

/* macros for accessing arrays and such */
#define Hy(MM)    g->hy[MM]
#define Ez(MM)    g->ez[MM]
#define SizeX     g->sizeX 
#define Time      g->time  
#define MaxTime   g->maxTime
#define Cdtds     g->cdtds

/*b*//* function prototypes */
void gridInit2(Grid *g);      /*@ \label{fdtd2HD} @*/
void updateH2(Grid *g);       /*@ \label{fdtd2HE} @*/
void updateE2(Grid *g);/*n*/  /*@ \label{fdtd2HF} @*/

#endif  /* matches #ifndef _FDTD2_H */
