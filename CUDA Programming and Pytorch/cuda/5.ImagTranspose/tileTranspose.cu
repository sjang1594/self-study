#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <assert.h>
#include <string>

static constexpr int TILE_DIM = 32; // tile = 32 x 32
static constexpr int THREAD_ROWS = 8; // block = 32 x 8 = 256 threads (# of thread in Y direction)

__global__ void copyKernel(const float* __restrict__ in, float* __restrict__ out, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < N)
        out[idx] = in[idx]; // copy kernel 
}

__global__ void tileTransposeNoPad(const float* __restrict__ in, float* __restrict__ out, int M, int N) {
    __shared__ float s[TILE_DIM][TILE_DIM]; // no padding 

    int row = blockIdx.y * TILE_DIM + threadIdx.y;
    int col = blockIdx.x * TILE_DIM + threadIdx.x;

    // Global -> Shared Memory Copy (not transposed)
    for (int i = 0; i < TILE_DIM; i += THREAD_ROWS) {
        if (col < N && (row + i) < M) {
            s[threadIdx.y + i][threadIdx.x] = in[(row + i) * N + col];
        }
    }
    __syncthreads();

    // transpose (coalesced write)
    row = blockIdx.y * TILE_DIM + threadIdx.x;
    col = blockIdx.x * TILE_DIM + threadIdx.y;

    for (int i = 0; i < TILE_DIM; i += THREAD_ROWS) {
        if (row < M && (col + i) < N) {
            out[(col + i) * M + row] = s[threadIdx.x][threadIdx.y + i];
        }
    }
}

__global__ void tileTranspose(const float* __restrict__ in, float* __restrict__ out, int M, int N) {
    __shared__ float s[TILE_DIM][TILE_DIM + 1];

    int row = blockIdx.y * TILE_DIM + threadIdx.y;
    int col = blockIdx.x * TILE_DIM + threadIdx.x;

    // Global -> Shared Memory Copy (not transposed)
    for (int i = 0; i < TILE_DIM; i += THREAD_ROWS) {
        if (col < N && (row + i) < M) {
            s[threadIdx.y + i][threadIdx.x] = in[(row + i) * N + col];
        }
    }

    __syncthreads();

    // transpose (coalesced write)
    row = blockIdx.y * TILE_DIM + threadIdx.x;
    col = blockIdx.x * TILE_DIM + threadIdx.y;

    for (int i = 0; i < TILE_DIM; i += THREAD_ROWS) {
        if (row < M && (col + i) < N) {
            out[(col + i) * M + row] = s[threadIdx.x][threadIdx.y + i];
        }
    }
}

void transposeCPU(const float* in, float* out, const int& M, const int& N)
{
    for (int r = 0; r < M; r++) {
        for (int c = 0; c < N; c++) {
            out[c * M + r] = in[r * N + c];
        }
    }
}

bool verify(const float* ref, const float* gpu, const int& n)
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
    const int M = 4096; // 32 x 128
    const int N = 4096; // 32 x 128
    const int num_elements = M * N;

    const size_t bytes = (size_t)M * N * sizeof(float);

    float* h_in = (float*)malloc(bytes);
    float* h_out = (float*)malloc(bytes);
    float* h_ref = (float*)malloc(bytes);
    assert(h_in && h_out && h_ref);

    for (int i = 0; i < M * N; i++)
        h_in[i] = (float)i * 0.001f;

    transposeCPU(h_in, h_ref, M, N);    
    float* d_in, * d_out;
    cudaMalloc(&d_in, bytes);
    cudaMalloc(&d_out, bytes);
    cudaMemcpy(d_in, h_in, bytes, cudaMemcpyHostToDevice);

    dim3 blockDim(TILE_DIM, THREAD_ROWS);
    dim3 gridDim((N + TILE_DIM - 1) / TILE_DIM, (M + TILE_DIM - 1) / TILE_DIM); // GRID DIM = 4128 / 32 x 4128 / 32 (128=#ofblocks in x and y)

    const int REPS = 100;
    cudaEvent_t start, stop;

    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    dim3 copyBlock(256);
    dim3 copyGrid((M * N + 255) / 256);
    cudaEventRecord(start);
    for (int i = 0; i < REPS; i++)
        copyKernel << <copyGrid, copyBlock >> > (d_in, d_out, M * N);
    
    cudaEventRecord(stop); 
    cudaEventSynchronize(stop);
    float ms_copy; 
    cudaEventElapsedTime(&ms_copy, start, stop); ms_copy /= REPS;
    double bw_copy = 2.0 * bytes / (ms_copy * 1e-3) / 1e9;


    // tile transpose no pad
    cudaEventRecord(start);
    for (int i = 0; i < REPS; i++) {
        tileTransposeNoPad << <gridDim, blockDim >> > (d_in, d_out, M, N);
    }
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float ms_no_pad;
    cudaEventElapsedTime(&ms_no_pad, start, stop);
    ms_no_pad /= REPS;
    double bw_no_pad = 2.0 * bytes / (ms_no_pad * 1e-3) / 1e9; // GB
    cudaMemcpy(h_out, d_out, bytes, cudaMemcpyDeviceToHost);
    bool ok_nopad = verify(h_ref, h_out, M * N);

    // tile transpose w pad
    cudaEventRecord(start);
    for (int i = 0; i < REPS; i++) {
        tileTranspose << <gridDim, blockDim >> > (d_in, d_out, M, N);
    }
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    
    float ms_w_pad;
    cudaEventElapsedTime(&ms_w_pad, start, stop);
    ms_w_pad /= REPS;
    double bw_w_pad = 2.0 * bytes / (ms_w_pad * 1e-3) / 1e9;
    cudaMemcpy(h_out, d_out, bytes, cudaMemcpyDeviceToHost);
    bool ok_w_pad = verify(h_ref, h_out, M * N);

    printf("=== Tiled Transpose Benchmark (M=%d, N=%d, TILE=%d) ===\n\n", M, N, TILE_DIM);
    printf("  %-25s  %8s  %10s  %7s  %s\n", "Kernel", "ms", "GB/s", "vs Copy", "Status");
    printf("  %s\n", std::string(65, '-').c_str());
    printf("  %-25s  %8.3f  %10.1f  %6s  (reference)\n",
        "Copy (peak BW ref)", ms_copy, bw_copy, "-");
    printf("  %-25s  %8.3f  %10.1f  %6.0f%%  %s\n",
        "Tiled NoPad (V1)", ms_no_pad, bw_no_pad,
        bw_no_pad / bw_copy * 100.0, ok_nopad ? "PASS" : "FAIL");
    printf("  %-25s  %8.3f  %10.1f  %6.0f%%  %s\n",
        "Tiled +1 Pad (V2)", ms_w_pad, bw_w_pad,
        bw_w_pad / bw_copy * 100.0, ok_w_pad ? "PASS" : "FAIL");

    printf("\n=== Bank Conflict Analysis ===\n");
    printf("  tile[TILE][TILE]   : bank(i) = (tx * 32 + ty) %% 32 = ty\n");
    printf("    => all 32 threads => same bank => 32-way conflict\n");
    printf("  tile[TILE][TILE+1] : bank(i) = (tx * 33 + ty) %% 32 = (tx + ty) %% 32\n");
    printf("    => 32 threads => banks 0..31 => 0 conflicts\n");
    printf("  Padding cost: %zu bytes/block (negligible)\n", TILE_DIM * 1 * sizeof(float));
        
    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    cudaFree(d_in);
    cudaFree(d_out);
    free(h_in);
    free(h_out);
    free(h_ref);
    return 0;
}