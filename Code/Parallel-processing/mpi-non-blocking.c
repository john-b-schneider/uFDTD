#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  int i, rank, size, tag_out=10, tag_in=11;
  MPI_Status status;
  MPI_Request *request_snd, *request_rcv;
  
  MPI_Init(&argc,&argv);
  
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank==0) {
    /* "master" process collects and distributes input */
    double *a, *b;

    /* allocate space for input and result */
    a=malloc((size-1)*sizeof(double));
    b=malloc((size-1)*sizeof(double));

    /* allocate space for the send and receive requests */
    request_snd=malloc((size-1)*sizeof(MPI_Request));
    request_rcv=malloc((size-1)*sizeof(MPI_Request));

    /* prompt user for input */
    printf("Enter %d numbers: ",size-1);
    for (i=0; i<size-1; i++)
      scanf("%lf",a+i);

    /* non-blocking send of values to other processes */
    for (i=0; i<size-1; i++)
      MPI_Isend(a+i,1,MPI_DOUBLE,i+1,tag_out,MPI_COMM_WORLD,request_snd+i);

    /* non-blocking reception of results calculated by other process */
    for (i=0; i<size-1; i++)
      MPI_Irecv(b+i,1,MPI_DOUBLE,i+1,tag_in,MPI_COMM_WORLD,request_rcv+i);

    /* wait until we have received all the results */
    for (i=0; i<size-1; i++)
      MPI_Wait(request_rcv+i,&status);

    for (i=0; i<size-1; i++)
      printf("%f\n",b[i]);

  } else {
    /* "slave" process */
    int j;
    double c, d;

    /* receive input from the master process */
    MPI_Recv(&c,1,MPI_DOUBLE,0,tag_out,MPI_COMM_WORLD,&status);
    
    /* do some silly number crunching */
    for (j=0;j<4000;j++)
      for (i=0;i<100000;i++)
        d = c*j+i;
    
    /* send the result back to master */
    MPI_Send(&d,1,MPI_DOUBLE,0,tag_in,MPI_COMM_WORLD);
  }
  
  MPI_Finalize();
  
  return 0;
}
