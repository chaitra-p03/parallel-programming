#include <stdio.h>
#include <cuda_runtime.h>

__global__ void sine(float *A, float *B, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < N)
        B[i] = sinf(A[i]);
}

int main()
{
    int N = 5;

    float h_A[5] = {0, 1.5708, 3.1416, 4.7124, 6.2832};
    float h_B[5];

    float *d_A, *d_B;

    int size = N * sizeof(float);

    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);

    sine<<<1, N>>>(d_A, d_B, N);

    cudaMemcpy(h_B, d_B, size, cudaMemcpyDeviceToHost);

    printf("Sine values:\n");

    for (int i = 0; i < N; i++)
        printf("%.2f ", h_B[i]);

    printf("\n");

    cudaFree(d_A);
    cudaFree(d_B);

    return 0;
}