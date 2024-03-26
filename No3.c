#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int parcel = 1;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 3)
    {
        if (rank == 0)
        {
            printf("This program requires 3 or more processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0)
    {
        MPI_Send(&parcel, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process %d sent parcel %d to Process 1\n", rank, parcel);
    }

    while (1)
    {
        if (rank < size - 1)
        {
            MPI_Recv(&parcel, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process %d received parcel %d from Process %d\n", rank, parcel, rank - 1);
            // Increment parcel
            parcel += 1;
            MPI_Send(&parcel, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
            printf("Process %d sent parcel %d to Process %d\n", rank, parcel, (rank + 1) % size);
        }
        else
        {
            MPI_Send(&parcel, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            printf("Process %d sent parcel %d to Process 0\n", rank, parcel);
            break;
        }
    }

    if (rank == 0)
    {
        MPI_Recv(&parcel, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received final parcel %d from Process %d\n", parcel, size - 1);
    }

    MPI_Finalize();
    return 0;
}
