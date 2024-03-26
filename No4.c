#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int size;
    int rank;
    int tag = 0;
    int count;
    MPI_Status status;
    int *data = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        for (int i = 1; i < size; i++)
        {
            MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, MPI_INT, &count);
            data = (int *)malloc(count * sizeof(int));
            MPI_Recv(data, count, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("Node ID: %d; tag: %d; MPI_Get_count: %d; \n", status.MPI_SOURCE, status.MPI_TAG, count);
            free(data);
        }
    }
    else
    {
        int num_elements = rand() % 100;
        data = (int *)malloc(num_elements * sizeof(int));
        MPI_Send(data, num_elements, MPI_INT, 0, tag, MPI_COMM_WORLD);
        free(data);
    }

    MPI_Finalize();
    return 0;
}
