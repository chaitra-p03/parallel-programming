#include<cuda_runtime.h>
#include<stdio.h>

__global__ void ranksort(int * d_arr, int * rank, int n){
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if(i<n){
    rank[i]=0;
    for(int j=0; j<n; j++){
      if(d_arr[j]<d_arr[i] || (d_arr[j]==d_arr[i] && j<i)){
        rank[i]++;
      }
    }
  }
}

int main(){
  int n; 
  printf("Enter n: ");
  scanf("%d",&n);

  int * rank = (int *)malloc(n*sizeof(int));
  int * arr = (int *) malloc(n*sizeof(int));
  printf("Enter elements: ");
  for(int i=0; i<n; i++){
    scanf("%d", &arr[i]);
  }

  int * d_arr;
  int * d_rank; 

  cudaMalloc(&d_arr,n*sizeof(int));
  cudaMalloc(&d_rank,n*sizeof(int));

  cudaMemcpy(d_arr,arr,n*sizeof(int),cudaMemcpyHostToDevice);
  ranksort<<<ceil(n/256.0),256>>>(d_arr,d_rank,n);
  cudaMemcpy(rank,d_rank,n*sizeof(int), cudaMemcpyDeviceToHost);
  int res[n];
  for(int i=0; i<n; i++){
    res[rank[i]] = arr[i]; 
  }

  printf("Sorted array: ");
  for(int i = 0; i < n; i++) printf("%d ", res[i]);

  cudaFree(d_arr);
  cudaFree(d_rank);
  free(arr);
  free(rank);
  return 0;


}
