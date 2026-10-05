#include <stdio.h>
#include <omp.h>

#define SIZE 5

int main(void)
{
    int A[SIZE][SIZE];
    int B[SIZE][SIZE];
    int row_owner[SIZE];

    printf("Enter the 25 elements of matrix A:\n");
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            scanf("%d", &A[i][j]);
        }
    }

    omp_set_num_threads(5);

    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++){
        int row_minimum = A[i][0];
        int row_maximum = A[i][0];

        row_owner[i] = omp_get_thread_num();

        for (int j = 1; j < SIZE; j++){
            if (A[i][j] < row_minimum){
                row_minimum = A[i][j];
            }
            if (A[i][j] > row_maximum){
                row_maximum = A[i][j];
            }
        }

        for (int j = 0; j < SIZE; j++){
            if (i == j){
                B[i][j] = 0;
            }
            else if (i > j)
            {
                B[i][j] = row_maximum;
            }
            else
            {
                B[i][j] = row_minimum;
            }
        }
    }

    printf("\nMatrix A:\n");

    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            printf("%4d ", A[i][j]);
        }

        printf("\n");
    }

    printf("\nMatrix B:\n");

    for (int i = 0; i < SIZE; i++){
        printf("Row %d, processed by Thread %d: ", i, row_owner[i]);
        for (int j = 0; j < SIZE; j++){
            printf("%4d ", B[i][j]);
        }
        printf("\n");
    }

    return 0;
}