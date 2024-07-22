#include "Renderer.h"

namespace LunaEngine {
Renderer::Renderer(HWND window, int width, int height, int canvasWidth,
                   int canvasHeight) {
    Initialize(window, width, height, canvasWidth, canvasHeight);
}

void Renderer::Initialize(HWND window, int width, int height, int canvasWidth,
                          int canvasHeight) {}

void Renderer::InitShaders() {}

void Renderer::Render() {}

void Renderer::Update() {}

void Renderer::Release() {}
} // namespace LunaEngine
