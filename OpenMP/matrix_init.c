#include <stdio.h>
#include <omp.h>

#define SIZE 5

int main(int argc, char * argv[])
{
    int matrix[SIZE][SIZE];
    int row_owner[SIZE];
    omp_set_num_threads(SIZE);
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        for (int i = thread_id; i < SIZE; i += total_threads){ //useful when threads assigned is less than needed threads
            row_owner[i] = thread_id;
            for (int j = 0; j < SIZE; j++){
                matrix[i][j] = i * SIZE + j + 1;
            }
        }
    }

    printf("\nInitialized matrix:\n");
    for (int i = 0; i < SIZE; i++){
        printf("Row %d, initialized by Thread %d: ", i, row_owner[i]);
        for (int j = 0; j < SIZE; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}