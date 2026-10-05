#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int rank;
    char str[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("Enter a word:\n");
        scanf("%99s", str);
        MPI_Ssend(str, strlen(str) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(str, 100, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Result: %s\n", str);
    }

    else if (rank == 1) {
        MPI_Recv(str, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; str[i] != '\0'; i++) {
            if (isupper(str[i]))
                str[i] = tolower(str[i]);
            else if (islower(str[i]))
                str[i] = toupper(str[i]);
        }
        MPI_Ssend(str, strlen(str) + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}