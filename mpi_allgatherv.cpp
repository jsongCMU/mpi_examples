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

int recvcounts[SIZE] = {3,1,3,3};
int displs[SIZE] = {0,3,4,7};
float recvbuf[SIZE*LEN];
float sendbuf[LEN];
for(int i = 0; i < LEN; i++)
    sendbuf[i] = float(rank+1);

if (numtasks == SIZE) {
  sendcount = LEN;
  if(rank==1)
    sendcount = 1;
  recvcount = LEN;
  MPI_Allgatherv(
    sendbuf, sendcount, MPI_FLOAT, 
    recvbuf, recvcounts,
    displs, MPI_FLOAT, MPI_COMM_WORLD);

  for(int pid = 0; pid < numtasks; pid++)
  {
    if(rank==pid)
    {
        printf("\nRank = %d\n", pid);
        float *flt_ptr = recvbuf;
        for(int i=0; i<SIZE; i++)
        {
            for(int j=0; j<recvcounts[i]; j++)
            {
                printf("%f, ", *flt_ptr);
                flt_ptr++;
            }
            printf("\n");
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }
  }
else
  printf("Must specify %d processors. Terminating.\n",SIZE);

MPI_Finalize();
}
