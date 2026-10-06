%%writefile add3.cu

#include <cuda_runtime.h>
#include <stdio.h>
#include <string.h>

__global__ void repeat(char *S, char *out, int len, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i < len)
    {
        for(int j = 0; j < N; j++)
            out[j * len + i] = S[i];
    }
}

int main()
{
    char S[100];
    int N;
    printf("Enter string: ");
    scanf("%s", S);

    printf("Enter N: ");
    scanf("%d", &N);

    int len = strlen(S);
    char *d_S, *d_out;

    cudaMalloc(&d_S, len * sizeof(char));
    cudaMalloc(&d_out, N * len * sizeof(char));

    cudaMemcpy(d_S, S, len * sizeof(char), cudaMemcpyHostToDevice);
    int blocks = (len + 255) / 256;
    repeat<<<blocks, 256>>>(d_S, d_out, len, N);
    char *out = (char *)malloc(N * len + 1);

    cudaMemcpy(out, d_out, N * len, cudaMemcpyDeviceToHost);

    out[N * len] = '\0';
    printf("Output: %s\n", out);

    cudaFree(d_S);
    cudaFree(d_out);
    free(out);

    return 0;
}