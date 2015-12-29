/* Program to demonstrate the use of structures.  Here structures are
passed as arguments to functions.*/

#include <stdio.h>

struct person {
  char *name;
  int age;
  int weight;
};

void changePerson1(struct person p);
void showPerson1(struct person p);

int main() {
  struct person bob, sue;    /*@ \label{structDemo1A} @*/

  sue.name = "Sue";     /*@ \label{structDemo1B} @*/
  sue.age = 21;
  sue.weight = 120;

  bob.name = "Bob";     /*@ \label{structDemo1C} @*/
  bob.age = 62;
  bob.weight = 180;

  showPerson1(sue);      /*@ \label{structDemo1D} @*/
  
  printf("*** Before changePerson1() ***\n");
  showPerson1(bob);      /*@ \label{structDemo1E} @*/
  changePerson1(bob);    /*@ \label{structDemo1F} @*/
  printf("*** After changePerson1() ***\n");
  showPerson1(bob);      /*@ \label{structDemo1G} @*/

  return 0;
}

/* Function to display the elements in a person. */
void showPerson1(struct person p) {      /*@ \label{structDemo1H} @*/
  printf("name: %s\n", p.name);
  printf("age: %d\n", p.age);
  printf("weight: %d\n", p.weight);
  return;
}

/* Function to modify the elements in a person. */
void changePerson1(struct person p) {       /*@ \label{structDemo1I} @*/
  p.age = p.age - 2;
  p.weight = p.weight - 5;
  printf("*** In changePerson1() ***\n");
  showPerson1(p);   /*@ \label{structDemo1J} @*/
  return;
}
