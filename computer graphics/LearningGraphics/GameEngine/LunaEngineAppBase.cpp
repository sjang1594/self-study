#include "LunaEngineAppBase.h"

#include <dxgi.h>    // DXGIFactory
#include <dxgi1_4.h> // DXGIFactory4

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
                                                             UINT msg,
                                                             WPARAM wParam,
                                                             LPARAM lParam);

namespace LunaEngine {

LunaEngineAppBase *g_LunaEngineBase = nullptr;

LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    return g_LunaEngineBase->MsgProc(hwnd, msg, wParam, lParam);
}

LunaEngineAppBase::LunaEngineAppBase()
    : m_screenWidth(1280), m_screenHeight(960), m_mainWindow(0),
      m_screenViewport(D3D11_VIEWPORT()) {
    g_LunaEngineBase = this;
}

LunaEngineAppBase::~LunaEngineAppBase() { Release(); }

bool LunaEngineAppBase::Initialize() {
    if (!InitMainWindow())
        return false;
    if (!InitDirect3DX())
        return false;
    if (!InitGUI())
        return false;
    return true;
}

void LunaEngineAppBase::Release() {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    DestroyWindow(m_mainWindow);
}

int LunaEngineAppBase::Run() {
    MSG msg = {0};
    while (WM_QUIT != msg.message) {

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            // Start the Frame
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();

            // Register what you want to render
            ImGui::NewFrame();
            ImGui::Begin("Scene Control");

            // Frame Rate
            ImGui::Text("Average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);

            UpdateGUI();
            ImGui::End();
            ImGui::Render(); // End Render

            // Update the delta time
            Update(ImGui::GetIO().DeltaTime);

            // My Randerer
            Render();

            // GUI Rendering
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            // swtich the back buffer and the front buffer
            m_swapChain->Present(1, 0);
        }
    }
    return 0;
}

float LunaEngineAppBase::GetAspectRatio() const { return float(m_screenWidth) / m_screenHeight; }

