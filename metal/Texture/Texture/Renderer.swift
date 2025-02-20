//
//  Renderer.swift
//  Shader
//
//  Created by Seungho Jang on 2/20/25.
//

import MetalKit

class Renderer : NSObject, MTKViewDelegate {
    var parent: MetalView
    var device: MTLDevice!
    var commandQueue: MTLCommandQueue!
    var pipeline: MTLRenderPipelineState
    var vertexBuffer: MTLBuffer?
    var indexBuffer: MTLBuffer?
    
    var vertices: [Vertex] = [
        Vertex(position: SIMD3<Float>(-1, 1, 0),  color: SIMD4<Float>(1, 0, 0, 1)),
        Vertex(position: SIMD3<Float>(-1, -1, 0), color: SIMD4<Float>(0, 1, 0, 1)),
        Vertex(position: SIMD3<Float>(1, -1, 0),  color: SIMD4<Float>(0, 0, 1, 1)),
        Vertex(position: SIMD3<Float>(1, 1, 0),   color: SIMD4<Float>(1, 0, 1, 1))
    ]
    
    var indicies: [UInt16] = [
        0, 1, 2, 2, 3, 0
    ]
    
    init(_ parent: MetalView){
        self.parent = parent
        
        guard let device = MTLCreateSystemDefaultDevice() else {
            fatalError()
        }
        self.device = device
        
        guard let commandQueue = device.makeCommandQueue() else {
            fatalError()
        }
        self.commandQueue = commandQueue
        
        pipeline = buildPipeline(device: device)
        
        vertexBuffer = device.makeBuffer(bytes: vertices,
                                         length: vertices.count * MemoryLayout<Vertex>.stride,
                                         options: [])
        indexBuffer = device.makeBuffer(bytes: indicies,
                                        length: indicies.count * MemoryLayout<UInt16>.stride,
                                        options: [])
        super.init()
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
        
        commandEncoder.drawIndexedPrimitives(type: .triangle,
                                             indexCount: indicies.count,
                                             indexType: .uint16,
                                             indexBuffer: indexBuffer,
                                             indexBufferOffset: 0)
        commandEncoder.endEncoding()
        commandBuffer.present(drawble)
        commandBuffer.commit()
    }
}
