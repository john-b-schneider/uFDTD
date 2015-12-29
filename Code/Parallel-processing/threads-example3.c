/* threaded implementation -- passing arguments and 
   returning a value */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double *func1(double *);
void *func2(double *);

double a, b;

int main() {
  double *c; // used for return value from func1
  double d=3.0, e=2.0; // arguments passed to functions
  pthread_t thread1, thread2; // ID's for threads

  pthread_create(&thread1, NULL, (void *)func1, (void *)&d);
  pthread_create(&thread2, NULL, (void *)func2, (void *)&e);

  pthread_join(thread1,(void **)&c);
  printf("a,c: %f %f\n", a, *c);

  pthread_join(thread2,NULL);
  printf("b: %f\n", b);

  return 0;
}

double *func1(double *arg) {
  int i, j;

  double *c;

  c=(double *)malloc(sizeof(double));
  *c = 10.0;

  for (j=0;j<4000;j++)
    for (i=0;i<1000000;i++)
      a = (*arg)*j+i;

  return c;
}
  
void *func2(double *arg) {
  int i, j;

  for (j=0;j<4000;j++)
    for (i=0;i<1000000;i++)
      b = (*arg)*j+i;

  return NULL;
}
