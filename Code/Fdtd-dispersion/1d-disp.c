/*      
 *     1D dispersion relation.  Permits both real and complex roots.
 *
 *     John Schneider
 *     School of Electrical Engineering and Computer Science
 *     Washington State University
 *     Pullman, WA 99164-2752
 *     schneidj@eecs.wsu.edu
 *     (509) 335-4655
 */ 

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double disp1d(double ppw, double cdtds);

int main()
{
  double ppw, ppw_max, ppw_min, delta, cdtds;
  int i, npnts;

  FILE *out;

  out        = fopen("junk-out","w");

  printf("Enter the beginning PPW: ");
  scanf("%lf",&ppw_max);
  printf("Enter the ending PPW: ");
  scanf("%lf",&ppw_min);
  printf("Enter the number of points: ");
  scanf("%d",&npnts);
  printf("Enter the Courant number: ");
  scanf("%lf",&cdtds);
  

  delta = (ppw_max-ppw_min)/(npnts-1);

  for (i=0,ppw=ppw_max; i<npnts; i++,ppw-=delta) {
    //    fprintf(out,"%f %f %f\n",ppw,1./ppw,disp1d(ppw,cdtds));
    fprintf(out,"%g %g\n",ppw,disp1d(ppw,cdtds));
  }

  return 0;
}
/* ------------------------- end of main() --------------------------*/

/*===================================================================*/
double disp1d(double ppw, double cdtds)
{
  double hold;
#ifdef M_PI
  const double pi=M_PI;
#else
  const double pi=3.14159265358979323844;
#endif

  hold = sin(pi * cdtds/ppw);
  if (hold < cdtds) {
    hold = hold/cdtds;
    hold = pi/(asin(hold)*ppw);
  } else {
    hold = 2/ppw;
  }
  
  return hold;
}
/*--------------------- end of disp1d() ------------------------*/
