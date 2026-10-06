
#include <cuda_runtime.h>
#include <stdio.h>
#include <string.h>

#define MAX 50

__global__ void reverseWords(char *words, int *lengths, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i < n)
    {
        int len = lengths[i];
        for(int j = 0; j < len / 2; j++)
        {
            char temp = words[i * MAX + j];
            words[i * MAX + j] = words[i * MAX + len - 1 - j];
            words[i * MAX + len - 1 - j] = temp;
        }
    }
}

int main()
{
    int n;
    printf("Enter number of words: ");
    scanf("%d", &n);
    char *words = (char *)malloc(n * MAX);
    int *lengths = (int *)malloc(n * sizeof(int));

    for(int i = 0; i < n; i++)
    {
        printf("Enter word %d: ", i + 1);
        scanf("%s", &words[i * MAX]);

        lengths[i] = strlen(&words[i * MAX]);
    }

    char *d_words;
    int *d_lengths;

    cudaMalloc(&d_words, n * MAX);
    cudaMalloc(&d_lengths, n * sizeof(int));
    cudaMemcpy(d_words, words, n * MAX, cudaMemcpyHostToDevice);
    cudaMemcpy(d_lengths, lengths, n * sizeof(int), cudaMemcpyHostToDevice);

    int blocks = (n + 255) / 256;
    reverseWords<<<blocks, 256>>>(d_words, d_lengths, n);
    cudaMemcpy(words, d_words, n * MAX, cudaMemcpyDeviceToHost);
    printf("Output: ");
    for(int i = 0; i < n; i++)
        printf("%s ", &words[i * MAX]);

    printf("\n");
    cudaFree(d_words);
    cudaFree(d_lengths);
    free(words);
    free(lengths);

    return 0;
}