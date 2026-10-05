#include <stdio.h>
#include <omp.h>

#define M 4
#define N 4

void printBinary(int n) {
    if (n > 1)
        printBinary(n / 2);

    printf("%d", n % 2);
}

int main() {

    int A[M][N] = {
        {1, 2, 3, 4},
        {6, 5, 8, 3},
        {2, 4, 10, 1},
        {9, 1, 2, 5}
    };

    int D[M][N];

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 || i == M-1 || j == 0 || j == N-1) {
                D[i][j] = A[i][j];
            }
            else {
                int num = A[i][j];
                int temp = num;
                int bits = 0;
                while (temp > 0) {
                    bits++;
                    temp /= 2;
                }
                int mask = (1 << bits) - 1;
                D[i][j] = num ^ mask;
            }
        }
    }

    printf("Matrix B:\n");

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 || i == M-1 || j == 0 || j == N-1)
                printf("%d\t", A[i][j]);
            else {
                printBinary(D[i][j]);
                printf("\t");
            }
        }
        printf("\n");
    }

    printf("\nMatrix D:\n");

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            printf("%d\t", D[i][j]);

        printf("\n");
    }

    return 0;
}