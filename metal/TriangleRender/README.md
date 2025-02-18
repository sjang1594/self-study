### Draw Triangle
* Written in SwiftUIKit. IOS. Other details are not written for simplicity.

1. Create `MTKDevice`, which represent the GPU device and `CommandQueue` for passing the command
2. In every frame in `draw` in `Renderer.swift`, create commandBuffer and descriptor(`what to do`), then encode this commandBuffer to commandEncoder.
3. Then we tell what PipelineState is by using `MTLRenderPipelineDescriptor` in which, we pass where the vertex shader and pixel shader by using `lib?.makeFunction(name: )` (warning: name must be same as it defined in .metal file).
4. Set those pipelinestate for encoder, then we set the vertexbuffer (how many vertex) and the primitive (shape: how these are going to be shaped depending on MTLPrimitiveType)

```swift
public enum MTLPrimitiveType : UInt, @unchecked Sendable {
    case point = 0
    case line = 1
    case lineStrip = 2
    case triangle = 3
    case triangleStrip = 4
} 
```

5. then we finish encoding and send it to GPU

### Shader
1. The vertex data from CPU is written in `definition.h`
2. For Vertex Data, it takes the data below, R is up, G is left-bottom corner, B is right-bottom corner.

```swift
vertices = [
            Vertex(position: [0, 1], color: [1, 0, 0, 1]),
            Vertex(position: [-1, -1], color: [0, 1, 0, 1]),
            Vertex(position: [1, -1], color: [0, 0, 1, 1])]
```

3. Within the fragment(pixel) shader from vertex shader, return those color to draw on the screen. 

### Build on IPad
* In order to build your app on IPad, you need to set following things:
  * Set the developer moode 
  * Set the VPN Privacy allowed on your account 

### Result on Preview
<img src="../asset/img/triangle.png" alt="isolated" width="200"/>

### Result on IPad
<img src="../asset/img/triangle_on_ipad.png" alt="isolated" width="200"/>

### Reference
* [Intro to Metal](https://www.youtube.com/watch?v=H2ufvcNvVmA&list=PLn3eTxaOtL2MThB3r1Pz5Z-EQaqBi3dHt&index=2&ab_channel=GetIntoGameDev)
* [Youtube](https://www.youtube.com/watch?v=GLDYreVv4Ns&list=PL23Revp-82LJG3vcDPm8w7b5HTKjBOY0W&index=4&ab_channel=Kodeco)