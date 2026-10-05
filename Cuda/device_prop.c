#include <stdio.h>
#include <cuda_runtime.h>

int main()
{
    int count;
    cudaGetDeviceCount(&count);

    printf("Number of CUDA devices: %d\n\n", count);

    for (int i = 0; i < count; i++)
    {
        cudaDeviceProp p;
        cudaGetDeviceProperties(&p, i);

        printf("Device %d\n", i);
        printf("Name: %s\n", p.name);
        printf("Number of SMs: %d\n", p.multiProcessorCount);
        printf("Max threads per block: %d\n", p.maxThreadsPerBlock);

        printf("Max thread dimensions: (%d, %d, %d)\n",p.maxThreadsDim[0], p.maxThreadsDim[1],p.maxThreadsDim[2]);

        printf("Max grid dimensions: (%d, %d, %d)\n",p.maxGridSize[0],p.maxGridSize[1],p.maxGridSize[2]);

        printf("Clock frequency: %d kHz\n\n", p.clockRate);
    }

    return 0;
}