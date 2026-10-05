#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>

__global__ void euclidean(float *A, float *B, float *D, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < N)
    {
        float diff = A[i] - B[i];
        D[i] = diff * diff;
    }
}

int main()
{
    int N = 1000;

    float *h_A = (float*)malloc(N * sizeof(float));
    float *h_B = (float*)malloc(N * sizeof(float));
    float *h_D = (float*)malloc(N * sizeof(float));

    float *d_A, *d_B, *d_D;

    int size = N * sizeof(float);

    for (int i = 0; i < N; i++)
    {
        h_A[i] = (float)rand() / RAND_MAX;
        h_B[i] = (float)rand() / RAND_MAX;
    }

    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_D, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (N + threads - 1) / threads;

    euclidean<<<blocks, threads>>>(d_A, d_B, d_D, N);

    cudaMemcpy(h_D, d_D, size, cudaMemcpyDeviceToHost);

    float sum = 0;

    for (int i = 0; i < N; i++)
        sum += h_D[i];

    float distance = sqrt(sum);

    printf("Euclidean Distance = %f\n", distance);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_D);

    free(h_A);
    free(h_B);
    free(h_D);

    return 0;
}