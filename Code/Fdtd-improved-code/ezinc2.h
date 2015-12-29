/* Header file to accompany ezinc2.c. */

#ifndef _EZINC2_H   /*@ \label{ezincHA} @*/
#define _EZINC2_H   /*@ \label{ezincHB} @*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "fdtd2.h"   /*@ \label{ezincHC} @*/

void ezIncInit(Grid *g);
double ezInc(double time, double location);

#endif  /* matches #ifndef _EZINC2_H */          /*@ \label{ezincHD} @*/
