#include <stdio.h>
#include <cuda_runtime.h>

__global__ void vectorAdd(float *A, float *B, float *C, int N)
{
    int i = threadIdx.x;

    if (i < N)
        C[i] = A[i] + B[i];
}

__global__ void dotProduct(float *A, float *B, float *D, int N)
{
    int i = threadIdx.x;

    if (i < N)
        D[i] = A[i] * B[i];
}

int main()
{
    int N = 5;

    float h_A[5] = {1, 2, 3, 4, 5};
    float h_B[5] = {6, 7, 8, 9, 10};

    float h_C[5];
    float h_D[5];

    float *d_A, *d_B, *d_C, *d_D;

    int size = N * sizeof(float);

    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);
    cudaMalloc(&d_D, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    vectorAdd<<<1, N>>>(d_A, d_B, d_C, N);
    dotProduct<<<1, N>>>(d_A, d_B, d_D, N);

    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(h_D, d_D, size, cudaMemcpyDeviceToHost);

    printf("Vector Addition:\n");
    for (int i = 0; i < N; i++)
        printf("%.1f ", h_C[i]);

    float dot = 0;

    for (int i = 0; i < N; i++)
        dot += h_D[i];

    printf("\n\nDot Product = %.1f\n", dot);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    cudaFree(d_D);

    return 0;
}