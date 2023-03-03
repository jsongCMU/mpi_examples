#include "mpi.h"
#include <stdio.h>

int main( int argc, char *argv[] )
{
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    
    char send_data[4];
    int send_data_size = 4;
    if(rank % 2)
    {
        strncpy(send_data, "foo", 4);
    }
    else
    {
        strncpy(send_data, "bar", 4);
    }
    int dest_rank = (rank+1)%size;
    int tag_id = 0;
    MPI_Request tx_status;
    MPI_Isend(send_data, send_data_size, MPI_CHAR, dest_rank, tag_id, MPI_COMM_WORLD, &tx_status);
    /* DON'T modify send_data until you check send is complete!!! */
    
    char recv_data[4];
    int recv_data_size = 4;
    int source_rank = rank ? rank-1 : size-1;
    MPI_Status comm_status;
    MPI_Recv(recv_data, recv_data_size, MPI_CHAR, source_rank, tag_id, MPI_COMM_WORLD, &comm_status);
    printf("Hello! I am %d of %d; I have received %s from rank %d\n", rank, size, recv_data, source_rank);
    MPI_Finalize();
    return 0;
}