/******************************************************************************
* FILE: mpi_scatter.c
* DESCRIPTION:
*   MPI tutorial example code: Collective Communications
* AUTHOR: Blaise Barney
* LAST REVISED: 04/13/05
******************************************************************************/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
#define LEN 3

int main (int argc, char *argv[])
{
int numtasks, rank, sendcount, recvcount, source;

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

float sendbuf[SIZE][LEN] = {
  {rank, 2.0, 3.0},
  {5.0, 6.0, 7.0},
  {9.0, 10.0, 11.0},
  {13.0, 14.0, 15.0}  };
float recvbuf[LEN];

if (numtasks == SIZE) {
  source = 0;
  sendcount = LEN;
  recvcount = LEN;
  MPI_Scatter(
    sendbuf,sendcount,MPI_FLOAT,
    recvbuf,recvcount,MPI_FLOAT,
    source,MPI_COMM_WORLD);

  printf("rank= %d  Results: %f %f %f\n",rank,recvbuf[0],
         recvbuf[1],recvbuf[2]);
  }
else
  printf("Must specify %d processors. Terminating.\n",SIZE);

MPI_Finalize();
}
