#include <stdio.h>
#include <stdlib.h>
#include "fdtd-macro.h"

static int temporalStride=-2, frame=0, startTime;
static char basename[80];

void snapshotInit3d(Grid *g) {
  
  int choice;
  
  printf("Do you want 2D snapshots of the 3D grid? (1=yes, 0=no) ");
  scanf("%d",&choice);
  if (choice==0) {
    temporalStride=-1;
    return;
  }

  printf("Duration of simulation is %d steps.\n",MaxTime);
  printf("Enter start time and temporal stride: ");
  scanf(" %d %d",&startTime,&temporalStride);
  printf("Enter the base name: ");
  scanf(" %s",basename);

  return;
}

void snapshot3d(Grid *g) {
  int mm, nn, pp;
  float dim1, dim2, temp;
  char filename[100];
  FILE *out;

  /* ensure temporal stride set to a reasonable value */
  if (temporalStride==-1) {
    return;
  } if (temporalStride<-1) {
    fprintf(stderr,
      "snapshot2d: snapshotInit2d must be called before snapshot.\n"
      "            Temporal stride must be set to positive value.\n");
    exit(-1);
  }

  /* get snapshot if temporal conditions met */
  if (Time>=startTime && 
      (Time-startTime)%temporalStride == 0) {

    /************ write the constant-y slice ************/
    sprintf(filename,"%s.%d",basename,frame++);
    out = fopen(filename,"wb");

    /* write dimensions to output file */
    dim1 = SizeX; // express dimensions as floats
    dim2 = SizeZ-1; // express dimensions as floats
    fwrite(&dim1,sizeof(float),1,out);
    fwrite(&dim2,sizeof(float),1,out);

    /* write remaining data */
    nn = SizeY/2;
    for (pp=SizeZ-2; pp>=0; pp--)
      for (mm=0; mm<SizeX; mm++) {
	temp = (float)Ez(mm,nn,pp); // store data as a float
	fwrite(&temp,sizeof(float),1,out); // write the float
      }

    fclose(out);  // close file
  }

  return;
}
