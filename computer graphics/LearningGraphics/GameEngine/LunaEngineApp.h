#pragma once
#include "LunaEngineAppBase.h"
#include <directxtk/SimpleMath.h>
#include <tuple>
#include <iostream>
#include <vector>

namespace LunaEngine {
using DirectX::SimpleMath::Matrix;
using DirectX::SimpleMath::Vector3;
using namespace DirectX;

// Vertex Definition
struct Vertex {
    Vector3 position;
    Vector3 color;
};

// Constant Buffer Data
struct ModelViewProjectionConstantBuffer {
    Matrix model;
    Matrix view;
    Matrix projection;
};

class LunaEngineApp : public LunaEngineAppBase {
  public:
    LunaEngineApp();
    virtual bool Initialize() override;
    virtual void UpdateGUI() override;
    virtual void Update(float dt) override;
    virtual void Render() override;

    ComPtr<ID3D11VertexShader> m_VertexShader;
    ComPtr<ID3D11PixelShader> m_PixelShader;
    ComPtr<ID3D11InputLayout> m_InputLayout;

    ComPtr<ID3D11Buffer> m_vertexBuffer;
    ComPtr<ID3D11Buffer> m_indexBuffer;
    ComPtr<ID3D11Buffer> m_constantBuffer;
    UINT m_indexCount;

    ModelViewProjectionConstantBuffer m_constantBufferData;
    bool m_usePerspectiveProjection = true;
};
} // namespace LunaEngine