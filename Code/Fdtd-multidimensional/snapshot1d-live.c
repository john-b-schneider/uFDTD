#include "fdtd-macro-tmz.h"

#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// following should correspond to gnuplot location
#define GNUPLOT "/net/local/bin/gnuplot"
//#define GNUPLOT "/sw/bin/gnuplot"

static int temporalStride=-2, spatialStride, 
  startTime, startNode, endNode, frame=0;
static char basename[80], filename[100];

/* stuff for live animation */
static float min, max;
static int live, saveFiles=0, oldTime,  newTime,
  fileNumRange, lastTimeShown;
static float timePerFrame;
static FILE *gnuplot;
struct timeval tv;
struct timezone tz;
struct timespec req, rem;

void snapshotInit1d(Grid *g) { 
  char command[200];
  float fps;
  int choice;
  
  printf("Do you want 1D snapshots? (1=yes, 0=no) ");
  scanf("%d",&choice);
  if (choice==0) {
    temporalStride=-1;
    return;
  }

  printf("Do you want to view the snapshots live? (1=yes, 0=no) ");
  scanf("%d",&live);
  if (live) {
    printf("Enter min and max of vertical axis: ");
    scanf(" %f %f",&min,&max);
    
    printf("Enter the desire frames per second: ");
    scanf(" %f",&fps);
    timePerFrame = 1.0/fps;

    printf("Do you want to save the snapshot data (0=no, 1=yes): ");
    scanf(" %d",&saveFiles);
    if (!saveFiles) {
      sprintf(basename,"/tmp/sim-%d",getpid());
      if (fps < 5.0)
	fileNumRange = 10;
      else
	fileNumRange = 2*fps;
    }
    gnuplot = popen(GNUPLOT,"w");
    printf("Enter any gnuplot commands (enter 'done' when done):\n");
    while(1) {
      scanf(" %[^\n]s",command);
      if (strcmp("done",command)==0)
	break;
      fprintf(gnuplot,"%s\n",command);
    }
  }

  printf("Duration of simulation is %d steps.\n",MaxTime);
  printf("Enter start time and temporal stride: ");
  scanf(" %d %d",&startTime,&temporalStride);
  printf("Grid has %d total nodes (ranging from 0 to %d).\n",
	 SizeX,SizeX-1);
  printf("Enter first node, last node, and spatial stride: ");
  scanf(" %d %d %d",&startNode,&endNode,&spatialStride);
  if (!live || saveFiles) {
    printf("Enter base name for output files: ");
    scanf(" %s",basename);
  }

  lastTimeShown = startTime +
    temporalStride*((MaxTime-1-startTime)/temporalStride);
  //  printf("Last time shown %d\n",lastTimeShown);

  return;
}

void snapshot1d(Grid *g) {
  int mm;
  FILE *snapshot;

  /* ensure temporal stride set to a reasonable value if snapshots to
     be taken */
  if (temporalStride==-1) {
    return;
  } if (temporalStride<-1) {
    fprintf(stderr,
      "snapshot1d: snapshotInit1d must be called before snapshot.\n"
      "            Temporal stride must be set to positive value.\n");
    exit(-1);
  }

  /* get snapshot if temporal conditions met */
  if (Time>=startTime && 
      (Time-startTime)%temporalStride == 0) {

    if (saveFiles)
      sprintf(filename,"%s.%d",basename,frame++);
    else
      sprintf(filename,"%s.%d",basename,frame++ % fileNumRange);

    snapshot=fopen(filename,"w");
    for (mm=startNode; mm <= endNode; mm+=spatialStride)
      fprintf(snapshot,"%g\n",Ez1(mm));
    fflush(snapshot);
    fclose(snapshot);

    if (live) {
      gettimeofday(&tv,&tz);
      newTime = tv.tv_sec + tv.tv_usec/1.e6;

      /* see if we need to wait */
      if (newTime-oldTime < timePerFrame) {
	float waitTime;

        waitTime = (timePerFrame - (newTime-oldTime));
        req.tv_sec = waitTime;  // integer seconds
        req.tv_nsec = (waitTime-req.tv_sec)*1.e9;
        nanosleep(&req,&rem);
      }

      fprintf(gnuplot,"plot [] [%f:%f] '%s'  t '%d' w l\n",min,max,filename,Time);
      fflush(gnuplot);
      
      oldTime = newTime;

      /* uncomment the following to keep last frame visible before moving on */
      //      if (Time == lastTimeShown) {
      //	printf("hit any key to continue");
      //	getchar(); // once to clear old carriage returns in input stream
      //	getchar();
      //      }

    }
  }

  /* If on last display and we're not storing files, delete the files
     in the /tmp directory. */
  if (Time==lastTimeShown && !saveFiles) {
    char command[200];
    sprintf(command,"rm -f %s.*",basename);
    system(command);
  }

  return;
}
