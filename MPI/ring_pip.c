#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    int rank, size, x;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        printf("Enter the number:\n");
        scanf("%d", &x);
        x++;
        printf("Process %d sending %d to Process %d\n", rank, x, rank + 1);
        MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&x, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Root received final value: %d\n", x);
    }

    else if (rank == size - 1) {
        MPI_Recv(&x, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        x++;
        printf("Process %d sending %d back to Root\n",rank, x);
        MPI_Send(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(&x, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        x++;
        printf("Process %d received and incremented value to %d\n", rank, x);
        MPI_Send(&x, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}