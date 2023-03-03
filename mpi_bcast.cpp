#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
#define LEN 3

int main (int argc, char *argv[])
{
int numtasks, rank;

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

float txrxbuf[LEN];
int txrxcount = LEN;
for(int i = 0; i < LEN; i++)
    txrxbuf[i] = float(rank+1);
int root = 0;

if (numtasks == SIZE) {
  MPI_Bcast(txrxbuf, txrxcount, MPI_FLOAT, root, MPI_COMM_WORLD);

  for(int pid = 0; pid < numtasks; pid++)
  {
    if(rank==pid)
    {
        printf("\nRank = %d\n", pid);
        for(int i=0; i<LEN; i++)
        {
            printf("%f, ", txrxbuf[i]);
        }
        printf("\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }
  }
else
  printf("Must specify %d processors. Terminating.\n",SIZE);

MPI_Finalize();
}
