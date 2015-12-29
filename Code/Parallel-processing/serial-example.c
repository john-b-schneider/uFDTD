/* serial (i.e., non-threaded) implementation */
#include <stdio.h>

void func1();
void func2();

double a, b;  // global variables

int main() {

  func1();  // call first function
  func2();  // call second function

  printf("a: %f\n", a);
  printf("b: %f\n", b);

  return 0;
}

/* do some lengthy calculation */
void func1() {
  int i, j;

  for (j=0;j<4000;j++)
    for (i=0;i<1000000;i++)
      a = 3.1456*j+i;

  return;
}
  
/* do another lengthy calculation (which happens to be the same as
   done by func1()) */
void func2() {
  int i, j;

  for (j=0;j<4000;j++)
    for (i=0;i<1000000;i++)
      b = 3.1456*j+i;

  return;
}
