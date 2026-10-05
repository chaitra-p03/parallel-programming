#include <stdio.h>
#include <omp.h>

#define N 1000

int main() {
    int A[N][N];
    int x[N];
    int result[N];

    for (int i = 0; i < N; i++) {
        x[i] = 1;
        for (int j = 0; j < N; j++) {
            A[i][j] = 1;
        }
    }

    double start = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        result[i] = 0;

        for (int j = 0; j < N; j++) {
            result[i] += A[i][j] * x[j];
        }
    }
    double end = omp_get_wtime();

    printf("Matrix size: %d x %d\n", N, N);
    printf("Execution time: %f seconds\n", end - start);

    return 0;
}