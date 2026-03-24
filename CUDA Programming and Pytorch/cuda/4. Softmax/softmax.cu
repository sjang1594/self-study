#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <math.h>

#define BLOCK_SIZE 256

/* Classical (Global) Softmax Implementation */

struct BlockInfo {
	const int rows = 1024;	// Batch Size
	const int cols = 256;	// Seqence Length
	const int n = rows * cols;
	const int bytes = n * sizeof(float);
};

// Finding the max 
__global__ void softmax_pass1(const float* in, float* out, int N) {
	__shared__ float s[BLOCK_SIZE];

	int tid = threadIdx.x;
	int idx = blockIdx.x * blockDim.x + threadIdx.x;

	s[tid] = (idx < N) ? in[idx] : -INFINITY;
	__syncthreads();

	for (int i = blockDim.x / 2; i > 0; i >>= 1) {
		if (tid < i) {
			s[tid] = fmaxf(s[tid], s[tid + i]);
		}
		__syncthreads();
	}

	if (tid == 0) {
		out[blockIdx.x] = s[0];
	}
}

// Subtract
__global__ void softmax_pass2_global(const float* in, float* out, float global_max, int N) {
	int tid = threadIdx.x;
	int idx = blockIdx.x * blockDim.x + threadIdx.x;

	if (idx < N)
		out[idx] = expf(in[idx] - global_max);
}

// Subtract 
__global__ void softmax_pass2_per_row(const float* in, float* out, const float* row_max, int N) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;

	if (idx < N)
		out[idx] = expf(in[idx] - row_max[blockIdx.x]);
}

// Sum per row
__global__ void softmax_sum_per_row(const float* in, float* row_sum, int N) {
	__shared__ float s[BLOCK_SIZE];
	int tid = threadIdx.x;
	int idx = blockIdx.x * blockDim.x + threadIdx.x;

	s[tid] = (idx < N) ? in[idx] : 0.0f;
	__syncthreads();

	for (int i = blockDim.x / 2; i > 0; i >>= 1) {
		if (tid < i) s[tid] += s[tid + i];
		__syncthreads();
	}

	if (tid == 0) row_sum[blockIdx.x] = s[0];
}

// Normalize
__global__ void softmax_pass3_global(float* out, float inv_sum, int N)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx < N)
		out[idx] *= inv_sum;
}

// Normalize
__global__ void softmax_pass3_per_row(float* out, float* row_sum, int N)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx < N)
		out[idx] /= row_sum[blockIdx.x];
}

// Online Softmax
__global__ void softmax_online(const float* in, float* out, int N)
{
	__shared__ float s_x[BLOCK_SIZE];

	int tid = threadIdx.x;
	int base = blockIdx.x * N;

	float running_max = -INFINITY;
	float running_sum = 0.0f;

	for (int i = tid; i < N; i += BLOCK_SIZE) {
		float xi = in[base + i];
		float new_max = fmaxf(running_max, xi);
		running_sum = running_sum * expf(running_max - new_max) + expf(xi - new_max);
		running_max = new_max;
	}

	__shared__ float s_max[BLOCK_SIZE];
	__shared__ float s_sum[BLOCK_SIZE];

	s_max[tid] = running_max;
	s_sum[tid] = running_sum;

	__syncthreads();

	for (int i = BLOCK_SIZE * 0.5; i > 0; i >>= 1) {
		if (tid < i) {
			float m1 = s_max[tid], m2 = s_max[tid + i];
			float s1 = s_sum[tid], s2 = s_sum[tid + i];

			float n_m = fmaxf(m1, m2);
			float n_s = s1 * expf(m1 - n_m) + s2 * expf(m2 - n_m);
			s_max[tid] = n_m;
			s_sum[tid] = n_s;
		}

		__syncthreads();
	}

	float global_max = s_max[0];
	float global_sum = s_sum[0];

	for (int i = tid; i < N; i += BLOCK_SIZE) {
		out[base + i] = expf(in[base + i] - global_max) / global_sum;
	}
}

