#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>

__global__ void counts(char *str, char c, int *d_count, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n)
    {
        if (str[i] == c)
            atomicAdd(d_count, 1);
    }
}

int main()
{
    int n;
    printf("Enter length of string: ");
    scanf("%d", &n);

    int size = (n + 1) * sizeof(char);
    char *str = (char *)malloc(size);
    printf("Enter sentence: ");
    scanf(" %[^\n]", str);
    char ch;
    printf("Enter char: ");
    scanf(" %c", &ch);

    char *d_str;
    int *d_count;
    int count = 0;
    cudaMalloc(&d_str, size);
    cudaMalloc(&d_count, sizeof(int));
    cudaMemcpy(d_str, str, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &count, sizeof(int), cudaMemcpyHostToDevice);
    int threads = 256;
    int blocks = (n + threads - 1) / threads;
    counts<<<blocks, threads>>>(d_str, ch, d_count, n);
    cudaMemcpy(&count, d_count, sizeof(int), cudaMemcpyDeviceToHost);
    printf("Count is %d\n", count);
    cudaFree(d_str);
    cudaFree(d_count);
    free(str);
    return 0;
}