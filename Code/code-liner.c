/*
 * This program is for adding line number to the end of each line.  It
 * is designed primarily for commenting C code.
 */

#include <unistd.h> /* for getopt() */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABS 8  // number of characters in a tab

int main(int argc, char *argv[]) {
  int i,  c, 
    isMatlab=0,   // matlab code?
    length=70,    // length of a line -- including comments
    line_num=1,   // line number counter
    line_start=1, // line at which to start
    count=0;      // character counter
  char in_filnam[80]="", out_filnam[80]="";
  FILE *in, *out;

  /* Process the command-line arguments. */
  while((c=getopt(argc, argv, "h?i:o:l:n:m"))!=EOF) {
    switch(c) {
    case 'i':
      strcpy(in_filnam,optarg);
      break;
    case 'o':
      strcpy(out_filnam,optarg);
      break;
    case 'l':
      length = atoi(optarg);
      break;
    case 'm':
      isMatlab = 1;
      break;
    case 'n':
      line_start = atoi(optarg);
      break;
    case '?':
    case 'h':
      printf("usage: %s [-h] [-i input_file] [-o output_file] [-l line_length]"
	     " [-n starting_line_num] -m\n"
	     " By default input is taken from STDIN and written to STDOUT.\n"
	     " Use the -m flag for matlab code (change comment delimiter"
	     " to %%).\n",
	     argv[0]);
      exit(0);
      break;
    }
  }


  if (strlen(in_filnam)!=0) {
    fprintf(stderr,"input file name: %s\n",in_filnam);
    in = fopen(in_filnam,"r");
    if (in==NULL) {
      perror(in_filnam);
      exit(-1);
    }
  } else {
    in = stdin;
  }

  if (strlen(out_filnam)!=0) {
    fprintf(stderr,"output file name: %s\n",out_filnam);
    out = fopen(out_filnam,"w");
    if (in==NULL) {
      perror(out_filnam);
      exit(-1);
    }
  } else {
    out = stdout;
  }

  /* discard any leading lines if there is an offset */
  while (line_num < line_start) {
    if ((c=fgetc(in)) == EOF) {
      fprintf(stderr,"Input file terminated before requested output line.\n");
      exit(0);
    }
    if (c=='\n')
      line_num++;
  }
  line_num = 1;  // reset line counter to unity

  while( (c=fgetc(in)) != EOF) {

    if (c !='\n') {

      if (c !='\t') {
	fputc(c,out);
	count++;
      } else {
	fputc(' ',out);
	count++;
	while ((count % 8) != 0) {
	  fputc(' ',out);
	count++;
	}
      }	

    } else {
      for (i=count; i<length-5; i++)
	fputc(' ',out);
      fputc(' ',out);
      if (isMatlab)
	fprintf(out,"%%%3d\n",line_num);
      else
	fprintf(out,"//%3d\n",line_num);
      count = 0;
      line_num++;
    }

  }

  return 0;
}
