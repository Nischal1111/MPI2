#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size, ball = 0;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2)
    {
        printf("Only runs on 2 processes.\n");
    }
    else
    {

        while (ball < 10)
        {
            if (rank == 0)
            {
                MPI_Send(&ball, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
                MPI_Recv(&ball, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Process 0 received ball: %d\n", ball);
            }
            else if (rank == 1)
            {
                MPI_Recv(&ball, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                ball++;
                MPI_Send(&ball, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
                printf("Process 1 received ball: %d, added 1 and sent back\n", ball);
            }
        }

        MPI_Finalize();
    }
    return 0;
}
