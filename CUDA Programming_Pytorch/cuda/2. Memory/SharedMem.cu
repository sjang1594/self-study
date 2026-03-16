
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

constexpr int TILE_SIZE = 16; // Shared Memory Size (16 x 16 = 256 threads/block);

// Global Memory Access
__global__ void MatMulNaive(float* A, float* B, float* C, int N) {
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int row = blockIdx.y * blockDim.y + threadIdx.y;

	float sum = 0.0f;
	if (row >= N || col >= N) return;

	for (int i = 0; i < N; i++) {
		sum += A[row * N + i] * B[row * N + col]; // coasc * stride 
	}
	C[row * N + col] = sum;
}

void matMulCPU(float* A, float* B, float* C, int N) {
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			float sum = 0;
			for (int i = 0; i < N; i++) {
				sum += A[row * N + i] * B[row * N + col];
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
	const int SIZE = N * N * sizeof(int);

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

	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
	free(h_A); free(h_B); free(h_C); free(h_ref);
	return 0;
}