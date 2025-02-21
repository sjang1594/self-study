//
//  Renderer.swift
//  Shader
//
//  Created by Seungho Jang on 2/20/25.

import MetalKit

class Renderer : NSObject, MTKViewDelegate {
    var parent: MetalView
    var device: MTLDevice!
    var commandQueue: MTLCommandQueue!
    var pipeline: MTLRenderPipelineState
    var vertexBuffer: MTLBuffer?
    var indexBuffer: MTLBuffer?
    var texture: MTLTexture?
    var samplerState: MTLSamplerState?
    var time: Float = 0.0
    
    var vertices: [Vertex] = [
        Vertex(position: SIMD3<Float>(-1, 1, 0),
               color: SIMD4<Float>(1, 0, 0, 1),
               texture: SIMD2<Float>(0, 0)),
        Vertex(position: SIMD3<Float>(-1, -1, 0),
               color: SIMD4<Float>(0, 1, 0, 1),
               texture: SIMD2<Float>(0, 1)),
        Vertex(position: SIMD3<Float>(1, -1, 0),
               color: SIMD4<Float>(0, 0, 1, 1),
               texture: SIMD2<Float>(1, 1)),
        Vertex(position: SIMD3<Float>(1, 1, 0),
               color: SIMD4<Float>(1, 0, 1, 1),
               texture: SIMD2<Float>(1, 0))
    ]
    
    var indicies: [UInt16] = [
        0, 1, 2, 2, 3, 0
    ]
    
    var modelConstants = ModelConstants()
    
    init(_ parent: MetalView){
        self.parent = parent
        self.device = Renderer.initDevice()
        self.commandQueue = Renderer.initCommandQueue(device: device)
        
        if let texture = Renderer.setTexture(device: device, imageName: "lens.jpg"){
            self.texture = texture
        }
        
        let descriptor = MTLSamplerDescriptor()
        descriptor.minFilter = .linear
        descriptor.magFilter = .linear
        samplerState = device.makeSamplerState(descriptor: descriptor)
        
        self.pipeline = buildPipeline(device: device, texture: texture)
     
        self.vertexBuffer = device.makeBuffer(bytes: vertices,
                                         length: vertices.count * MemoryLayout<Vertex>.stride,
                                         options: [])
        self.indexBuffer = device.makeBuffer(bytes: indicies,
                                        length: indicies.count * MemoryLayout<UInt16>.stride,
                                        options: [])
    
        super.init()
    }
    
    private static func initDevice() -> MTLDevice {
        guard let device = MTLCreateSystemDefaultDevice() else {
            fatalError()
        }
        return device
    }
    
    private static func initCommandQueue(device: MTLDevice) -> MTLCommandQueue {
        guard let commandQueue = device.makeCommandQueue() else {
            fatalError()
        }
        return commandQueue
    }
    
    func mtkView(_ view: MTKView, drawableSizeWillChange size: CGSize) {}
    
    func draw(in view: MTKView) {
        guard let drawble = view.currentDrawable else { return }
        
        guard let commandBuffer = commandQueue.makeCommandBuffer() else { return }
        
        let descriptor = view.currentRenderPassDescriptor
        descriptor?.colorAttachments[0].clearColor = MTLClearColor(red: 0.1, green: 0.1, blue: 0.1, alpha: 1)
        descriptor?.colorAttachments[0].loadAction = .clear
        descriptor?.colorAttachments[0].storeAction = .store

        guard let descriptor else { return }
    
        guard let commandEncoder = commandBuffer.makeRenderCommandEncoder(descriptor: descriptor) else { return }
        
        guard let vertexBuffer = vertexBuffer,
              let indexBuffer = indexBuffer else { return }
        
        commandEncoder.setRenderPipelineState(pipeline)
        commandEncoder.setVertexBuffer(vertexBuffer,
                                       offset: 0,
                                       index: 0)
        
        time += 1 / Float(view.preferredFramesPerSecond)
        let animateBy = abs(sin(time) * 0.5 + 0.5)
        
        let rotationMatrix = simd_float4x4(rotationZ: animateBy)   // model
        let viewMatrix = simd_float4x4(translation: SIMD3<Float>(0, 0, 4)) // camera
        let modelViewMatrix = simd_mul(rotationMatrix, viewMatrix)
        let projectionMatrix = simd_float4x4(
            projectionFov: radians(fromDeg: 70),
            near: 0.1, far: 20, aspect: Float(view.bounds.width / view.bounds.height))
        
        modelConstants.modelViewMatrix = matrix_multiply(projectionMatrix, modelViewMatrix)
        
        commandEncoder.setVertexBytes(&modelConstants,
                                      length: MemoryLayout<ModelConstants>.stride,
                                      index: 1)
        
        commandEncoder.setFragmentTexture(texture, index: 0)
        commandEncoder.setFragmentSamplerState(samplerState, index: 0)
        commandEncoder.drawIndexedPrimitives(type: .triangle,
                                             indexCount: indicies.count,
                                             indexType: .uint16,
                                             indexBuffer: indexBuffer,
                                             indexBufferOffset: 0)
        commandEncoder.endEncoding()
        commandBuffer.present(drawble)
        commandBuffer.commit()
    }
    
    private static func setTexture(device: MTLDevice, imageName: String) -> MTLTexture? {
        let textureLoader = MTKTextureLoader(device: device)
        var texture: MTLTexture? = nil
        
        let options: [MTKTextureLoader.Option: Any] = [
            .SRGB: false,
            .generateMipmaps: true
        ]
        
        if let textureURL = Bundle.main.url(forResource: imageName, withExtension: nil){
            do {
                texture = try textureLoader.newTexture(URL: textureURL, options: options)
            } catch {
                print("Failed to load texture")
            }
        }
        
        return texture
    }
}
