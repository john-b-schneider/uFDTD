/* threaded implementation */
#include <stdio.h>
#include <pthread.h>

void *func1();
void *func2();

double a, b;

int main() {
  pthread_t thread1, thread2;  // ID's for threads

  /* create threads which run in parallel -- one for each function */
  pthread_create(&thread1, NULL, func1, NULL);
  pthread_create(&thread2, NULL, func2, NULL);

  /* wait for first thread to complete */
  pthread_join(thread1,NULL);
  printf("a: %f\n", a);

  /* wait for second thread to complete */
  pthread_join(thread2,NULL);
  printf("b: %f\n", b);

  return 0;
}

void *func1() {
  int i, j;

  for (j=0;j<4000;j++)
    for (i=0;i<1000000;i++)
      a = 3.1456*j+i;

  return NULL;
}
  
void *func2() {
  int i, j;

  for (j=0;j<4000;j++)
    for (i=0;i<1000000;i++)
      b = 3.1456*j+i;

  return NULL;
}
