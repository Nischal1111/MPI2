#include <stdio.h>
#include <mpi.h>

#define NUMDATA 10000

void LoadData(int data[], int count)
{
    for (int i = 0; i < count; i++)
    {
        data[i] = 1;
    }
}

int AddUp(int data[], int count)
{
    int sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += data[i];
    }
    return sum;
}

int main(int argc, char *argv[])
{
    int rank, size;
    int data[NUMDATA];
    int local_sum = 0, total_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    LoadData(data, NUMDATA);

    int start_index = rank * (NUMDATA / size);
    int end_index = (rank + 1) * (NUMDATA / size);
    if (rank == size - 1)
    {
        end_index += NUMDATA % size;
    }
    for (int i = start_index; i < end_index; i++)
    {
        local_sum += data[i];
    }

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    printf("Rank %d has local sum %d\n", rank, local_sum);

    if (rank == 0)
    {
        printf("The total sum of data is %d\n", total_sum);
    }

    MPI_Finalize();
    return 0;
}
