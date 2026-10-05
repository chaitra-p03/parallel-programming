#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void)
{
    long long n;
    printf("Enter the array size N: ");
    scanf("%lld", &n);
    double *array = malloc((size_t)n * sizeof(double));
    if (array == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (long long i = 0; i < n; i++){
        array[i] = 1.0;
    }

    double serial_sum = 0.0;
    double parallel_sum = 0.0;
    double serial_start = omp_get_wtime();

    for (long long i = 0; i < n; i++){
        serial_sum += array[i];
    }

    double serial_end = omp_get_wtime();
    double parallel_start = omp_get_wtime();
    #pragma omp parallel for reduction(+:parallel_sum)
    for (long long i = 0; i < n; i++){
        parallel_sum += array[i];
    }

    double parallel_end = omp_get_wtime();
    double serial_time = serial_end - serial_start;
    double parallel_time = parallel_end - parallel_start;

    printf("\nSerial sum   = %.2f\n", serial_sum);
    printf("Parallel sum = %.2f\n", parallel_sum);

    printf("\nSerial execution time   = %f seconds\n",serial_time);
    printf("Parallel execution time = %f seconds\n",parallel_time);

    if (parallel_time > 0.0){
        printf("Speedup = %f\n", serial_time / parallel_time);
    }
    free(array);
    return 0;
}