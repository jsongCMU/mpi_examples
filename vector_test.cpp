#include "mpi.h"
#include <stdio.h>
#include <vector>

int main( int argc, char *argv[] )
{
    // Get PID and total number of threads
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    
    // Set up output buffer
    std::string send_data;
    int send_data_size = 4;
    if(rank % 2)
    {
        send_data="foo";
    }
    else
    {
        send_data="bar";
    }
    
    // Send/receive logistics
    int dest_rank = (rank+1)%size;
    int source_rank = rank ? rank-1 : size-1;
    int tag_id = 0;

    // Send
    MPI_Request tx_status;
    MPI_Isend(send_data.c_str(), send_data_size, MPI_CHAR, dest_rank, tag_id, MPI_COMM_WORLD, &tx_status);
    /* DON'T modify send_data until you check send is complete!!! */

    // Buffer
    std::vector<char> recv_data;
    int recv_data_size = 100;
    // If mesage size completely unknown, then probe to find out
    MPI_Status probe_status;
    MPI_Probe(source_rank, tag_id, MPI_COMM_WORLD, &probe_status); // Note: blocking
    MPI_Get_count(&probe_status, MPI_CHAR, &recv_data_size); // Must know datatype to get correct count
    // Use message size to adjust buffer
    recv_data.resize(recv_data_size); // If no resizing (or buffer too small), will cause runtime error

    // Can also get message size from receive
    // Can often just have buffer that's large enough, then get message size from receive after-the-fact
    // In that case don't need to probe; just look at received number of data
    MPI_Status comm_status;
    MPI_Recv(&recv_data[0], recv_data_size, MPI_CHAR, source_rank, tag_id, MPI_COMM_WORLD, &comm_status);
    int num_ele_recv;
    MPI_Get_count(&comm_status, MPI_CHAR, &num_ele_recv); // Get amount of elements received
    printf("PID %d of %d; I have received %s (%d count, buffer size=%ld) from PID %d (tag = %d)\n", 
        rank, size, &recv_data[0], num_ele_recv, recv_data.size(), comm_status.MPI_SOURCE, comm_status.MPI_TAG);
    MPI_Finalize();
    return 0;
}