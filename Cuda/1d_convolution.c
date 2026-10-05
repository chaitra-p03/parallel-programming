#include<stdio.h>
#include<cuda_runtime.h>

__global__ void convolution(int * d_arr, int * d_mask, int *res, int n, int m){
  int tid = blockIdx.x * blockDim.x + threadIdx.x;
  if(tid<n){
    float f = 0.0;
    int start = tid - m/2;
    for(int i=0; i<m; i++){
      int index = start + i;
      if(index >=0 && index < n){
        f += d_arr[index] * d_mask[i];
      }
    }
    res[tid]=f;
  }
}



int main(){
  int n; 
  int m;
  printf("Enter length of array: \n");
  scanf("%d",&n);
  printf("Enter length of mask array: \n");
  scanf("%d",&m);

  int * arr = (int *)malloc(sizeof(int) * n);
  int * mask = (int *)malloc(sizeof(int) * m);
  int * res = (int *)malloc(sizeof(int) * n);
  printf("Enter elements of array: ");
  for(int i=0; i<n; i++){
    scanf("%d",&arr[i]);
  }
  printf("Enter elements of mask array: ");
  for(int i=0; i<m; i++){
    scanf("%d",&mask[i]);
  }

  int * d_arr;
  int * d_mask;
  int * d_res;

  cudaMalloc(&d_arr, n*sizeof(int));
  cudaMalloc(&d_mask, m*sizeof(int));
  cudaMalloc(&d_res, n*sizeof(int));

  cudaMemcpy(d_arr, arr, n*sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(d_mask, mask, m*sizeof(int), cudaMemcpyHostToDevice);

  int blocks = (n+256-1)/256;
  convolution<<<blocks,256>>>(d_arr, d_mask, d_res, n, m);


  cudaMemcpy(res,d_res,n*sizeof(int), cudaMemcpyDeviceToHost);

  for(int i=0; i<n; i++){
    printf("%d ", res[i]);
  }

  cudaFree(d_arr);
  cudaFree(d_mask);
  cudaFree(d_res);

  free(arr);
  free(mask);
  free(res);

return 0;

}