void softmax_naive_global(const float* d_in, float* d_out, int N)
{
	int threads = BLOCK_SIZE;
	int blocks = (N + threads - 1) / threads; // GridDim = 1024, BlockDim = 256

	float* d_block_max;
	cudaMalloc(&d_block_max, blocks * sizeof(float));

	softmax_pass1 << <blocks, threads >> > (d_in, d_block_max, N);
	float* h_block_max = (float*)malloc(blocks * sizeof(float));
	cudaMemcpy(h_block_max, d_block_max, blocks * sizeof(float), cudaMemcpyDeviceToHost);
	float global_max = -INFINITY;

	for (int i = 0; i < blocks; i++)
		global_max = fmaxf(global_max, h_block_max[i]);

	softmax_pass2_global << <blocks, threads >> > (d_in, d_out, global_max, N);

	float* h_out = (float*)malloc(N * sizeof(float));
	cudaMemcpy(h_out, d_out, N * sizeof(float), cudaMemcpyDeviceToHost);
	float sum = 0.0f;
	for (int i = 0; i < N; i++) sum += h_out[i];

	softmax_pass3_global << <blocks, threads >> > (d_out, 1.0f / sum, N);

	cudaFree(d_block_max);
	free(h_out);
	free(h_block_max);
}

void softmax_naive_per_row(const float* d_in, float* d_out, int rows, int cols) {
	int threads = cols; // 256
	int blocks = rows; // 1024

	int N = rows * cols;

	float* d_row_max, * d_row_sum;
	cudaMalloc(&d_row_max, blocks * sizeof(float));
	cudaMalloc(&d_row_sum, blocks * sizeof(float));

	softmax_pass1 << <blocks, threads >> > (d_in, d_row_max, N);
	softmax_pass2_per_row << <blocks, threads >> > (d_in, d_out, d_row_max, N);
	softmax_sum_per_row << < blocks, threads >> > (d_out, d_row_sum, N);
	softmax_pass3_per_row << <blocks, threads >> > (d_out, d_row_sum, N);

	cudaFree(d_row_max);
	cudaFree(d_row_sum);
}

void softmax_cpu_row_helper(const float* in, float* out, const int& N) {
	float m = in[0];
	for (int i = 1; i < N; i++)
		m = fmaxf(m, in[i]);

	float s = 0.0f;
	for (int i = 0; i < N; i++) {
		out[i] = expf(in[i] - m);
		s += out[i];
	}

	for (int i = 0; i < N; i++)
		out[i] /= s;
}

void softmax_cpu_global(const float* in, float* out, const int& N)
{
	softmax_cpu_row_helper(in, out, N);
}

void softmax_cpu_per_row(const float* in, float* out, int rows, int cols)
{
	for (int r = 0; r < rows; r++) {
		softmax_cpu_row_helper(in + r * cols, out + r * cols, cols);
	}
}

bool verify(const float* ref, const float* got, int n, float eps = 1e-4f)
{
	for (int i = 0; i < n; i++) {
		if (fabsf(ref[i] - got[i]) > eps) {
			printf("  MISMATCH at [%d]: ref=%.6f, got=%.6f\n", i, ref[i], got[i]);
			return false;
		}
	}
	return true;
}

