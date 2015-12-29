#ifndef _FDTD_ALLOC_H
#define _FDTD_ALLOC_H

#include <stdio.h>
#include <stdlib.h>

/* memory allocation macros */
#define ALLOC_1D(name,nx,type)                                      \
    name = (type *)calloc(nx,sizeof(type));                         \
    if (!name) {                                                    \
      perror("ALLOC_1D");                                           \
      fprintf(stderr,                                               \
              "Allocation failed for " #name ". Terminating...\n"); \
      exit(-1);                                                     \
    }

#define ALLOC_2D(name,nx,ny,type)                                   \
    name = (type *)calloc((nx)*(ny),sizeof(type));                  \
    if (!name) {                                                    \
      perror("ALLOC_2D");                                           \
      fprintf(stderr,                                               \
              "Allocation failed for " #name ".  Terminating...\n");\
      exit(-1);                                                     \
    }

#define ALLOC_3D(name,nx,ny,nz,type)                                \
    name = (type *)calloc((nx)*(ny)*(nz),sizeof(type));             \
    if (!name) {                                                    \
      perror("ALLOC_2D");                                           \
      fprintf(stderr,                                               \
              "Allocation failed for " #name ".  Terminating...\n");\
      exit(-1);                                                     \
    }

#endif
