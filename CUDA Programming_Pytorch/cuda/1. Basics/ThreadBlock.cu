#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

__global__ void printThreadInfo()
{
    int threadId = threadIdx.x;
    int blockId = blockIdx.x;
    int globalId = blockId * blockDim.x + threadId;

    if (globalId < 8) {
        printf("[Block %d | Thread %d] → Global ID: %d\n",
            blockId, threadId, globalId);
    }
}

int main()
{
    printf("1. Thread / Block / Grid Structure \n");
	printf("2. Grid: 2 Blocks, 1 Block: 4 Threads \n");

    // Kernel
    printThreadInfo<<< 2, 4 >>>();
    cudaDeviceSynchronize();
}