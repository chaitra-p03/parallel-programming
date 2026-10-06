#include <cuda_runtime.h>
#include <stdio.h>
#include <string.h>

__global__ void replace(int *str, int n){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i < n)
    {
        char c = (char)str[i];
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        {
            atomicExch(&str[i], '*');
        }
    }
}

int main()
{
    char str[100];
    printf("Enter string: ");
    scanf(" %[^\n]", str);
    int n = strlen(str);
    int *arr = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
        arr[i] = str[i];
    int *d_str;
    cudaMalloc(&d_str, n * sizeof(int));
    cudaMemcpy(d_str, arr, n * sizeof(int),cudaMemcpyHostToDevice);
    int blocks = (n + 255) / 256;
    replace<<<blocks, 256>>>(d_str, n);
    cudaMemcpy(arr, d_str, n * sizeof(int),cudaMemcpyDeviceToHost);
    for(int i = 0; i < n; i++)
        str[i] = (char)arr[i];
    str[n] = '\0';
    printf("Output String: %s\n", str);
    cudaFree(d_str);
    free(arr);

    return 0;
}