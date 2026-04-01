import torch

def print_sep(title:str) -> None:
    print(f"\n{'='*55}")
    print(f"  {title}")
    print(f"{'='*55}")

def tensor_basics() -> None:
    print_sep("1. dtype / device / shape")
    t = torch.randn(2, 3, 4, 5, device="cpu", dtype=torch.float32)
    print(f"dtype  : {t.dtype}")
    print(f"device : {t.device}")
    print(f"shape  : {t.shape}")
    print(f"numel  : {t.numel()}")

    print_sep("2. stride() — the key to memory layout")
    print(f"shape  : {list(t.shape)}")
    print(f"stride : {t.stride()}")
    print(f"element [n][c][h][w] is at offset: n*{t.stride(0)} + c*{t.stride(1)} + h*{t.stride(2)} + w*{t.stride(3)}")

    print_sep("3. NCHW vs NHWC — same data, different access pattern")
    nchw = torch.rand(1, 3, 8, 8) # N = 1, C = 3, H = 8, W = 8
    print(f"NCHW shape  : {list(nchw.shape)}")
    print(f"NCHW stride  : {nchw.stride()}")
    print(f"pixel [n=0][c=1][h=2][w=3] at offset: {0*nchw.stride(0) + 1*nchw.stride(1) + 2*nchw.stride(2) + 3*nchw.stride(3)}")

    nhcw = nchw.permute(0, 2, 3, 1) # 1, 8, 8, 3 N x H x W x C
    print(f"NHCW shape  : {list(nhcw.shape)}")
    print(f"NHCW stride  : {nhcw.stride()}")
    print(f"Before contiguous copy  {nhcw.is_contiguous()}")
    nhwc_c = nchw.contiguous() # Memory rearrangement
    print(f"After continugous copy {nhwc_c.is_contiguous()}")
    print(f"pixel [n=0][h=2][w=3][c=1] at offset: {0*nhwc_c.stride(0) + 2*nhwc_c.stride(1) + 3*nhwc_c.stride(2) + 1*nhwc_c.stride(3)}")


    print(f"\n  Key difference for CUDA kernels:")
    print(f"NCHW (stride={list(nchw.stride())}): 마지막 차원 W가 stride=1 → 스레드가 W 방향으로 읽으면 coalesced")
    print(f"반면 C 방향은 stride=H*W={8*8} → 멀리 뛰어야 해서 non-coalesced")
    print(f"NHWC (stride={list(nhwc_c.stride())}): 마지막 차원 C가 stride=1 → 스레드가 C 방향으로 읽으면 coalesced")
    print(f"반면 W 방향은 stride=C=3 → non-coalesced")
    print(f"어느 차원을 병렬로 처리하느냐에 따라 유리한 레이아웃이 다름")

    print_sep("4. contiguous() — when CUDA kernels need it")
    t_nc = nchw.permute(0, 2, 3, 1)
    print(f"is_contiguous (after permute) : {t_nc.is_contiguous()}")
    print(f"stride                        : {t_nc.stride()}")
    t_c = t_nc.contiguous()
    print(f"is_contiguous (after .contiguous()) : {t_c.is_contiguous()}")
    print(f"stride                              : {t_c.stride()}")
    print(f"Non-contiguous tensor passed to a raw CUDA kernel = wrong results")

    print_sep("5. data_ptr() — passing to CUDA kernel")
    if torch.cuda.is_available():
        t_gpu = torch.randn(4, 4, device="cuda")
        ptr = t_gpu.data_ptr()
        print(f"GPU tensor data_ptr: 0x{ptr:016x}")
        print(f"Cast to float* in CUDA C++: (float*)tensor.data_ptr()")
    else:
        print("(CUDA not available — skipping GPU demo)")

if __name__ == "__main__":
    tensor_basics()