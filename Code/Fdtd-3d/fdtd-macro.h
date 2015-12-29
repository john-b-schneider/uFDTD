#ifndef _FDTD_MACRO_H
#define _FDTD_MACRO_H

#include "fdtd-grid.h"

/* macros that permit the "Grid" to be specified */
/* one-dimensional grid */
#define Hy1G(G,MM)     G->hy[MM]
#define Chyh1G(G,MM)   G->chyh[MM]
#define Chye1G(G,MM)   G->chye[MM]

#define Ez1G(G,MM)     G->ez[MM]
#define Ceze1G(G,MM)   G->ceze[MM]
#define Cezh1G(G,MM)   G->cezh[MM]

/* TMz grid */
#define Hx2G(G,MM,NN)   G->hx[(MM)*(SizeYG(G)-1) + NN]
#define Chxh2G(G,MM,NN) G->chxh[(MM)*(SizeYG(G)-1) + NN]
#define Chxe2G(G,MM,NN) G->chxe[(MM)*(SizeYG(G)-1) + NN]

#define Hy2G(G,MM,NN)   G->hy[(MM)*SizeYG(G) + NN]
#define Chyh2G(G,MM,NN) G->chyh[(MM)*SizeYG(G) + NN]
#define Chye2G(G,MM,NN) G->chye[(MM)*SizeYG(G) + NN]

#define Ez2G(G,MM,NN)   G->ez[(MM)*SizeYG(G) + NN]
#define Ceze2G(G,MM,NN) G->ceze[(MM)*SizeYG(G) + NN]
#define Cezh2G(G,MM,NN) G->cezh[(MM)*SizeYG(G) + NN]

/* TEz grid */
#define Ex2G(G,MM,NN)   G->ex[(MM)*SizeYG(G) + NN]
#define Cexe2G(G,MM,NN) G->cexe[(MM)*SizeYG(G) + NN]
#define Cexh2G(G,MM,NN) G->cexh[(MM)*SizeYG(G) + NN]

#define Ey2G(G,MM,NN)   G->ey[(MM)*(SizeYG(G)-1) + NN]
#define Ceye2G(G,MM,NN) G->ceye[(MM)*(SizeYG(G)-1) + NN]
#define Ceyh2G(G,MM,NN) G->ceyh[(MM)*(SizeYG(G)-1) + NN]

#define Hz2G(G,MM,NN)   G->hz[(MM)*(SizeYG(G)-1) + NN]
#define Chzh2G(G,MM,NN) G->chzh[(MM)*(SizeYG(G)-1) + NN]
#define Chze2G(G,MM,NN) G->chze[(MM)*(SizeYG(G)-1) + NN]

/* 3D grid */
#define HxG(G,MM,NN,PP)   G->hx[((MM)*(SizeYG(G)-1) + NN)*(SizeZG(G)-1) + PP]
#define ChxhG(G,MM,NN,PP) G->chxh[((MM)*(SizeYG(G)-1) + NN)*(SizeZG(G)-1) + PP]
#define ChxeG(G,MM,NN,PP) G->chxe[((MM)*(SizeYG(G)-1) + NN)*(SizeZG(G)-1) + PP]

#define HyG(G,MM,NN,PP)   G->hy[((MM)*SizeYG(G) + NN)*(SizeZG(G)-1) + PP]
#define ChyhG(G,MM,NN,PP) G->chyh[((MM)*SizeYG(G) + NN)*(SizeZG(G)-1) + PP]
#define ChyeG(G,MM,NN,PP) G->chye[((MM)*SizeYG(G) + NN)*(SizeZG(G)-1) + PP]

#define HzG(G,MM,NN,PP)   G->hz[((MM)*(SizeYG(G)-1) + NN)*SizeZG(G) + PP]
#define ChzhG(G,MM,NN,PP) G->chzh[((MM)*(SizeYG(G)-1) + NN)*SizeZG(G) + PP]
#define ChzeG(G,MM,NN,PP) G->chze[((MM)*(SizeYG(G)-1) + NN)*SizeZG(G) + PP]

#define ExG(G,MM,NN,PP)   G->ex[((MM)*SizeYG(G) + NN)*SizeZG(G) + PP]
#define CexeG(G,MM,NN,PP) G->cexe[((MM)*SizeYG(G) + NN)*SizeZG(G) + PP]
#define CexhG(G,MM,NN,PP) G->cexh[((MM)*SizeYG(G) + NN)*SizeZG(G) + PP]

#define EyG(G,MM,NN,PP)   G->ey[((MM)*(SizeYG(G)-1) + NN)*SizeZG(G) + PP]
#define CeyeG(G,MM,NN,PP) G->ceye[((MM)*(SizeYG(G)-1) + NN)*SizeZG(G) + PP]
#define CeyhG(G,MM,NN,PP) G->ceyh[((MM)*(SizeYG(G)-1) + NN)*SizeZG(G) + PP]

