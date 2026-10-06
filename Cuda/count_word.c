#include<cuda_runtime.h>
#include<stdio.h>
#include<string.h>

__global__ void occurences(char * str, char * word, int * count, int m, int n){
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if(i+n<=m){
    int match = 1;
    for(int j=0; j<n; j++){
      if(str[i+j]!=word[j]){
        match = 0; 
        break;
      }
    }
    if(match==1){
      atomicAdd(count,1);
    }
  }
}


int main(){
  char * str; 
  char * word;
  word = (char *) malloc(100*sizeof(char));
  str = (char *)malloc(100*sizeof(char));

  printf("Enter sentence: ");
  scanf(" %[^\n]", str);
  printf("Enter word: ");
  scanf("%s",word);
  int m = strlen(str);
  int n = strlen(word);
  char * d_str;
  char * d_word;
  int count = 0;
  int * d_count;
  cudaMalloc(&d_str, (m+1)*sizeof(char));
  cudaMalloc(&d_word, (n+1)*sizeof(char));
  cudaMalloc(&d_count, sizeof(int));
  cudaMemcpy(d_str, str, (m+1)*sizeof(char), cudaMemcpyHostToDevice);
  cudaMemcpy(d_word, word, (n+1)*sizeof(char), cudaMemcpyHostToDevice);
  cudaMemcpy(d_count, &count, sizeof(int), cudaMemcpyHostToDevice);

  occurences<<<ceil(m/256.0),256>>>(d_str, d_word, d_count, m, n);

  cudaMemcpy(&count, d_count, sizeof(int), cudaMemcpyDeviceToHost);
  printf("Occurrences = %d\n", count);

  cudaFree(d_str);
  cudaFree(d_word);
  cudaFree(d_count);

  free(str);
  free(word);

  return 0;


}