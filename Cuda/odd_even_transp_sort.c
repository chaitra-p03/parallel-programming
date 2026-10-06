#include<cuda_runtime.h>
#include<stdio.h>

__global__ void func(int * arr, int n, int phase){
  int i = 2*(blockIdx.x * blockDim.x + threadIdx.x) + phase;
  if(i+1 < n){
    if(arr[i] > arr[i+1]){
      int temp = arr[i];
      arr[i] = arr[i+1];
      arr[i+1] = temp;
      }
  }
}

int main(){
  int n; 
  printf("Enter no of elements: ");
  scanf("%d",&n);

  int * arr = (int *)malloc(n*sizeof(int));
  printf("Enter elements: ");
  for(int i=0; i<n; i++){
    scanf("%d", &arr[i]);
  }
3
  int * d_res;
  cudaMalloc(&d_res, sizeof(int)*n);
  cudaMemcpy(d_res, arr, n*sizeof(int), cudaMemcpyHostToDevice);
  for(int phase = 0; phase<n; phase++){
    func<<<ceil(n/256.0), 256>>>(d_res,n,phase%2);
    cudaDeviceSynchronize();
  }

  cudaMemcpy(arr, d_res, n*sizeof(int), cudaMemcpyDeviceToHost);

  for(int i=0; i<n; i++){
    printf("%d ", arr[i]);
  }

  cudaFree(d_res);
  free(arr);

  return 0;


}