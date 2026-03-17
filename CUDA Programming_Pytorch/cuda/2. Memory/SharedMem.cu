
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

/*
*  Matrix Multiplication: C = A x B
*  Naive version: Each thread computes one element of C using global memory only.
*  Tiled version: Each thread block loads a tile of A and B into shared memory, then computes a tile of C.

*  Performance Metrics:
*    - Time (ms)
*    - GFLOPS (Giga FLoating-point Operations Per Second)
*    - Speedup (Naive time / Tiled time)

*  Results:
*  Computing CPU reference (N=512)...
*  === Naive (Global Memory only) ===
*  Time:   3.021 ms
*  GFLOPS: 88.9
*  Correct: YES

*  === Tiled (Shared Memory, TILE=16) ===
*  Time:   3.855 ms
*  GFLOPS: 69.6
*  Correct: YES
*  Speedup: 0.78x

*  === Memory Access Analysis ===
*  Naive  Global reads: 268435456
*  Tiled  Global reads: 16777216  (16.0x reduction)

*  Explanation:
*  - The naive version performs 2*N^3 global memory reads (N^3 for A and N^3 for B).
*  - The tiled version reduces global memory reads by a factor of TILE_SIZE, since each
*    tile of A and B is reused TILE_SIZE times by threads in the block.

*  Observations:
*  - The tiled version may not always be faster than the naive version.
*    The reason why is that it's Warp processing (Latency Hiding). Since it is 512, Warp is good enough to hide the latency of global memory access. 
*    Also, __syncthreads() can introduce overhead (x 2) x 32 threads = 64x overhead. So, the performance can be worse than naive version.
*    If the matrix size is larger (e.g., 1024 or 2048), the tiled version would likely outperform the naive version due to better memory access patterns and reduced global memory reads.
*/
constexpr int TILE_SIZE = 16; // Shared Memory Size (16 x 16 = 256 threads/block);

// Global Memory Access
__global__ void MatMulNaive(float* A, float* B, float* C, int N) {
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int row = blockIdx.y * blockDim.y + threadIdx.y;

	float sum = 0.0f;
	if (row >= N || col >= N) return;

	for (int i = 0; i < N; i++) {
		sum += A[row * N + i] * B[i * N + col]; // coasc * stride 
	}
	C[row * N + col] = sum;
}

__global__ void matmulTiled(float* A, float* B, float* C, int N) {
	__shared__ float s_A[TILE_SIZE][TILE_SIZE];
	__shared__ float s_B[TILE_SIZE][TILE_SIZE];

	int row = blockIdx.y * TILE_SIZE + threadIdx.y;
	int col = blockIdx.x * TILE_SIZE + threadIdx.x;

	float sum = 0.0f;
	int numTiles = (N + TILE_SIZE - 1) / TILE_SIZE;

	for (int t = 0; t < numTiles; t++) {
		// --- Phase 1: Global → Shared 
		int aCol = t * TILE_SIZE + threadIdx.x;
		int bRow = t * TILE_SIZE + threadIdx.y;

		s_A[threadIdx.y][threadIdx.x] = (row < N && aCol < N) ? A[row * N + aCol] : 0.0f;
		s_B[threadIdx.y][threadIdx.x] = (bRow < N && col < N) ? B[bRow * N + col] : 0.0f;

		__syncthreads();  

		for (int k = 0; k < TILE_SIZE; k++) {
			sum += s_A[threadIdx.y][k] * s_B[k][threadIdx.x];
		}

		__syncthreads(); 
	}

	if (row < N && col < N) {
		C[row * N + col] = sum;
	}
}

void matMulCPU(float* A, float* B, float* C, int N) {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			float sum = 0;
			for (int i = 0; i < N; i++) {
				sum += A[row * N + i] * B[i * N + col];
			}
			C[row * N + col] = sum;
		}
	}
}

bool checkEqual(float* ref, float* out, int N, float eps = 1e-2f) {
	for (int i = 0; i < N * N; i++) {
		if (fabsf(ref[i] - out[i]) > eps) {
			printf("  MISMATCH at [%d]: ref=%.4f, got=%.4f\n", i, ref[i], out[i]);
			return false;
		}
	}

	return true;
}

int main() {
	const int N = 512;
	const int SIZE = N * N * sizeof(float);

	float* h_A = (float*)malloc(SIZE);
	float* h_B = (float*)malloc(SIZE);
	float* h_C = (float*)malloc(SIZE);
	float* h_ref = (float*)malloc(SIZE);

	for (int i = 0; i < N * N; i++) {
		h_A[i] = (float)(rand() % 10) / 10.0f;
		h_B[i] = (float)(rand() % 10) / 10.0f;
	}

	printf("Computing CPU reference (N=%d)...\n", N);
	matMulCPU(h_A, h_B, h_ref, N);

	float* d_A, * d_B, *d_C;
	cudaMalloc(&d_A, SIZE);
	cudaMalloc(&d_B, SIZE);
	cudaMalloc(&d_C, SIZE);
	cudaMemcpy(d_A, h_A, SIZE, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_B, SIZE, cudaMemcpyHostToDevice);

	dim3 blockDim(TILE_SIZE, TILE_SIZE);
	dim3 gridDim((N + TILE_SIZE - 1) / TILE_SIZE,
				 (N + TILE_SIZE - 1) / TILE_SIZE);

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	MatMulNaive << <gridDim, blockDim >> > (d_A, d_B, d_C, N);
	cudaDeviceSynchronize();

	printf("\n=== Naive (Global Memory only) ===\n");
	const int RUNS = 10;
	cudaEventRecord(start);
	for (int i = 0; i < RUNS; i++)
		MatMulNaive << <gridDim, blockDim >> > (d_A, d_B, d_C, N);
	cudaEventRecord(stop);
	cudaEventSynchronize(stop);
	float t_naive;
	cudaEventElapsedTime(&t_naive, start, stop);
	t_naive /= RUNS;

	cudaMemcpy(h_C, d_C, SIZE, cudaMemcpyDeviceToHost);
	printf("  Time:   %.3f ms\n", t_naive);
	printf("  GFLOPS: %.1f\n", 2.0f * N * N * N / (t_naive * 1e6f));
	printf("  Correct: %s\n", checkEqual(h_ref, h_C, N) ? "YES" : "NO");

	printf("\n=== Tiled (Shared Memory, TILE=%d) ===\n", TILE_SIZE);
	cudaEventRecord(start);
	for (int i = 0; i < RUNS; i++)
		matmulTiled << <gridDim, blockDim >> > (d_A, d_B, d_C, N);
	cudaEventRecord(stop);
	cudaEventSynchronize(stop);
	float t_tiled;
	cudaEventElapsedTime(&t_tiled, start, stop);
	t_tiled /= RUNS;

	cudaMemcpy(h_C, d_C, SIZE, cudaMemcpyDeviceToHost);
	printf("  Time:   %.3f ms\n", t_tiled);
	printf("  GFLOPS: %.1f\n", 2.0f * N * N * N / (t_tiled * 1e6f));
	printf("  Correct: %s\n", checkEqual(h_ref, h_C, N) ? "YES" : "NO");

	printf("\n  Speedup: %.2fx\n", t_naive / t_tiled);

	printf("\n=== Memory Access Analysis ===\n");
	printf("  Naive  Global reads: %lld\n", (long long)2 * N * N * N);
	printf("  Tiled  Global reads: %lld  (%.1fx reduction)\n",
		(long long)2 * N * N * N / TILE_SIZE,
		(float)TILE_SIZE);

	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
	free(h_A); free(h_B); free(h_C); free(h_ref);
	return 0;
}