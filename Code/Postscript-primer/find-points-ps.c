/* C program to generate a PostScript file which draws a cross
 * if a point is outside of a circular boundary and draws a
 * filled circle if the point is inside the boundary.
 */

#include <stdio.h>
#include <math.h>

int is_inside_pec(double x, double y);

int main() {
  int m, n;

  FILE *out;

  out = fopen("grid.ps","w");  // output file is "grid.ps"

  /* header material for PostScript file */
  fprintf(out,"%%!PS\n"
	  "306 396 translate\n"
	  "/scalefactor 20 def\n"
	  "scalefactor scalefactor scale\n"
	  "1 scalefactor div setlinewidth\n"
	  "/cross {moveto\n"
	  "         -.2 0 rmoveto .4 0 rlineto\n"
	  "         -.2 -.2 rmoveto 0 .4 rlineto stroke} def\n"
	  "/circle {.2 0 360 arc fill} def\n"
	  );

  for (m=-10; m<=10; m++)
    for (n=-10; n<=10; n++)
      if (is_inside_pec(m,n)) {
	fprintf(out,"%d %d circle\n",m,n);
      } else {
	fprintf(out,"%d %d cross\n",m,n);
      }

  fprintf(out,"showpage\n");

  return 0;
}

/* Function returns 1 if point (x,y) is inside a circle (or on
 * the perimeter of circle) and returns 0 otherwise.
 */
int is_inside_pec(double x, double y) {
  double radius = 5.0;

  return x*x + y*y <= radius*radius;
}
