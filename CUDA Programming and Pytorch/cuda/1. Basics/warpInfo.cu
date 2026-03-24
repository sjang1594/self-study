
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

__global__ void warpInfo() {
	int globalId = blockIdx.x * blockDim.x + threadIdx.x;
	int warpId = threadIdx.x / 32; // 32 threads per warp -> go to SM
	int laneId = threadIdx.x % 32; // position in the warp

	if (blockIdx.x == 0 && laneId == 0) {
		printf("[Block 0 | Warp %d] Lane 0 reporting (threads %d-%d)\n", warpId, globalId, globalId + 31);
	}
}

int main()
{
	warpInfo << <1, 64>> > ();
	cudaDeviceSynchronize();
}