#define EzG(G,MM,NN,PP)   G->ez[((MM)*SizeYG(G) + NN)*(SizeZG(G)-1) + PP]
#define CezeG(G,MM,NN,PP) G->ceze[((MM)*SizeYG(G) + NN)*(SizeZG(G)-1) + PP]
#define CezhG(G,MM,NN,PP) G->cezh[((MM)*SizeYG(G) + NN)*(SizeZG(G)-1) + PP]

#define SizeXG(G)      G->sizeX
#define SizeYG(G)      G->sizeY
#define SizeZG(G)      G->sizeZ
#define TimeG(G)       G->time
#define MaxTimeG(G)    G->maxTime
#define CdtdsG(G)      G->cdtds
#define TypeG(G)       G->type

/* macros that assume the "Grid" is "g" */
/* one-dimensional grid */
#define Hy1(MM)     Hy1G(g,MM)
#define Chyh1(MM)   Chyh1G(g,MM)   
#define Chye1(MM)   Chye1G(g,MM)   

#define Ez1(MM)     Ez1G(g,MM)     
#define Ceze1(MM)   Ceze1G(g,MM)   
#define Cezh1(MM)   Cezh1G(g,MM)   

/* TMz grid */
#define Hx2(MM,NN)   Hx2G(g,MM,NN)   
#define Chxh2(MM,NN) Chxh2G(g,MM,NN) 
#define Chxe2(MM,NN) Chxe2G(g,MM,NN) 

#define Hy2(MM,NN)   Hy2G(g,MM,NN)   
#define Chyh2(MM,NN) Chyh2G(g,MM,NN) 
#define Chye2(MM,NN) Chye2G(g,MM,NN) 

#define Ez2(MM,NN)   Ez2G(g,MM,NN)   
#define Ceze2(MM,NN) Ceze2G(g,MM,NN) 
#define Cezh2(MM,NN) Cezh2G(g,MM,NN) 

/* TEz grid */
#define Hz2(MM,NN)   Hz2G(g,MM,NN)   
#define Chzh2(MM,NN) Chzh2G(g,MM,NN) 
#define Chze2(MM,NN) Chze2G(g,MM,NN) 

#define Ex2(MM,NN)   Ex2G(g,MM,NN)   
#define Cexe2(MM,NN) Cexe2G(g,MM,NN) 
#define Cexh2(MM,NN) Cexh2G(g,MM,NN) 

#define Ey2(MM,NN)   Ey2G(g,MM,NN)   
#define Ceye2(MM,NN) Ceye2G(g,MM,NN) 
#define Ceyh2(MM,NN) Ceyh2G(g,MM,NN) 

/* 3D grid */
#define Hx(MM,NN,PP)   HxG(g,MM,NN,PP)   
#define Chxh(MM,NN,PP) ChxhG(g,MM,NN,PP) 
#define Chxe(MM,NN,PP) ChxeG(g,MM,NN,PP) 

#define Hy(MM,NN,PP)   HyG(g,MM,NN,PP)   
#define Chyh(MM,NN,PP) ChyhG(g,MM,NN,PP) 
#define Chye(MM,NN,PP) ChyeG(g,MM,NN,PP) 

#define Hz(MM,NN,PP)   HzG(g,MM,NN,PP)   
#define Chzh(MM,NN,PP) ChzhG(g,MM,NN,PP) 
#define Chze(MM,NN,PP) ChzeG(g,MM,NN,PP) 

#define Ex(MM,NN,PP)   ExG(g,MM,NN,PP)   
#define Cexe(MM,NN,PP) CexeG(g,MM,NN,PP) 
#define Cexh(MM,NN,PP) CexhG(g,MM,NN,PP) 

#define Ey(MM,NN,PP)   EyG(g,MM,NN,PP)   
#define Ceye(MM,NN,PP) CeyeG(g,MM,NN,PP) 
#define Ceyh(MM,NN,PP) CeyhG(g,MM,NN,PP) 

#define Ez(MM,NN,PP)   EzG(g,MM,NN,PP)
#define Ceze(MM,NN,PP) CezeG(g,MM,NN,PP)
#define Cezh(MM,NN,PP) CezhG(g,MM,NN,PP) 

#define SizeX       SizeXG(g)
#define SizeY       SizeYG(g)
#define SizeZ       SizeZG(g)
#define Time        TimeG(g)
#define MaxTime     MaxTimeG(g)   
#define Cdtds       CdtdsG(g)
#define Type        TypeG(g)

#endif
