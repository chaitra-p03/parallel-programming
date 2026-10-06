// S -> RS 
// PCAP -> PCAPPCAPPC

#include <cuda_runtime.h>
#include <stdio.h>
#include <string.h>

__global__ void makeRS(char *S, char *RS, int n, int r)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i < r)
        RS[i] = S[i % n];
}

int main()
{
    char S[100];
    int r;

    printf("Enter string: ");
    scanf("%s", S);

    printf("Enter output length: ");
    scanf("%d", &r);

    int n = strlen(S);

    char *d_S, *d_RS;

    cudaMalloc(&d_S, n * sizeof(char));
    cudaMalloc(&d_RS, r * sizeof(char));

    cudaMemcpy(d_S, S, n * sizeof(char), cudaMemcpyHostToDevice);

    int blocks = (r + 255) / 256;

    makeRS<<<blocks, 256>>>(d_S, d_RS, n, r);

    char *RS = (char *)malloc((r + 1) * sizeof(char));

    cudaMemcpy(RS, d_RS, r * sizeof(char), cudaMemcpyDeviceToHost);

    RS[r] = '\0';

    printf("Output: %s\n", RS);

    cudaFree(d_S);
    cudaFree(d_RS);
    free(RS);

    return 0;
}