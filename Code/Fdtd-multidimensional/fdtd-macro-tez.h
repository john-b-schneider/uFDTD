#ifndef _FDTD_MACRO_TEZ_H
#define _FDTD_MACRO_TEZ_H

#include "fdtd-grid1.h"

/* macros that permit the "Grid" to be specified */
/* one-dimensional grid */
#define Hz1G(G, MM)     G->hz[MM]
#define Chzh1G(G, MM)   G->chzh[MM]
#define Chze1G(G, MM)   G->chze[MM]

#define Ey1G(G, MM)     G->ey[MM]
#define Ceye1G(G, MM)   G->ceye[MM]
#define Ceyh1G(G, MM)   G->ceyh[MM]

/* TEz grid */
#define HzG(G, MM, NN)     G->hz[(MM) * (SizeYG(G) - 1) + (NN)]
#define ChzhG(G, MM, NN) G->chzh[(MM) * (SizeYG(G) - 1) + (NN)]
#define ChzeG(G, MM, NN) G->chze[(MM) * (SizeYG(G) - 1) + (NN)]

#define ExG(G, MM, NN)     G->ex[(MM) * SizeYG(G) + (NN)]
#define CexeG(G, MM, NN) G->cexe[(MM) * SizeYG(G) + (NN)]
#define CexhG(G, MM, NN) G->cexh[(MM) * SizeYG(G) + (NN)]

#define EyG(G, MM, NN)     G->ey[(MM) * (SizeYG(G) - 1) + (NN)]
#define CeyeG(G, MM, NN) G->ceye[(MM) * (SizeYG(G) - 1) + (NN)]
#define CeyhG(G, MM, NN) G->ceyh[(MM) * (SizeYG(G) - 1) + (NN)]

#define SizeXG(G)        G->sizeX
#define SizeYG(G)        G->sizeY
#define SizeZG(G)        G->sizeZ
#define TimeG(G)         G->time
#define MaxTimeG(G)      G->maxTime
#define CdtdsG(G)        G->cdtds
#define TypeG(G)         G->type

/* macros that assume the "Grid" is "g" */
/* one-dimensional grid */
#define Hz1(MM)      Hz1G(g, MM)
#define Chzh1(MM)    Chzh1G(g, MM)
#define Chze1(MM)    Chze1G(g, MM)

#define Ey1(MM)      Ey1G(g, MM)
#define Ceye1(MM)    Ceye1G(g, MM)
#define Ceyh1(MM)    Ceyh1G(g, MM)

/* TEz grid */
#define Hz(MM, NN)   HzG(g, MM, NN)
#define Chzh(MM, NN) ChzhG(g, MM, NN)
#define Chze(MM, NN) ChzeG(g, MM, NN) 

#define Ex(MM, NN)   ExG(g, MM, NN)
#define Cexh(MM, NN) CexhG(g, MM, NN)
#define Cexe(MM, NN) CexeG(g, MM, NN)

#define Ey(MM, NN)   EyG(g, MM, NN)
#define Ceye(MM, NN) CeyeG(g, MM, NN) 
#define Ceyh(MM, NN) CeyhG(g, MM, NN) 

#define SizeX        SizeXG(g)
#define SizeY        SizeYG(g)
#define SizeZ        SizeZG(g)
#define Time         TimeG(g)
#define MaxTime      MaxTimeG(g)
#define Cdtds        CdtdsG(g)
#define Type         TypeG(g)

#endif   /* matches #ifndef _FDTD_MACRO_TEZ_H */
