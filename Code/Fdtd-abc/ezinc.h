#ifndef _MATH_H
#include <math.h>
#endif

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _STDLIB_H
#include <stdlib.h>
#endif
/*b*/
#ifndef _FDTD4_H
#include "fdtd4.h"
#endif

void ezIncInit(Grid *g); /*n*/
double ezInc(double time, double location);
