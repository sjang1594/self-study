
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

__global__ void matrixIndex(int* out, int width) {
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int row = blockIdx.y * blockDim.y + threadIdx.y;

	if (row < width && col < width) {
		int idx = row * width + col;
		out[idx] = idx;
	}
}

int main()
{
	const int WIDTH = 4;
	int* d_out;
	cudaMalloc(&d_out, WIDTH * WIDTH * sizeof(int));

	dim3 blockDim(2, 2); // block 2 x 2 
	dim3 gridDim(2, 2); // 2 x 2 Grid

	matrixIndex << <gridDim, blockDim >> > (d_out, WIDTH);
	cudaDeviceSynchronize();

	cudaError_t err = cudaGetLastError();
	printf("Kernel launch error: %s\n", cudaGetErrorString(err));

	int h_out[WIDTH * WIDTH];
	cudaMemcpy(h_out, d_out, WIDTH * WIDTH * sizeof(int), cudaMemcpyDeviceToHost);

	for (int r = 0; r < WIDTH; r++) {
		for (int c = 0; c < WIDTH; c++) {
			printf("%3d ", h_out[r * WIDTH + c]);
		}
		printf("\n");
	}

	cudaFree(d_out);
}