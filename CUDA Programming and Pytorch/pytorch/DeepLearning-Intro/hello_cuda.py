import torch
import time

device = torch.device("cuda")

# 1. Tensor Create & Device Management
print(" 1. Tensor & Device ")

a_cpu = torch.randn(1024, 1024)
a_gpu = a_cpu.to(device)
print(f"  CPU tensor: {a_cpu.device}, shape={a_cpu.shape}")
print(f"  GPU tensor: {a_gpu.device}, shape={a_gpu.shape}")

# Faster
b_gpu = torch.randn(1024, 1024, device=device)
print(f" Direct GPU: {b_gpu.device}")

fp16 = torch.randn(4, 4, device=device, dtype=torch.float16)
fp32 = torch.randn(4, 4, device=device, dtype=torch.float32)
print(f"  FP16 size: {fp16.element_size()} bytes/elem")
print(f"  FP32 size: {fp32.element_size()} bytes/elem")

# 2. GPU Memory Management
print("\n 2. GPU Memory Management ")

def mem_mb():
    return torch.cuda.memory_allocated() / 1024**2

print(f"  Before alloc : {mem_mb():.1f} MB")
big = torch.randn(1024, 1024, 64, device=device)  # ~256MB
print(f"  After  alloc : {mem_mb():.1f} MB")
del big
torch.cuda.empty_cache()
print(f"  After  delete: {mem_mb():.1f} MB")

total = torch.cuda.get_device_properties(0).total_memory / 1024**3
print(f"Total VRAM   : {total:.1f} GB")

# 3. CPU vs GPU Speed
print("\n 3. CPU vs GPU Speed ")

N = 4096
a = torch.randn(N, N)
b = torch.randn(N, N)

# CPU
t0 = time.perf_counter()
for _ in range(5):
    c = torch.matmul(a, b)
t_cpu = (time.perf_counter() - t0) / 5 * 1000
print(f"  CPU matmul ({N}x{N}): {t_cpu:.1f} ms")

# GPU (included data transfer time)
a_g = a.to(device)
b_g = b.to(device)
for _ in range(3):
    _ = torch.matmul(a_g, b_g)
torch.cuda.synchronize()

start = torch.cuda.Event(enable_timing=True)
end   = torch.cuda.Event(enable_timing=True)
start.record()
for _ in range(5):
    c_g = torch.matmul(a_g, b_g)
end.record()
torch.cuda.synchronize()
t_gpu = start.elapsed_time(end) / 5
print(f"  GPU matmul ({N}x{N}): {t_gpu:.3f} ms  ({t_cpu/t_gpu:.0f}x faster)")

# 4. CUDA Stream - Sync vs Async Execution
print("\n 4. CUDA Streams ")

stream1 = torch.cuda.Stream()
stream2 = torch.cuda.Stream()

x = torch.randn(2048, 2048, device=device)
y = torch.randn(2048, 2048, device=device)

# sync
torch.cuda.synchronize()
t0 = time.perf_counter()
r1 = torch.matmul(x, x)
r2 = torch.matmul(y, y)
torch.cuda.synchronize()
t_sync = (time.perf_counter() - t0) * 1000
print(f"  Sequential : {t_sync:.2f} ms")

# async
torch.cuda.synchronize()
t0 = time.perf_counter()
with torch.cuda.stream(stream1):
    r1 = torch.matmul(x, x)
with torch.cuda.stream(stream2):
    r2 = torch.matmul(y, y)
torch.cuda.synchronize()
t_async = (time.perf_counter() - t0) * 1000
print(f"  Parallel   : {t_async:.2f} ms  ({t_sync/t_async:.2f}x)")

# 5. CUDA Event Timing
print("\n 5. CUDA Event Timing ")

def benchmark(fn, runs=20):
    # warmup
    for _ in range(3): fn()
    torch.cuda.synchronize()

    s = torch.cuda.Event(enable_timing=True)
    e = torch.cuda.Event(enable_timing=True)
    s.record()
    for _ in range(runs): fn()
    e.record()
    torch.cuda.synchronize()
    return s.elapsed_time(e) / runs

t = benchmark(lambda: torch.matmul(a_g, b_g))
gflops = 2 * N**3 / (t * 1e6)
print(f"  matmul {N}x{N}: {t:.3f} ms  |  {gflops:.1f} GFLOPS")

t = benchmark(lambda: torch.relu(a_g))
print(f"  relu   {N}x{N}: {t:.3f} ms")

t = benchmark(lambda: a_g + b_g)
print(f"  add    {N}x{N}: {t:.3f} ms")

# 6. FP16 (Half Precision)
print("\n 6. FP32 vs FP16 (Tensor Core) ")

a_fp32 = torch.randn(N, N, device=device, dtype=torch.float32)
b_fp32 = torch.randn(N, N, device=device, dtype=torch.float32)
a_fp16 = a_fp32.half()
b_fp16 = b_fp32.half()

t_fp32 = benchmark(lambda: torch.matmul(a_fp32, b_fp32))
t_fp16 = benchmark(lambda: torch.matmul(a_fp16, b_fp16))

print(f"  FP32: {t_fp32:.3f} ms  |  {2*N**3/(t_fp32*1e6):.1f} GFLOPS")
print(f"  FP16: {t_fp16:.3f} ms  |  {2*N**3/(t_fp16*1e6):.1f} GFLOPS  ({t_fp32/t_fp16:.1f}x)")