#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int len, partSize;
    int count = 0, total = 0;
    int counts[100];
    char str[100];
    char part[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        printf("Enter a string: ");
        scanf("%99s", str);
        len = strlen(str);
    }
    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
    partSize = len / size;
    MPI_Scatter(str, partSize, MPI_CHAR, part, partSize, MPI_CHAR, 0, MPI_COMM_WORLD);
    for (int i = 0; i < partSize; i++) {
        if (part[i] != 'a' &&
            part[i] != 'e' &&
            part[i] != 'i' &&
            part[i] != 'o' &&
            part[i] != 'u' &&
            part[i] != 'A' &&
            part[i] != 'E' &&
            part[i] != 'I' &&
            part[i] != 'O' &&
            part[i] != 'U') {
            count++;
        }
    }

    MPI_Gather(&count, 1, MPI_INT, counts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("\nNon-vowels found by each process:\n");
        for (int i = 0; i < size; i++) {
            printf("Process %d = %d\n", i, counts[i]);
            total += counts[i];
        }
        printf("Total non-vowels = %d\n", total);
    }
    MPI_Finalize();
    return 0;
}