#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {

    int rank, size;
    char word[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        printf("Enter the string:\n");
        scanf("%99s", word);
    }
    MPI_Bcast(word, 100, MPI_CHAR, 0, MPI_COMM_WORLD);
    if (rank < strlen(word)) {
        if (word[rank] >= 'a' && word[rank] <= 'z') {
            word[rank] = toupper(word[rank]);
        }
        else if (word[rank] >= 'A' && word[rank] <= 'Z') {
            word[rank] = tolower(word[rank]);
        }
        printf("Rank %d changed character: %c\n", rank, word[rank]);
    }

    MPI_Finalize();

    return 0;
}