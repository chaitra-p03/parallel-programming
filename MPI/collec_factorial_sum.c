#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int fact(int x);

int main(int argc, char *argv[]) {
    int rank, size;
    int *arr;
    int *arr2;
    int x, ans;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        arr = malloc(size * sizeof(int));
        arr2 = malloc(size * sizeof(int));
        printf("Enter %d values:\n", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &arr[i]);
        }
    }
    MPI_Scatter(arr, 1, MPI_INT, &x, 1, MPI_INT, 0, MPI_COMM_WORLD);
    ans = fact(x);
    MPI_Gather(&ans, 1, MPI_INT, arr2, 1, MPI_INT,0, MPI_COMM_WORLD);
    if (rank == 0) {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += arr2[i];
        }
        printf("Sum of factorials = %d\n", sum);
        free(arr);
        free(arr2);
    }
    MPI_Finalize();
    return 0;
}

int fact(int x) {
    if (x <= 1) return 1;
    return x * fact(x - 1);
}