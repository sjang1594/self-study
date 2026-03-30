#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <cassert>
#include <string>

// read coalesced , write strided
__global__ void naiveTransposeGPU(const float* __restrict__ in, float* __restrict__ out, int M, int N)
{
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;

    if (row < M && col < N)
        out[col * M + row] = in[row * N + col]; // strided write 32 threads
}

// read coalesced
__global__ void copyKernel(const float* __restrict in, float* __restrict__ out, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < N)
        out[idx] = in[idx]; // copy kernel 
}

void transposeCPU(const float* in, float* out, const int& M, const int& N)
{
    for (int r = 0; r < M; r++) {
        for (int c = 0; c < N; c++) {
            out[c * M + r] = in[r * N + c];
        }
    }
}

bool verify(const float* ref, const float* gpu, int& n)
{
    for (int i = 0; i < n; i++) {
        if (fabsf(ref[i] - gpu[i]) > 1e-5f) {
            printf("  [FAIL] index %d: ref=%.6f  gpu=%.6f\n", i, ref[i], gpu[i]);
            return false;
        }
    }
    return true;
}

int main()
{
    // You can certainly load image

    const int M = 4096;
    const int N = 4096;
	int NUM_ELEMENTS = M * N;
    const size_t bytes = (size_t)M * N * sizeof(float);

    float* h_in = (float*)malloc(bytes);
    float* h_ref = (float*)malloc(bytes);
    float* h_gpu = (float*)malloc(bytes);
    assert(h_in && h_ref && h_gpu);

    for (int i = 0; i < M * N; i++) 
        h_in[i] = (float)i * 0.001f;

    transposeCPU(h_in, h_ref, M, N);

    float* d_in, * d_out;
    cudaMalloc(&d_in, bytes);
    cudaMalloc(&d_out, bytes);
    cudaMemcpy(d_in, h_in, bytes, cudaMemcpyHostToDevice);

    const float warpSize = 32;
    dim3 blockDim(warpSize, warpSize);
    dim3 gridDim((N + warpSize - 1) / warpSize, (M + warpSize - 1) / warpSize);

    const int REPS = 100;
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // COPY
    dim3 copyBlockDim(256);
    dim3 gridDim((N + warpSize - 1) / warpSize, (M + warpSize - 1) / warpSize);

    const int REPS = 100;
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // COPY
    dim3 copyBlockDim(256);
    dim3 copyGridDim((M * N + 255) / 256);
    cudaEventRecord(start);

    for (int i = 0;i < REPS; i++)
		copyKernel << <copyGridDim, copyBlockDim >> > (d_in, d_out, M * N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float ms_copy;
    cudaEventElapsedTime(&ms_copy, start, stop);
    ms_copy /= REPS;
    double bw_copy = 2.0 * bytes / (ms_copy * 1e-3) / 1e9;

    // Transpose
    cudaEventRecord(start);

    for (int i = 0; i < REPS; i++)
		naiveTransposeGPU << <gridDim, blockDim >> > (d_in, d_out, M, N);
    
	cudaEventRecord(stop);
	cudaEventSynchronize(stop);

    float ms_transpose;
    cudaEventElapsedTime(&ms_transpose, start, stop);
	ms_transpose /= REPS;
	double bw_transpose = 2.0 * bytes / (ms_transpose * 1e-3) / 1e9;

    cudaMemcpy(h_gpu, d_out, bytes, cudaMemcpyDeviceToHost);

    cudaMemcpy(h_gpu, d_out, bytes, cudaMemcpyDeviceToHost);

    printf("=== Image Transpose Benchmark (M=%d, N=%d) ===\n\n", M, N);
    printf("  Matrix size : %.1f MB\n", bytes / 1e6);
    printf("  Read + Write: %.1f MB total\n\n", 2.0 * bytes / 1e6);

    printf("  %-20s  %8s  %10s  %s\n", "Kernel", "ms", "GB/s", "vs Copy");
    printf("  %s\n", std::string(55, '-').c_str());
    printf("  %-20s  %8.3f  %10.1f  (baseline)\n", "Copy (peak ref)", ms_copy, bw_copy);
    printf("  %-20s  %8.3f  %10.1f  %.0f%%\n",
        "Naive Transpose", ms_transpose, bw_transpose, bw_transpose / bw_copy * 100.0);

    printf("\n  Status: %s\n", verify(h_ref, h_gpu, NUM_ELEMENTS) ? "PASS" : "FAIL");

    printf("\n=== Why Naive is slow ===\n");
    printf("  READ  in[row*N+col]   => coalesced (32 threads × consecutive cols)\n");
    printf("  WRITE out[col*M+row]  => STRIDED   (32 threads × M-apart addresses)\n");
    printf("  Strided write => cache lines evicted before reuse => DRAM write per element\n");
    printf("  Expected: Naive ≈ 40-60%% of Copy bandwidth\n");

    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    cudaFree(d_in);
    cudaFree(d_out);
    free(h_in);
    free(h_ref);
    free(h_gpu);
   
    return 0;
}