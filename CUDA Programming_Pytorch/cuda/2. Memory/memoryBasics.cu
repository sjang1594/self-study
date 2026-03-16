
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>


// 1. Global Memory
// - Possible for all threads can access, but slow (400 ~ 800) cycles
__global__ void globalMemAccess(float* in, float* out, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        out[idx] = in[idx] * 2.0f;  // Global → Register → Global
    }
}

// 2. Constant Memory
__constant__ float d_coeffs[4];  // Max 64KB

__global__ void constantMemAccess(float* in, float* out, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        out[idx] = in[idx] * d_coeffs[0] + d_coeffs[1];
    }
}

// 3. Shared Memory
// - Shared within block(threads) -> 4 cycle
// - Max: 48KB
__global__ void sharedMemAccess(float* in, float* out, int n) {
    // Block 당 Shared Memory 선언
    __shared__ float s_data[256];

    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int tid = threadIdx.x;

    if (idx < n) {
        s_data[tid] = in[idx];
    }
    __syncthreads();  // wait all threads to end between block

    if (idx < n) {
        // Avg
        float left = (tid > 0) ? s_data[tid - 1] : s_data[tid];
        float right = (tid < blockDim.x - 1) ? s_data[tid + 1] : s_data[tid];
        out[idx] = (left + s_data[tid] + right) / 3.0f;
    }
}

// 4. Register 
// - Very Fast for threads, compiler manages automatically
// - all localvariables are stored in register
__global__ void registerAccess(float* in, float* out, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= n) return;

    float val = in[idx]; // register
    float tmp = val * val;
    float result = tmp + val;
    out[idx] = result;
}

__global__ void coalescedAccess(float* in, float* out, int n) {
    int idx = blockIdx.x + blockDim.x + threadIdx.x;
    if (idx >= n) return;
    out[idx] = in[idx]; // Thread 0→[0], 1→[1], 2→[2] ... Coalesced
}

__global__ void stridedAccess(float* in, float* out, int n, int stride) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int src = idx * stride;
    if (src < n) {
        out[idx] = in[src]; // Thread 0→[0], 1→[stride], 2→[2*stride] ... Strided
    }
}

float timeKernel(cudaEvent_t start, cudaEvent_t stop) {
    float ms;
    cudaEventElapsedTime(&ms, start, stop);
    return ms;
}

int main() {
    const int N = 1 << 20;  // 1M elements
    const int SIZE = N * sizeof(float);

    float* h_in = (float*)malloc(SIZE);
    float* h_out = (float*)malloc(SIZE);
    for (int i = 0; i < N; i++) h_in[i] = (float)i;

    float* d_in, * d_out;
    cudaMalloc(&d_in, SIZE);
    cudaMalloc(&d_out, SIZE);
    cudaMemcpy(d_in, h_in, SIZE, cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (N + threads - 1) / threads;

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // 1. Global Memory
    printf("=== 1. Global Memory ===\n");
    cudaEventRecord(start);
    globalMemAccess << <blocks, threads >> > (d_in, d_out, N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    printf("  Time: %.3f ms\n", timeKernel(start, stop));
    cudaMemcpy(h_out, d_out, 4 * sizeof(float), cudaMemcpyDeviceToHost);
    printf("  out[0..3] = %.0f %.0f %.0f %.0f\n",
        h_out[0], h_out[1], h_out[2], h_out[3]);

    // 2. Constant Memory
    printf("\n=== 2. Constant Memory ===\n");
    float coeffs[4] = { 2.0f, 1.0f, 0.0f, 0.0f };
    cudaMemcpyToSymbol(d_coeffs, coeffs, sizeof(coeffs));
    cudaEventRecord(start);
    constantMemAccess << <blocks, threads >> > (d_in, d_out, N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    printf("  Time: %.3f ms\n", timeKernel(start, stop));
    cudaMemcpy(h_out, d_out, 4 * sizeof(float), cudaMemcpyDeviceToHost);
    printf("  out[0..3] = %.0f %.0f %.0f %.0f  (in*2 + 1)\n",
        h_out[0], h_out[1], h_out[2], h_out[3]);

    // 3. Shared Memory
    printf("\n=== 3. Shared Memory (smoothing) ===\n");
    cudaEventRecord(start);
    sharedMemAccess << <blocks, threads >> > (d_in, d_out, N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    printf("  Time: %.3f ms\n", timeKernel(start, stop));
    cudaMemcpy(h_out, d_out, 4 * sizeof(float), cudaMemcpyDeviceToHost);
    printf("  out[0..3] = %.2f %.2f %.2f %.2f  (3-point avg)\n",
        h_out[0], h_out[1], h_out[2], h_out[3]);

    // 4. Register 
    printf("\n=== 4. Register (val^2 + val) ===\n");
    cudaEventRecord(start);
    registerAccess << <blocks, threads >> > (d_in, d_out, N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    printf("  Time: %.3f ms\n", timeKernel(start, stop));
    cudaMemcpy(h_out, d_out, 4 * sizeof(float), cudaMemcpyDeviceToHost);
    printf("  out[0..3] = %.0f %.0f %.0f %.0f\n",
        h_out[0], h_out[1], h_out[2], h_out[3]);

    // 5. coalescing memory access
    printf("\n=== 5. Memory Coalescing ===\n");
    cudaEventRecord(start);
    coalescedAccess << <blocks, threads >> > (d_in, d_out, N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float t_coalesced = timeKernel(start, stop);
    printf("  Coalesced:  %.3f ms\n", t_coalesced);


    cudaEventRecord(start);
    stridedAccess << <blocks / 4, threads >> > (d_in, d_out, N, 4);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float t_strided = timeKernel(start, stop);
    printf("  Strided(4): %.3f ms  (%.1fx slower)\n",
        t_strided, t_strided / t_coalesced);


    // Clean up
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaFree(d_in);
    cudaFree(d_out);
    free(h_in);
    free(h_out);
}