LRESULT LunaEngineAppBase::MsgProc(HWND hwnd, UINT msg, WPARAM wParam,
                                   LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
        return true;

    switch (msg) {
    case WM_SIZE:
        // Reset and resize swapchain
        break;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_MOUSEMOVE:
        // cout << "Mouse " << LOWORD(lParam) << " " << HIWORD(lParam) << endl;
        break;
    case WM_LBUTTONUP:
        // cout << "WM_LBUTTONUP Left mouse button" << endl;
        break;
    case WM_RBUTTONUP:
        // cout << "WM_RBUTTONUP Right mouse button" << endl;
        break;
    case WM_KEYDOWN:
        // cout << "WM_KEYDOWN " << (int)wParam << endl;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }

    return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

bool LunaEngineAppBase::InitMainWindow() {
    // Struct
    WNDCLASSEX wc = {sizeof(WNDCLASSEX),
                     CS_CLASSDC,
                     WndProc,
                     0L,
                     0L,
                     GetModuleHandle(NULL),
                     NULL,
                     NULL,
                     NULL,
                     NULL,
                     L"Luna Engine", // lpszClassName, L-string
                     NULL};

    // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassa?redirectedfrom=MSDN
    if (!RegisterClassEx(&wc)) {
        return false;
    }

    RECT wr = {0, 0, m_screenWidth, m_screenHeight};
    // update wr by the "AdjustWindowRect"
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);

    m_mainWindow =
        CreateWindow(wc.lpszClassName, L"Luna Engine", WS_OVERLAPPEDWINDOW,
                     100,                // x coordinate in window on far right.
                     100,                // y coordinate in window on far right
                     wr.right - wr.left, // Window Horizontal Resolution
                     wr.bottom - wr.top, // Window Vertical Resolution
                     NULL, NULL, wc.hInstance, NULL);

    if (!m_mainWindow)
        return false;

    ShowWindow(m_mainWindow, SW_SHOWDEFAULT);
    UpdateWindow(m_mainWindow);
    return true;
}

bool LunaEngineAppBase::InitDirect3DX() {

    // 이 예제는 Intel 내장 그래픽스 칩으로 실행을 확인하였습니다.
    // (LG 그램, 17Z90n, Intel Iris Plus Graphics)
    // 만약 그래픽스 카드 호환성 문제로 D3D11CreateDevice()가 실패하는 경우에는
    // D3D_DRIVER_TYPE_HARDWARE 대신 D3D_DRIVER_TYPE_WARP 사용해보세요
    // const D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_WARP;
    const D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;

    // 여기서 생성하는 것들
    // m_device, m_context, m_swapChain,
    // m_renderTargetView, m_screenViewport, m_rasterizerSate
    // m_device와 m_context 생성

    UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;

    const D3D_FEATURE_LEVEL featureLevels[2] = {
        D3D_FEATURE_LEVEL_11_0, // 더 높은 버전이 먼저 오도록 설정
        D3D_FEATURE_LEVEL_9_3};
    D3D_FEATURE_LEVEL featureLevel;

    if (FAILED(D3D11CreateDevice(
            nullptr,    // Specify nullptr to use the default adapter.
            driverType, // Create a device using the hardware graphics driver.
            0, // Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
            createDeviceFlags, // Set debug and Direct2D compatibility flags.
            featureLevels,     // List of feature levels this app can support.
            ARRAYSIZE(featureLevels), // Size of the list above.
            D3D11_SDK_VERSION, // Always set this to D3D11_SDK_VERSION for
                               // Microsoft Store apps.
            &device,           // Returns the Direct3D device created.
            &featureLevel,     // Returns feature level of device created.
            &context           // Returns the device immediate context.
            ))) {
        std::cout << "D3D11CreateDevice() failed." << std::endl;
        return false;
    }

    if (featureLevel != D3D_FEATURE_LEVEL_11_0) {
        std::cout << "D3D Feature Level 11 unsupported." << std::endl;
        return false;
    }

    // 참고: Immediate vs deferred context
    // A deferred context is primarily used for multithreading and is not
    // necessary for a single-threaded application.
    // https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-devices-intro#deferred-context

    // Check MSAA 
    UINT numQualityLevels;
    device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4,
                                          &numQualityLevels);
    if (numQualityLevels <= 0) {
        std::cout << "MSAA not supported." << std::endl;
    }

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferDesc.Width = m_screenWidth;   // set the back buffer width
    sd.BufferDesc.Height = m_screenHeight; // set the back buffer height
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // use 32-bit color (8 *
                                                       // 4 bits) / Data Format
    sd.BufferCount = 2;                                // Double-buffering
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage =
        DXGI_USAGE_RENDER_TARGET_OUTPUT; // how swap chain is to be used
    sd.OutputWindow = m_mainWindow;      // the window to be used
    sd.Windowed = TRUE;                  // windowed/full-screen mode
    sd.Flags =
        DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // allow full-screen switching
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    if (numQualityLevels > 0) {
        sd.SampleDesc.Count = 4; // how many multisamples
        sd.SampleDesc.Quality = numQualityLevels - 1;
    } else {
        sd.SampleDesc.Count = 1; // how many multisamples
        sd.SampleDesc.Quality = 0;
    }

    if (FAILED(device.As(&m_device))) {
        std::cout << "device.AS() failed." << std::endl;
        return false;
    }

    if (FAILED(context.As(&m_context))) {
        std::cout << "context.As() failed." << std::endl;
        return false;
    }

    if (FAILED(D3D11CreateDeviceAndSwapChain(
            0, // Default adapter
            driverType,
            0, // No software device
            createDeviceFlags, featureLevels, 1, D3D11_SDK_VERSION, &sd,
            &m_swapChain, &m_device, &featureLevel, &m_context))) {
        std::cout << "D3D11CreateDeviceAndSwapChain() failed." << std::endl;
        return false;
    }

    // CreateRenderTarget
    ID3D11Texture2D *pBackBuffer;
    m_swapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    if (pBackBuffer) {
        m_device->CreateRenderTargetView(pBackBuffer, NULL,
                                         &m_renderTargetView);
        pBackBuffer->Release();
    } else {
        std::cout << "CreateRenderTargetView() failed." << std::endl;
        return false;
    }

    // Set the viewport
    ZeroMemory(&m_screenViewport, sizeof(D3D11_VIEWPORT));
    m_screenViewport.TopLeftX = 0;
    m_screenViewport.TopLeftY = 0;
    m_screenViewport.Width = float(m_screenWidth);
    m_screenViewport.Height = float(m_screenHeight);
    // m_screenViewport.Width = static_cast<float>(m_screenHeight);
    m_screenViewport.MinDepth = 0.0f;
    m_screenViewport.MaxDepth = 1.0f; // Note: important for depth buffering

    m_context->RSSetViewports(1, &m_screenViewport);

    // Create a rasterizer state
    D3D11_RASTERIZER_DESC rastDesc;
    ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC)); // Need this
    rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    // rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
    rastDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    rastDesc.FrontCounterClockwise = false;

    m_device->CreateRasterizerState(&rastDesc, &m_rasterizerSate);

    // Create depth buffer

    D3D11_TEXTURE2D_DESC depthStencilBufferDesc;
    depthStencilBufferDesc.Width = m_screenWidth;
    depthStencilBufferDesc.Height = m_screenHeight;
    depthStencilBufferDesc.MipLevels = 1;
    depthStencilBufferDesc.ArraySize = 1;
    depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    if (numQualityLevels > 0) {
        depthStencilBufferDesc.SampleDesc.Count = 4; // how many multisamples
        depthStencilBufferDesc.SampleDesc.Quality = numQualityLevels - 1;
    } else {
        depthStencilBufferDesc.SampleDesc.Count = 1; // how many multisamples
        depthStencilBufferDesc.SampleDesc.Quality = 0;
    }
    depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilBufferDesc.CPUAccessFlags = 0;
    depthStencilBufferDesc.MiscFlags = 0;

    if (FAILED(m_device->CreateTexture2D(
            &depthStencilBufferDesc, 0, m_depthStencilBuffer.GetAddressOf()))) {
        std::cout << "CreateTexture2D() failed." << std::endl;
    }
    if (FAILED(m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), 0,
                                                &m_depthStencilView))) {
        std::cout << "CreateDepthStencilView() failed." << std::endl;
    }

    // Create depth stencil state

    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
    depthStencilDesc.DepthEnable = true; // false
    depthStencilDesc.DepthWriteMask =
        D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc =
        D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
    if (FAILED(m_device->CreateDepthStencilState(
            &depthStencilDesc, m_depthStencilState.GetAddressOf()))) {
        std::cout << "CreateDepthStencilState() failed." << std::endl;
    }

    return true;
}

