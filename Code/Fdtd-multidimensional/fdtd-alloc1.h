#ifndef _FDTD_ALLOC1_H
#define _FDTD_ALLOC1_H

#include <stdio.h>
#include <stdlib.h>

/* memory allocation macros */
#define ALLOC_1D(PNTR, NUM, TYPE)                               \
    PNTR = (TYPE *)calloc(NUM, sizeof(TYPE));                   \
    if (!PNTR) {                                                \
      perror("ALLOC_1D");                                       \
      fprintf(stderr,                                           \
          "Allocation failed for " #PNTR ".  Terminating...\n");\
      exit(-1);                                                 \
    }

#define ALLOC_2D(PNTR, NUMX, NUMY, TYPE)                            \
    PNTR = (TYPE *)calloc((NUMX) * (NUMY), sizeof(TYPE));           \
    if (!PNTR) {                                                    \
      perror("ALLOC_2D");                                           \
      fprintf(stderr,                                               \
              "Allocation failed for " #PNTR ".  Terminating...\n");\
      exit(-1);                                                     \
    }

#endif
