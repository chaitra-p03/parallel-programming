#include <stdio.h>
#include <omp.h>

int main(void)
{
    int M, N;
    printf("Enter number of rows M: ");
    scanf("%d", &M);
    printf("Enter number of columns N: ");
    scanf("%d", &N);

    int A[M][N];
    int B[M][N];
    int serial_result[M][N];
    int parallel_result[M][N];
    int row_owner[M];

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = i + j;
            B[i][j] = (i + j) * 2;
        }
    }

    /*  SERIAL ADDITION  */

    double serial_start = omp_get_wtime();

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            serial_result[i][j] = A[i][j] + B[i][j];
        }
    }

    double serial_end = omp_get_wtime();
    double serial_time = serial_end - serial_start;

    /*  PARALLEL ADDITION  */

    omp_set_num_threads(4);
    double parallel_start = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < M; i++){
        row_owner[i] = omp_get_thread_num();
        for (int j = 0; j < N; j++)
        {
            parallel_result[i][j] = A[i][j] + B[i][j];
        }
    }

    double parallel_end = omp_get_wtime();
    double parallel_time = parallel_end - parallel_start;

    /*  DISPLAY RESULTS  */

    printf("\nResultant matrix:\n");

    for (int i = 0; i < M; i++){
        printf("Row %d computed by Thread %d: ", i, row_owner[i]);

        for (int j = 0; j < N; j++) {
            printf("%4d ", parallel_result[i][j]);
        }
        printf("\n");
    }

    printf("\nSerial execution time   = %.9f seconds\n", serial_time);

    printf("Parallel execution time = %.9f seconds\n", parallel_time);

    if (parallel_time > 0){
        printf("Speedup = %.2f\n", serial_time / parallel_time);
    }

    return 0;
}