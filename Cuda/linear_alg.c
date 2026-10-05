#include <stdio.h>
#include <cuda_runtime.h>

__global__ void saxpy(float *x, float *y, float alpha, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < N)
        y[i] = alpha * x[i] + y[i];
}

int main()
{
    int N = 5;
    float alpha = 2;

    float h_x[5] = {1, 2, 3, 4, 5};
    float h_y[5] = {5, 4, 3, 2, 1};

    float *d_x, *d_y;

    int size = N * sizeof(float);

    cudaMalloc(&d_x, size);
    cudaMalloc(&d_y, size);

    cudaMemcpy(d_x, h_x, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, h_y, size, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (N + threads - 1) / threads;

    saxpy<<<blocks, threads>>>(d_x, d_y, alpha, N);

    cudaMemcpy(h_y, d_y, size, cudaMemcpyDeviceToHost);

    printf("Result:\n");
    for (int i = 0; i < N; i++)
        printf("%.1f ", h_y[i]);

    printf("\n");

    cudaFree(d_x);
    cudaFree(d_y);

    return 0;
}