#pragma once

#include <d3d11.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <wrl.h> // ComPtr

namespace LunaEngine {
using Microsoft::WRL::ComPtr;
using std::vector;
using std::wstring;

class LunaEngineAppBase {
  public:
    LunaEngineAppBase();
    virtual ~LunaEngineAppBase();
    virtual bool Initialize();
    virtual void Update(float dt) = 0;
    virtual void UpdateGUI() = 0;
    virtual void Render() = 0;
    void Release();
    int Run();
    float GetAspectRatio() const;

    virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    virtual void OnMouseDown(WPARAM btnState, int x, int y){};
    virtual void OnMouseUp(WPARAM btnState, int x, int y){};
    virtual void OnMouseMove(WPARAM btnState, int x, int y){};

  protected:
    bool InitMainWindow();
    bool InitDirect3DX();
    bool InitGUI();
    void CreateVertexShaderAndInputLayout(
        const wstring &filename,
        const vector<D3D11_INPUT_ELEMENT_DESC> &inputElements,
        ComPtr<ID3D11VertexShader> &vertexShader,
        ComPtr<ID3D11InputLayout> &inputLayout);

    void CreatePixelShader(const wstring &filename,
                           ComPtr<ID3D11PixelShader> &pixelShader);

    void CreateIndexBuffer(const vector<uint16_t> &indices,
                           ComPtr<ID3D11Buffer> &indexBuffer);

    template <typename VertexT>
    void CreateVertexBuffer(const vector<VertexT> &vertices,
                            ComPtr<ID3D11Buffer> &vertexBuffer) {
        // D3D11_USAGE enumeration (d3d11.h)
        // https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_usage
        D3D11_BUFFER_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(bufferDesc));
        bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
        bufferDesc.ByteWidth = UINT(sizeof(VertexT) * vertices.size());
        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bufferDesc.CPUAccessFlags = 0; // no cpu access
        bufferDesc.StructureByteStride =
            sizeof(VertexT); // it's like walking some bytes (strides)

        D3D11_SUBRESOURCE_DATA vertexBufferData = {0}; // init
        vertexBufferData.pSysMem = vertices.data();
        vertexBufferData.SysMemPitch = 0;
        vertexBufferData.SysMemSlicePitch = 0;

        const HRESULT hr = m_device->CreateBuffer(
            &bufferDesc, &vertexBufferData, vertexBuffer.GetAddressOf());
        if (FAILED(hr)) {
            std::cout << "CreateVertexBuffer() failed" << std::hex << hr
                      << std::endl;
        }
    }

    template <typename ConstantT>
    void CreateConstantBuffer(const ConstantT &constantBufferData,
                              ComPtr<ID3D11Buffer> &constantBuffer) {

        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        bufferDesc.ByteWidth = sizeof(constantBufferData);
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        bufferDesc.MiscFlags = 0;
        bufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA constantBufferResource;
        constantBufferResource.pSysMem = &constantBufferData;
        constantBufferResource.SysMemPitch = 0;
        constantBufferResource.SysMemSlicePitch = 0;

        const HRESULT hr =
            m_device->CreateBuffer(&bufferDesc, &constantBufferResource,
                                   constantBuffer.GetAddressOf());
        if (FAILED(hr)) {
            std::cout << "CreateIndexBuffer() failed" << std::hex << hr
                      << std::endl;
        }
    }

    template <typename DataT>
    void UpdateBuffer(const DataT &bufferData, ComPtr<ID3D11Buffer> buffer) {
        D3D11_MAPPED_SUBRESOURCE mapResource;
        m_context->Map(buffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL,
                       &mapResource);
        memcpy(mapResource.pData, &bufferData, sizeof(bufferData));
        m_context->Unmap(buffer.Get(), NULL);
    }

    void ThrowIfFailed(HRESULT hr);

    D3D11_VIEWPORT GetScreenViewport() const { return m_screenViewport; }
    ComPtr<ID3D11DeviceContext> GetContext() const { return m_context; }
    ComPtr<ID3D11DepthStencilView> GetDepthStencilView() const {
        return m_depthStencilView;
    }

    ComPtr<ID3D11RenderTargetView> GetRenderTargetView() {
        return m_renderTargetView;
    }

    ComPtr<ID3D11Texture2D> GetDepthStencilBuffer() const {
        return m_depthStencilBuffer;
    }

    ComPtr<ID3D11DepthStencilState> GetDepthStencilState() const {
        return m_depthStencilState;
    }

    ComPtr<ID3D11RasterizerState> GetRasterizerState() const
    {
        return m_rasterizerSate;
    }

    void CheckResult(HRESULT hr, ID3DBlob *errorBlob);

    int m_screenWidth;
    int m_screenHeight;
    HWND m_mainWindow;
    D3D11_VIEWPORT m_screenViewport;

    // DX relatedCS_CLASSDC
    ComPtr<ID3D11Device> m_device;
    ComPtr<ID3D11DeviceContext> m_context;
    ComPtr<ID3D11RenderTargetView> m_renderTargetView;
    ComPtr<IDXGISwapChain> m_swapChain;
    ComPtr<ID3D11RasterizerState> m_rasterizerSate;

    // Depth buffer Related
    ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
    ComPtr<ID3D11DepthStencilView> m_depthStencilView;
    ComPtr<ID3D11DepthStencilState> m_depthStencilState;
};
}; // namespace LunaEngine