#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

__global__ void warpDivergence(float* out, float size) {
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	if (index >= size) return;

	if (index % 2 == 0) {
		out[index] = index * 2.0f;
	}
	else {
		out[index] = index * 3.0f;
	}
}

int main()
{
	const int N = 8;
	float* d_bd;
	float h_bd[N];

	cudaMalloc(&d_bd, N * sizeof(float));
	warpDivergence << <1 , N>> > (d_bd, N);
	cudaDeviceSynchronize();
	cudaMemcpy(h_bd, d_bd, N * sizeof(float), cudaMemcpyDeviceToHost);
	for (int i = 0; i < N; i++) {
		printf("out[%d] = %.1f (%s)\n", i, h_bd[i], i % 2 == 0 ? "even *2" : "odd  *3");
	}
	cudaFree(d_bd);
}