int main()
{
	const int RUNS = 100;
	BlockInfo blockInfo;
	printf("Softmax Kernel\n");
	printf("Batch Size: %d, Sequence Length: %d\n", blockInfo.rows, blockInfo.cols);
	printf("Data Size: %.1f bytes\n", blockInfo.bytes / 1e6f);

	printf("\n=== Memory Access per kernel call ===\n");
	printf("  V1 Naive  : ~%.1f MB  (3 passes)\n", 3.0f * blockInfo.bytes / 1e6f);
	printf("  V2 Online : ~%.1f MB  (1 pass read + 1 pass write)\n", 2.0f * blockInfo.bytes / 1e6f);
	printf("  V3 Warp   : ~%.1f MB  (1 pass, no shared mem)\n", 2.0f * blockInfo.bytes / 1e6f);

	float* h_in = (float*)malloc(blockInfo.bytes);
	float* h_ref_global = (float*)malloc(blockInfo.bytes);
	float* h_out = (float*)malloc(blockInfo.bytes);
	float* h_ref_per_row = (float*)malloc(blockInfo.bytes);

	srand(42);

	for (int i = 0; i < blockInfo.n; i++) {
		h_in[i] = (float)(rand() % 100) / 10.0f - 5.0f; // Random values in range [-5, 5]
	}

	softmax_cpu_global(h_in, h_ref_global, blockInfo.n);
	softmax_cpu_per_row(h_in, h_ref_per_row, blockInfo.rows, blockInfo.cols);

	float* d_in, * d_out;
	cudaMalloc(&d_in, blockInfo.bytes);
	cudaMalloc(&d_out, blockInfo.bytes);
	cudaMemcpy(d_in, h_in, blockInfo.bytes, cudaMemcpyHostToDevice);

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	printf("\n===== Benchmarks =====\n");
	printf("\n=== Global Softmax ===\n");
	cudaEventRecord(start);
	for (int i = 0; i < RUNS; i++) softmax_naive_global(d_in, d_out, blockInfo.n);
	cudaEventRecord(stop);
	cudaEventSynchronize(stop);

	float t_naive;
	cudaEventElapsedTime(&t_naive, start, stop);
	t_naive /= RUNS;
	cudaMemcpy(h_out, d_out, blockInfo.bytes, cudaMemcpyDeviceToHost);
	printf(" V1 Naive : %.3f ms\n", t_naive);

	bool ok = verify(h_ref_global, h_out, blockInfo.n);
	printf(" V1 Naive : %.3f ms  %s\n", t_naive, ok ? "PASS" : "FAIL");

	printf("\n=== Per-row Softmax ===\n");
	cudaEventRecord(start);
	for (int i = 0; i < RUNS; i++) softmax_naive_per_row(d_in, d_out, blockInfo.rows, blockInfo.cols);
	cudaEventRecord(stop);
	cudaEventSynchronize(stop);

	float t_row;
	cudaEventElapsedTime(&t_row, start, stop);
	t_row /= RUNS;
	cudaMemcpy(h_out, d_out, blockInfo.bytes, cudaMemcpyDeviceToHost);
	printf(" V1 Row   : %.3f ms\n", t_row);

	ok = verify(h_ref_per_row, h_out, blockInfo.n);
	printf(" V1 Row   : %.3f ms  %s\n", t_row, ok ? "PASS" : "FAIL");

	// Online Softmax
	dim3 threads_online(BLOCK_SIZE);
	dim3 blocks_online(blockInfo.rows);

    printf("\n=== Online Softmax ===\n");
	cudaEventRecord(start);
	for (int i = 0; i < RUNS; i++) {
		softmax_online << <blocks_online, threads_online >> > (d_in, d_out, blockInfo.cols);
	}
	cudaEventRecord(stop);
	cudaEventSynchronize(stop);

	float t_online;
	cudaEventElapsedTime(&t_online, start, stop);
	t_online /= RUNS;
	cudaMemcpy(h_out, d_out, blockInfo.bytes, cudaMemcpyDeviceToHost);
	printf(" V1 Online : %.3f ms\n", t_online);

	ok = verify(h_ref_per_row, h_out, blockInfo.n);
	printf(" V1 Online : %.3f ms  %s\n", t_online, ok ? "PASS" : "FAIL");

	cudaFree(d_in);
	cudaFree(d_out);
	free(h_in);
	free(h_ref_global);
	free(h_ref_per_row);
	free(h_out);
	return 0;
}