#ifndef _FDTD_MACRO_TMZ_H
#define _FDTD_MACRO_TMZ_H

#include "fdtd-grid1.h"    /*@ \label{fdtdmacrotmzHE} @*/

/* macros that permit the "Grid" to be specified */
/* one-dimensional grid */
#define Hy1G(G, MM)      G->hy[MM]   /*@ \label{fdtdmacrotmzHA} @*/
#define Chyh1G(G, MM)    G->chyh[MM]
#define Chye1G(G, MM)    G->chye[MM]

#define Ez1G(G, MM)      G->ez[MM]
#define Ceze1G(G, MM)    G->ceze[MM]
#define Cezh1G(G, MM)    G->cezh[MM]

/* TMz grid */
#define HxG(G, MM, NN)     G->hx[(MM) * (SizeYG(G)-1) + (NN)]
#define ChxhG(G, MM, NN) G->chxh[(MM) * (SizeYG(G)-1) + (NN)]
#define ChxeG(G, MM, NN) G->chxe[(MM) * (SizeYG(G)-1) + (NN)]

#define HyG(G, MM, NN)     G->hy[(MM) * SizeYG(G) + (NN)]
#define ChyhG(G, MM, NN) G->chyh[(MM) * SizeYG(G) + (NN)]
#define ChyeG(G, MM, NN) G->chye[(MM) * SizeYG(G) + (NN)]

#define EzG(G, MM, NN)     G->ez[(MM) * SizeYG(G) + (NN)]
#define CezeG(G, MM, NN) G->ceze[(MM) * SizeYG(G) + (NN)]
#define CezhG(G, MM, NN) G->cezh[(MM) * SizeYG(G) + (NN)]

#define SizeXG(G)        G->sizeX
#define SizeYG(G)        G->sizeY
#define SizeZG(G)        G->sizeZ
#define TimeG(G)         G->time
#define MaxTimeG(G)      G->maxTime
#define CdtdsG(G)        G->cdtds
#define TypeG(G)         G->type     /*@ \label{fdtdmacrotmzHB} @*/

/* macros that assume the "Grid" is "g" */
/* one-dimensional grid */
#define Hy1(MM)      Hy1G(g, MM)     /*@ \label{fdtdmacrotmzHC} @*/
#define Chyh1(MM)    Chyh1G(g, MM)
#define Chye1(MM)    Chye1G(g, MM)

#define Ez1(MM)      Ez1G(g, MM)
#define Ceze1(MM)    Ceze1G(g, MM)
#define Cezh1(MM)    Cezh1G(g, MM)

/* TMz grid */
#define Hx(MM, NN)   HxG(g, MM, NN)
#define Chxh(MM, NN) ChxhG(g, MM, NN)
#define Chxe(MM, NN) ChxeG(g, MM, NN) 

#define Hy(MM, NN)   HyG(g, MM, NN)
#define Chyh(MM, NN) ChyhG(g, MM, NN)
#define Chye(MM, NN) ChyeG(g, MM, NN)

#define Ez(MM, NN)   EzG(g, MM, NN)
#define Ceze(MM, NN) CezeG(g, MM, NN) 
#define Cezh(MM, NN) CezhG(g, MM, NN) 

#define SizeX        SizeXG(g)
#define SizeY        SizeYG(g)
#define SizeZ        SizeZG(g)
#define Time         TimeG(g)
#define MaxTime      MaxTimeG(g)
#define Cdtds        CdtdsG(g)
#define Type         TypeG(g)       /*@ \label{fdtdmacrotmzHD} @*/

#endif   /* matches #ifndef _FDTD_MACRO_TMZ_H */
