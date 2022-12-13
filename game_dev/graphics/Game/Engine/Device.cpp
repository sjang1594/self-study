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
	// - 전체 화면 모드 전환
	// - 지원되는 디스플레이 모드 열거 등
	// CreateDXGIFactory
	// - riid : COM ID of Device
	// - ppDevice : Setting the parameter from the created device
	::CreateDXGIFactory(IID_PPV_ARGS(&_dxgi));

	// CreateDevice
	// - Display Adaptor(Graphic Card)를 나태내는 Object
	// - pAdapter : nullptr 지정하면 System Default Display Adapter
	// - MinimumFeatureLevel : 응용 프로그램이 요구하는 최소 기능 수준 (구닥다리는 걸러낸다)
	// - riid : COM ID of Device
	// - ppDevice : Setting the parameter from the created device
	::D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&_device));
}