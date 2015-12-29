/* Program to demonstrate the use of pointers to structures. */

#include <stdlib.h>
#include <stdio.h>

#define ALLOC_1D(PNTR, NUM, TYPE)                               \
    PNTR = (TYPE *)calloc(NUM, sizeof(TYPE));                   \
    if (!PNTR) {                                                \
      perror("ALLOC_1D");                                       \
      fprintf(stderr,                                           \
          "Allocation failed for " #PNTR ".  Terminating...\n");\
      exit(-1);                                                 \
    }

struct person {
  char *name;
  int age;
  int weight;
};

typedef struct person Person;   /*@ \label{structDemo2A} @*/

void changePerson2(Person *p);
void showPerson2(Person *p);  

int main() {
  Person *robert, *susan;     /*@ \label{structDemo2B} @*/

  ALLOC_1D(susan, 1, Person);     /*@ \label{structDemo2C} @*/
  ALLOC_1D(robert, 1, Person);

  susan->name = "Susan";
  susan->age = 21;
  susan->weight = 120;

  robert->name = "Robert";
  robert->age = 62;
  robert->weight = 180;

  showPerson2(susan);
  
  printf("*** Before changePerson2() ***\n");
  showPerson2(robert);
  changePerson2(robert);
  printf("*** After changePerson2() ***\n");
  showPerson2(robert);

  return 0;
}

/* Function to display the elements in a person. */
void showPerson2(Person *p) {
  printf("name: %s\n", p->name);
  printf("age: %d\n", p->age);
  printf("weight: %d\n", p->weight);
  return;
}

/* Function to modify the elements in a person. */
void changePerson2(Person *p) {
  p->age = p->age - 2;
  p->weight = p->weight - 5;
  printf("*** In changePerson2() ***\n");
  showPerson2(p);
  return;
}