bool LunaEngineAppBase::InitGUI() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.DisplaySize = ImVec2(float(m_screenWidth), float(m_screenHeight));
    ImGui::StyleColorsLight();

    // Set Platform / Renderer backends
    if (!ImGui_ImplDX11_Init(m_device.Get(), m_context.Get()))
        return false;
    if (!ImGui_ImplWin32_Init(m_mainWindow))
        return false;
    return true;
}

void LunaEngineAppBase::CreateVertexShaderAndInputLayout(
    const wstring &filename,
    const vector<D3D11_INPUT_ELEMENT_DESC> &inputElements,
    ComPtr<ID3D11VertexShader> &vertexShader,
    ComPtr<ID3D11InputLayout> &inputLayout) {

    ComPtr<ID3DBlob> shaderBlob;
    ComPtr<ID3DBlob> errorBlob;

    HRESULT hr = D3DCompileFromFile(filename.c_str(), 0, 0, "main", "vs_5_0", 0,
                                    0, &shaderBlob, &errorBlob);

    CheckResult(hr, errorBlob.Get());

    if (!shaderBlob)
        return;

    m_device->CreateVertexShader(shaderBlob->GetBufferPointer(),
                                 shaderBlob->GetBufferSize(), NULL,
                                 &vertexShader);

    m_device->CreateInputLayout(inputElements.data(),
                                UINT(inputElements.size()),
                                shaderBlob->GetBufferPointer(),
                                shaderBlob->GetBufferSize(), &inputLayout);
}

void LunaEngineAppBase::CreateIndexBuffer(const vector<uint16_t> &indices,
                                          ComPtr<ID3D11Buffer> &indexBuffer) {
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_IMMUTABLE; // do not change after init
    bufferDesc.ByteWidth = UINT(sizeof(uint16_t) * indices.size());
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0; // no cpu access
    bufferDesc.StructureByteStride = sizeof(uint16_t);

    D3D11_SUBRESOURCE_DATA indexBufferData = {0};
    indexBufferData.pSysMem = indices.data();
    indexBufferData.SysMemPitch = 0;
    indexBufferData.SysMemSlicePitch = 0;
    const HRESULT hr = m_device->CreateBuffer(&bufferDesc, &indexBufferData,
                                              indexBuffer.GetAddressOf());
    if (FAILED(hr)) {
        std::cout << "CreateIndexBuffer() failed" << std::hex << hr
                  << std::endl;
    }
}

void LunaEngineAppBase::CreatePixelShader(
    const wstring &filename, ComPtr<ID3D11PixelShader> &pixelShader) {
    
    // Temp Data Blob
    ComPtr<ID3DBlob> shaderBlob;
    ComPtr<ID3DBlob> errorBlob;

    HRESULT hr = D3DCompileFromFile(filename.c_str(), 0, 0, "main", "ps_5_0", 0,
                                    0, &shaderBlob, &errorBlob);
    CheckResult(hr, errorBlob.Get());
    m_device->CreatePixelShader(shaderBlob->GetBufferPointer(),
                                shaderBlob->GetBufferSize(), NULL,
                                &pixelShader);
}

void LunaEngineAppBase::ThrowIfFailed(HRESULT hr) {
    // TODO: Finish this implementation
    // #ifndef ThrowIfFailed
    // #define ThrowIfFailed(x)
    //     {
    //         HRESULT hr__ = (x);
    //         std::wstring wfn = AnsiToWString(__FILE__);
    //         if (FAILED(hr__)) {
    //             throw DxException(hr__, L#x, wfn, __LINE__);
    //         }
    //     }
    // #endif
}

void LunaEngineAppBase::CheckResult(HRESULT hr, ID3DBlob *errorBlob) {
    if (FAILED(hr)) {
        if ((hr & D3D11_ERROR_FILE_NOT_FOUND) != 0) {
            std::cout << "D3D11 File Not Found" << std::endl;
        }

        if (errorBlob) {
            std::cout << "Shader Compilation Error \n"
                      << (char *)errorBlob->GetBufferPointer() << std::endl;
        }
    }
}
} // namespace LunaEngine
