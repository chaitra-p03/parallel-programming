#include <stdio.h>
#include <cuda_runtime.h>

__global__ void reverse(int *A, int *B, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < N)
        B[N - 1 - i] = A[i];
}

int main()
{
    int N = 10;

    int h_A[10] = {1,2,3,4,5,6,7,8,9,10};
    int h_B[10];

    int *d_A, *d_B;

    int size = N * sizeof(int);

    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);

    int threads = 32;
    int blocks = (N + threads - 1) / threads;

    reverse<<<blocks, threads>>>(d_A, d_B, N);

    cudaMemcpy(h_B, d_B, size, cudaMemcpyDeviceToHost);

    printf("Reversed array:\n");

    for (int i = 0; i < N; i++)
        printf("%d ", h_B[i]);

    printf("\n");

    cudaFree(d_A);
    cudaFree(d_B);

    return 0;
}