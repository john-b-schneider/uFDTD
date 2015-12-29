#ifndef _FDTD1_H         /*@ \label{impfdtd1A} @*/
#define _FDTD1_H         /*@ \label{impfdtd1B} @*/

#include <stdio.h>
#include <stdlib.h>

struct Grid {            /*@ \label{impfdtd1C} @*/
  double *ez;
  double *hy;
  int sizeX;
  int time, maxTime;
  double cdtds;
};

typedef struct Grid Grid;

/* memory allocation macro */
#define ALLOC_1D(PNTR, NUM, TYPE)                               /*@ \label{impfdtd1D} @*/\
    PNTR = (TYPE *)calloc(NUM, sizeof(TYPE));                   \
    if (!PNTR) {                                                \
      perror("ALLOC_1D");                                       \
      fprintf(stderr,                                           \
          "Allocation failed for " #PNTR ".  Terminating...\n");\
      exit(-1);                                                 \
    }

/* macros for accessing arrays and such */
/* NOTE!!!!  Here we assume the Grid structure is g. */
#define Hy(MM)    g->hy[MM]   /*@ \label{impfdtd1E} @*/
#define Ez(MM)    g->ez[MM]   /*@ \label{impfdtd1F} @*/
#define SizeX     g->sizeX    /*@ \label{impfdtd1G} @*/
#define Time      g->time
#define MaxTime   g->maxTime
#define Cdtds     g->cdtds    /*@ \label{impfdtd1K} @*/

#endif  /* matches #ifndef _FDTD1_H */    /*@ \label{impfdtd1L} @*/
