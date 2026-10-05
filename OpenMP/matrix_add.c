#include <stdio.h>
#include <omp.h>

int main(void){
    int rows, columns;
    printf("Enter the number of rows M: ");
    scanf("%d", &rows);
    printf("Enter the number of columns N: ");
    scanf("%d", &columns);

    int A[rows][columns];
    int B[rows][columns];
    int result[rows][columns];
    int row_owner[rows];

    printf("Enter elements of Matrix A:\n");
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of Matrix B:\n");
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            scanf("%d", &B[i][j]);
        }
    }

    #pragma omp parallel for
    for (int i = 0; i < rows; i++){
        row_owner[i] = omp_get_thread_num();
        for (int j = 0; j < columns; j++){
            result[i][j] = A[i][j] + B[i][j];
        }
    }

    printf("\nResultant matrix:\n");
    for (int i = 0; i < rows; i++){
        printf("Row %d, computed by Thread %d: ",i, row_owner[i]);
        for (int j = 0; j < columns; j++){
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}