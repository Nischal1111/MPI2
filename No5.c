#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define FILENAME "WarAndPeace.txt"
#define ALPHABET_SIZE 26

int main(int argc, char *argv[])
{
    int rank, size;
    char c;
    int local_counts[ALPHABET_SIZE] = {0};
    int total_counts[ALPHABET_SIZE] = {0};
    FILE *file;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        file = fopen(FILENAME, "r");
        if (file == NULL)
        {
            fprintf(stderr, "Error: Unable to open file %s\n", FILENAME);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        while ((c = fgetc(file)) != EOF)
        {
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            {
                if (c >= 'a')
                    c -= 'a';
                else
                    c -= 'A';
                local_counts[c]++;
            }
        }

        fclose(file);
    }

    MPI_Allreduce(local_counts, total_counts, ALPHABET_SIZE, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("\n---------Letter Counts---------\n");
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            printf("%c: %d\n", 'a' + i, total_counts[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
