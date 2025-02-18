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

class Renderer : NSObject, MTKViewDelegate {
    /* MARK - */
    var parent: ContentView
    var metalDevice: MTLDevice!
    var metalCommandQueue: MTLCommandQueue!
    let pipelineState: MTLRenderPipelineState
    let vertexBuffer: MTLBuffer
    
    init(_ parent: ContentView) {
        /* One deivce & One CommandQueue */
        self.parent = parent
        /* Setup Device */
        if let metalDevice = MTLCreateSystemDefaultDevice() {
            self.metalDevice = metalDevice
        }
         
        /* Setup CommandQueue */
        if let metalCommandQueue = metalDevice.makeCommandQueue() {
            self.metalCommandQueue = metalCommandQueue
        }
        
        let pipelineDescriptor = MTLRenderPipelineDescriptor()
        let lib = metalDevice.makeDefaultLibrary()
        pipelineDescriptor.vertexFunction = lib?.makeFunction(name: "vertexShader")
        pipelineDescriptor.fragmentFunction = lib?.makeFunction(name: "fragmentShader")
        pipelineDescriptor.colorAttachments[0].pixelFormat = .bgra8Unorm
        
        do {
            try pipelineState = metalDevice.makeRenderPipelineState(descriptor: pipelineDescriptor)
        } catch {
            fatalError()
        }
        
        let vertices = [
            Vertex(position: [0, 1], color: [1, 0, 0, 1]),
            Vertex(position: [-1, -1], color: [0, 1, 0, 1]),
            Vertex(position: [1, -1], color: [0, 0, 1, 1]),
        ]
        vertexBuffer = metalDevice.makeBuffer(bytes: vertices, length: vertices.count * MemoryLayout<Vertex>.stride, options: [])!
        
        super.init()
    }
    
    /* Case: where user rotate the device (drawableSize will change)  */
    func mtkView(_ view: MTKView, drawableSizeWillChange size: CGSize) {
        
    }
    
    /* Method that calls every frame
       The view has a drawable (object displayed on screen) and the render pass descriptor (How the buffer are to be rendered)
       
     */
    func draw(in view: MTKView){
        // This is where actually drawing happen in the preview or contentview
        guard let drawable = view.currentDrawable else { return }
        
        /* To hold CommandEncoder */
        let commandBuffer = metalCommandQueue.makeCommandBuffer()

        /* Describe what to draw (pass this into command encoder)
           colorAttachments are like a color render command */
        let descriptor = view.currentRenderPassDescriptor
        descriptor?.colorAttachments[0].clearColor = MTLClearColorMake(1.0, 1.0, 1.0, 1.0)
        descriptor?.colorAttachments[0].loadAction = .clear
        descriptor?.colorAttachments[0].storeAction = .store
        
        // To encode what they need to do as descriptor shown
        let renderEncoder = commandBuffer?.makeRenderCommandEncoder(descriptor: descriptor!)
        renderEncoder?.setRenderPipelineState(pipelineState)
        renderEncoder?.setVertexBuffer(vertexBuffer, offset: 0, index: 0)
        renderEncoder?.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 3)
        
        // Finishing Encoding the Command
        renderEncoder?.endEncoding()
        commandBuffer?.present(drawable)
        commandBuffer?.commit()
    }
}
