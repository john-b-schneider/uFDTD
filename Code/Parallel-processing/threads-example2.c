/* threaded implementation -- returning a value */
#include <stdio.h>
#include <stdlib.h> // needed for malloc()
#include <pthread.h>

double *func1();  // now returns a pointer to a double
void *func2();

double a, b;

int main() {
  double *c; // used for return value from func1
  pthread_t thread1, thread2; // ID's for threads

  // typecast the return value of func1 to a void pointer
  pthread_create(&thread1, NULL, (void *)func1, NULL);
  pthread_create(&thread2, NULL, func2, NULL);

  // typecast the address of c to a void pointer to a pointer
  pthread_join(thread1,(void **)&c); /*@ \label{threadExample2A} @*/
  printf("a,c: %f %f\n", a, *c);

  pthread_join(thread2,NULL);
  printf("b: %f\n", b);

  return 0;
}

double *func1() {
  int i, j;

  double *c;  // c is a pointer to a double

  // allocate space to store a double
  c=(double *)malloc(sizeof(double));  /*@ \label{threadExample2B} @*/
  *c = 10.0;

  for (j=0;j<4000;j++)
    for (i=0;i<1000000;i++)
      a = 3.1456*j+i;

  return c;
}
  
void *func2() {
  int i, j;

  for (j=0;j<4000;j++)
    for (i=0;i<1000000;i++)
      b = 3.1456*j+i;

  return NULL;
}
