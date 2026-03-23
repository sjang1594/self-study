#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

#define BLOCK_SIZE 256

// 1. Naive Reduction - Shows Divergence
__global__ void reduceNaive(float* in, float* out, int n) {
    __shared__ float s[BLOCK_SIZE];

    int tid = threadIdx.x;
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    s[tid] = (idx < n) ? in[idx] : 0.0f;
    __syncthreads();

    for (int stride = 1; stride < blockDim.x; stride *= 2) {
        if (tid % (2 * stride) == 0) {
            s[tid] += s[tid + stride];
        }
        __syncthreads();
    }

    if (tid == 0) out[blockIdx.x] = s[0];
}

// 2. Interleaved Reduction
__global__ void reduceInterleaved(float* in, float* out, int n) {
    __shared__ float s[BLOCK_SIZE];

    int tid = threadIdx.x;
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    s[tid] = (idx < n) ? in[idx] : 0.0f;
    __syncthreads();

    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            s[tid] += s[tid + stride];
        }
        __syncthreads();
    }

    if (tid == 0) out[blockIdx.x] = s[0];
}

// 3. Warp Shuffle Reduction
__device__ float warpReduceSum(float val) {
    // FULL_MASK: Warp (all 32 thrads)
    const unsigned FULL_MASK = 0xffffffff;

    for (int offset = 16; offset > 0; offset >>= 1) {
        val += __shfl_down_sync(FULL_MASK, val, offset);
    }
    return val; 
}

__global__ void reduceWarpShuffle(float* in, float* out, int n) {
    __shared__ float s_warpSums[BLOCK_SIZE / 32]; 

    int tid = threadIdx.x;
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    float val = (idx < n) ? in[idx] : 0.0f;

    val = warpReduceSum(val);
    int warpId = tid / 32;
    int laneId = tid % 32;
    if (laneId == 0) s_warpSums[warpId] = val;
    __syncthreads();

    if (warpId == 0) {
        val = (laneId < (blockDim.x / 32)) ? s_warpSums[laneId] : 0.0f;
        val = warpReduceSum(val);
        if (laneId == 0) out[blockIdx.x] = val;
    }
}

float reduceGPU(float* d_in, int n,
    void(*kernel)(float*, float*, int)) {
    int threads = BLOCK_SIZE;
    int blocks = (n + threads - 1) / threads;

    float* d_out;
    cudaMalloc(&d_out, blocks * sizeof(float));

    kernel << <blocks, threads >> > (d_in, d_out, n);

    float* h_out = (float*)malloc(blocks * sizeof(float));
    cudaMemcpy(h_out, d_out, blocks * sizeof(float), cudaMemcpyDeviceToHost);

    float total = 0.0f;
    for (int i = 0; i < blocks; i++) total += h_out[i];

    free(h_out);
    cudaFree(d_out);
    return total;
}

int main() {
    const int N = 1 << 24;  // 16M elements
    const int SIZE = N * sizeof(float);

    float* h_in = (float*)malloc(SIZE);
    for (int i = 0; i < N; i++) h_in[i] = 1.0f;

    float* d_in;
    cudaMalloc(&d_in, SIZE);
    cudaMemcpy(d_in, h_in, SIZE, cudaMemcpyHostToDevice);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    printf("N = %d (%.0fM elements)\n", N, N / 1e6f);
    printf("Expected sum = %d\n\n", N);

    const int RUNS = 20;

    // --- 1. Naive ---
    cudaEventRecord(start);
    float result1;
    for (int i = 0; i < RUNS; i++) result1 = reduceGPU(d_in, N, reduceNaive);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float t1; cudaEventElapsedTime(&t1, start, stop); t1 /= RUNS;
    printf("1. Naive             | sum=%.0f | %.3f ms\n", result1, t1);

    // --- 2. Interleaved ---
    cudaEventRecord(start);
    float result2;
    for (int i = 0; i < RUNS; i++) result2 = reduceGPU(d_in, N, reduceInterleaved);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float t2; cudaEventElapsedTime(&t2, start, stop); t2 /= RUNS;
    printf("2. Interleaved       | sum=%.0f | %.3f ms | %.2fx\n", result2, t2, t1 / t2);

    // --- 3. Warp Shuffle ---
    cudaEventRecord(start);
    float result3;
    for (int i = 0; i < RUNS; i++) result3 = reduceGPU(d_in, N, reduceWarpShuffle);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float t3; cudaEventElapsedTime(&t3, start, stop); t3 /= RUNS;
    printf("3. Warp Shuffle      | sum=%.0f | %.3f ms | %.2fx\n", result3, t3, t1 / t3);

    printf("\n=== Warp Shuffle (8 threads) ===\n");
    printf("Initial:  [1][1][1][1][1][1][1][1]\n");
    printf("offset=4: [2][2][2][2][1][1][1][1]  (0+=4, 1+=5, 2+=6, 3+=7)\n");
    printf("offset=2: [4][4][2][2][1][1][1][1]  (0+=2, 1+=3)\n");
    printf("offset=1: [8][4][2][2][1][1][1][1]  (0+=1)\n");
    printf("Lane 0 = 8 (final sum)\n");

    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaFree(d_in);
    free(h_in);

    return 0;
}
