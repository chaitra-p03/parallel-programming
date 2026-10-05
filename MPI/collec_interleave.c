#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int len, partSize;
    char s1[100];
    char s2[100];
    char part1[100];
    char part2[100];
    char resultPart[200];
    char result[200];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter String S1: \n");
        scanf("%99s", s1);
        printf("Enter String S2: \n");
        scanf("%99s", s2);
        len = strlen(s1);
    }
    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
    partSize = len / size;
    MPI_Scatter(s1, partSize, MPI_CHAR, part1, partSize, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(s2, partSize, MPI_CHAR, part2, partSize, MPI_CHAR, 0, MPI_COMM_WORLD);
    for (int i = 0; i < partSize; i++) {
        resultPart[2 * i] = part1[i];
        resultPart[2 * i + 1] = part2[i];
    }
    MPI_Gather(resultPart, 2 * partSize, MPI_CHAR, result, 2 * partSize, MPI_CHAR,0, MPI_COMM_WORLD);
    if (rank == 0) {
        result[2 * len] = '\0';
        printf("Resultant String: %s\n", result);
    }
    MPI_Finalize();
    return 0;
}