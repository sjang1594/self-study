#include "pch.h"
#include "Device.h"

void Device::Init()
{
	// D3D12 Debug Layer Activate
	// - VC++ Detailed Debugging Log will be outputted
	// - riid : COM ID of Device
	// - ppDevice : Setting the parameter from the created device
#ifdef _DEBUG
	::D3D12GetDebugInterface(IID_PPV_ARGS(&_debugController));
	_debugController->EnableDebugLayer();
#endif

	// DXGI(DirectX Graphics Infrastructure)
	// Direct3D APIs
	// - ��ü ȭ�� ��� ��ȯ
	// - �����Ǵ� ���÷��� ��� ���� ��
	// CreateDXGIFactory
	// - riid : COM ID of Device
	// - ppDevice : Setting the parameter from the created device
	::CreateDXGIFactory(IID_PPV_ARGS(&_dxgi));

	// CreateDevice
	// - Display Adaptor(Graphic Card)�� ���³��� Object
	// - pAdapter : nullptr �����ϸ� System Default Display Adapter
	// - MinimumFeatureLevel : ���� ���α׷��� �䱸�ϴ� �ּ� ��� ���� (���ڴٸ��� �ɷ�����)
	// - riid : COM ID of Device
	// - ppDevice : Setting the parameter from the created device
	::D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&_device));
}