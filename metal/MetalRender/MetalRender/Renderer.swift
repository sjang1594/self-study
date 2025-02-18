//
//  Renderer.swift
//  MetalRender
//
//  Created by Seungho Jang on 2/18/25.

import MetalKit
/* MTKViewDelegate protocol
   This shows 
 
   Why Renderer need to inherit NSObject s
 */

struct Vertex {
    var position: SIMD2<Float>
    var color: SIMD4<Float>
}

class Renderer : NSObject, MTKViewDelegate {
    /* MARK - */
    let device: MTLDevice!
    var commandQueue: MTLCommandQueue!
    var pipelineState: MTLRenderPipelineState?
    var vertexBuffer: MTLBuffer?
    
    var vertices = [
        Vertex(position: [0, 1], color: [1, 0, 0, 1]),
        Vertex(position: [-1, -1], color: [0, 1, 0, 1]),
        Vertex(position: [1, -1], color: [0, 0, 1, 1]),
    ]
    
    init(device: MTLDevice){
        self.device = device
        super.init()
        commandQueue = device.makeCommandQueue()!
        buildModel()
        buildPipelineState()
    }
    
    private func buildModel() {
        vertexBuffer = device.makeBuffer(bytes: vertices, length: vertices.count * MemoryLayout<Vertex>.stride, options: [])!
    }
    
    private func buildPipelineState(){
        let library = device.makeDefaultLibrary()
        let vertexFunction = library?.makeFunction(name: "vertexShader")
        let fragmentFunction = library?.makeFunction(name: "fragmentShader")
        
        let pipelineDescriptor = MTLRenderPipelineDescriptor()
        pipelineDescriptor.vertexFunction = vertexFunction
        pipelineDescriptor.fragmentFunction = fragmentFunction
        pipelineDescriptor.colorAttachments[0].pixelFormat = .bgra8Unorm
        
        do {
            pipelineState = try device.makeRenderPipelineState(descriptor: pipelineDescriptor)
        } catch let error as NSError{
            print("error: \(error.localizedDescription)")
        }
    }
    
    func mtkView(_ view: MTKView, drawableSizeWillChange size: CGSize) {}
    
    func draw(in view: MTKView) {
        guard let drawable = view.currentDrawable,
              let pipelineState = pipelineState,
              let descriptor = view.currentRenderPassDescriptor else { return }
        
        /* Clear */
        descriptor.colorAttachments[0].clearColor = MTLClearColor(red: 1.0, green: 1.0, blue: 1.0, alpha: 1.0)
        descriptor.colorAttachments[0].loadAction = .clear
        
        guard let commandBuffer = commandQueue.makeCommandBuffer(),
              let commandEncoder = commandBuffer.makeRenderCommandEncoder(descriptor: descriptor) else { return }

        commandEncoder.setRenderPipelineState(pipelineState)
        commandEncoder.setVertexBuffer(vertexBuffer, offset: 0, index: 0)
        commandEncoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 3)
        commandEncoder.endEncoding()
        
        commandBuffer.present(drawable)
        commandBuffer.commit()
    }
}
