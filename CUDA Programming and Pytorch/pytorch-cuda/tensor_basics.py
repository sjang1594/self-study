import torch

def print_sep(title:str) -> None:
    print(f"\n{'='*55}")
    print(f"{title}")
    print(f"{'='*55}")

def tensor_basics() -> None:
    print_sep("1. dtype / device / shape")
    a = torch.randn(2, 3, 4, device="cpu", dtype=torch.float32)
    print(a)

    print(f"dtype : {a.dtype}")
    print(f"device: {a.device}")
    print(f"shape : {a.shape}")
    print(f"numel : {a.numel()}") # number of element


    

if __name__ == "__main__":
    tensor_basics()