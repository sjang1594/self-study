#pragma once

// Swap Chain
// [���� ����]
// - ���� ���� ���� �ִ� ��Ȳ�� ����
// - � ���������� ��� ������� ������
// - GPU ������ ��� (����)
// - ����� �޾Ƽ� ȭ�鿡 �׷��ش�.

// [���� �����]�� ��� ����
// - � ����(buffer) �� �׷��� �ǳ��޶�� ��Ź�غ���
// - Ư�� ���̸� ���� -> ó���� �ǳ��ְ� -> ������� �ش� ���̿� �޴´� OK
// - �츮 ȭ�鿡 Ư�� ����(���� �����) ��� ���ش�.

// [?]
// - �׷��� ȭ�鿡 ���� ����� ����ϴ� ���߿�, ���� ȭ�鵵 ���ָ� �ðܾ���
// - ���� ȭ�� ������� �̹� ȭ�� ��¿� �����
// - Ư�� ���̸� 2�� ����, �ϳ��� ���� ȭ���� �׷��ְ�, �ϳ��� ���� �ñ��
// - Double Buffering

// [1] [2]
// ���� ȭ�� [1] <-> GPU �۾��� [2] BackBuffer
// ���� ȭ�� [2] <-> GPU �۾��� [1] BackBuffer

class SwapChain
{
public:
	void Init(const WindowInfo& info, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);
	void Present();
	void SwapIndex();

	ComPtr<IDXGISwapChain> GetSwapChain() { return _swapChain; }
	ComPtr<ID3D12Resource> GetRenderTarget(int32 index) { return _renderTargets[index]; }

	uint32 GetCurrentBackBufferIndex() { return _backBufferIndex; }
	ComPtr<ID3D12Resource> GetCurrentBackBufferResource() { return _renderTargets[_backBufferIndex]; }

private:
	ComPtr<IDXGISwapChain>	_swapChain;
	ComPtr<ID3D12Resource>	_renderTargets[SWAP_CHAIN_BUFFER_COUNT];
	uint32					_backBufferIndex = 0; // ���� backBuffer [0] <-> [1]
};

