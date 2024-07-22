#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <iostream>
#include <memory>
#include <vector>
#include <windows.h>

namespace LunaEngine {
class Renderer {
  public:
    Renderer(HWND window, int width, int height, int canvasWidth,
             int canvasHeight);
    void Initialize(HWND window, int width, int height, int canvasWidth,
                    int canvasHeight);
    void InitShaders();
    void Render();
    void Update();
    void Release();

  private:
    int canvasWidth, canvasHeight;
    float backgroundColor[4] = {0.8f, 0.8f, 0.8f, 0.8f};
};
} // namespace LunaEngine