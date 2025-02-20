//
//  Renderer.swift
//  ConstantBuffer
//
//  Created by Seungho Jang on 2/18/25.
//

import MetalKit

class Renderer: NSObject, MTKViewDelegate {
    var parent: MetalView
    var device: MTLDevice!
    var commandQueue: MTLCommandQueue!
    var pipelineState: MTLRenderPipelineState
    var vertexBuffer: MTLBuffer?
    var indexBuffer: MTLBuffer?
    var time: Float = 0.0
    
    struct Constants {
        var animatedBy: Float = 0.0
    }
    var constants = Constants()
    
    let vertices: [Float] = [
        -1,  1, 0, // v0
        -1, -1, 0,
         1, -1, 0,
         1,  1, 0
    ]
    
    let indices: [UInt16] = [
        0, 1, 2,
        2, 3, 0,
    ]

    
    init(_ parent: MetalView) {
        self.parent = parent
        
        /* Device Setup*/
        guard let device = MTLCreateSystemDefaultDevice() else {
            fatalError(MetalError.deviceCreateFailed.localizedDescription)
        }
        self.device = device
        
        /* Command Queue*/
        guard let commandQueue = device.makeCommandQueue() else {
            fatalError(MetalError.commandQueueCreateFailed.localizedDescription)
        }
        self.commandQueue = commandQueue
        
        /* Create Vertex Buffer */
        vertexBuffer = device.makeBuffer(bytes: vertices, length: vertices.count * MemoryLayout<Float>.stride, options: [])
        indexBuffer = device.makeBuffer(bytes: indices, length: indices.count * MemoryLayout<UInt16>.stride, options: [])
        
        /* pipeline descriptor & libary hook shader */
        let pipelineDescriptor = MTLRenderPipelineDescriptor()
        let library = device.makeDefaultLibrary()
        pipelineDescriptor.vertexFunction = library?.makeFunction(name: "vertexShader")
        pipelineDescriptor.fragmentFunction = library?.makeFunction(name: "fragmentShader")
        pipelineDescriptor.colorAttachments[0].pixelFormat = .bgra8Unorm
        
        do {
            pipelineState = try device.makeRenderPipelineState(descriptor: pipelineDescriptor)
        } catch {
            fatalError(MetalError.pipelineStateCreateFailed.localizedDescription)
        }
        
        super.init()
    }
    
    func mtkView(_ view: MTKView, drawableSizeWillChange size: CGSize){
    
    }
     
    func draw(in view: MTKView){
        guard let drawable = view.currentDrawable else { return }
    
        time += 1 / Float(view.preferredFramesPerSecond)
        let animatedBy = abs(sin(time) * 0.5 + 0.5)
        constants.animatedBy = animatedBy
        
        guard let commandBuffer = commandQueue.makeCommandBuffer() else {
            print(MetalError.bufferCreateFailed.localizedDescription)
            return
        }
        
        /* Initialze Render Pass Descriptor*/
        let descriptor = view.currentRenderPassDescriptor
        descriptor?.colorAttachments[0].clearColor = MTLClearColor(red: 0.51, green: 0.51, blue: 0.51, alpha: 1.0)
        descriptor?.colorAttachments[0].loadAction = .clear
        descriptor?.colorAttachments[0].storeAction = .store
        
        guard let descriptor else {
            print(MetalError.descriptorFactoryCreateFailed.localizedDescription)
            return
        }
        
        guard let commandEncoder = commandBuffer.makeRenderCommandEncoder(descriptor: descriptor) else {
            print(MetalError.commandEncoderCreateFailed.localizedDescription)
            return
        }
        
        guard let vertexBuffer = vertexBuffer,
              let indexBuffer = indexBuffer else {
            print(MetalError.bufferCreateFailed.localizedDescription)
            return
        }
        
        commandEncoder.setRenderPipelineState(pipelineState)
        commandEncoder.setVertexBuffer(vertexBuffer, offset: 0, index: 0)
        commandEncoder.setVertexBytes(&constants, length: MemoryLayout<Constants>.stride, index: 1)
        commandEncoder.drawIndexedPrimitives(type: .triangle,
                                             indexCount: indices.count,
                                             indexType: .uint16,
                                             indexBuffer: indexBuffer,
                                             indexBufferOffset: 0)
        commandEncoder.endEncoding()
        commandBuffer.present(drawable) // schedule to submit
        commandBuffer.commit()
    }
}
