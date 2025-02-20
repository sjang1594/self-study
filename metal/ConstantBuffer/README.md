### Shader Animation (Index Buffer & Constant Buffer)
* Written in SwiftUIKit. IOS. Other details are not written for simplicity.

Other Steps are shown in the TriangleRender

1. Make sure to set `enableSetNeedsDisplay = false` in `MetalView.swift` because this will make the screen not refreshed every time. (which in this case, draw is called every time)
2. Create Structure for sending the data to the GPU (check .shader file)
3. Create vertices / indices to reduce what to draw (check `Renderer.swift`)
4. Create drawIndexedPrimitive for drawing (check `Renderer.swift`) and set the vertexBytes for `constants` data are passing into index 1 ([[buffer 1]]).
5. Add a parameter to the .shader file. 

### Output
![Alt text](<../asset/gif/2025-02-20 10.35.29.gif>)