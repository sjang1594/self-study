//
//  PipelineBuilder.swift
//  Shader
//
//  Created by Seungho Jang on 2/20/25.
//

import Metal

func buildPipeline(device: MTLDevice) -> MTLRenderPipelineState {
    let pipeline: MTLRenderPipelineState
    let pipelineDescriptor = MTLRenderPipelineDescriptor()
    let library = device.makeDefaultLibrary()!
    pipelineDescriptor.vertexFunction = library.makeFunction(name: "vertexShader")
    pipelineDescriptor.fragmentFunction = library.makeFunction(name: "fragmentShader")
    pipelineDescriptor.colorAttachments[0].pixelFormat = .bgra8Unorm
    
    let vertexDescriptor = MTLVertexDescriptor()
    // Position
    vertexDescriptor.attributes[0].format = .float3
    vertexDescriptor.attributes[0].offset = 0
    vertexDescriptor.attributes[0].bufferIndex = 0
    // Color
    vertexDescriptor.attributes[1].format = .float4
    vertexDescriptor.attributes[1].offset = MemoryLayout<SIMD4<Float>>.stride // color
    vertexDescriptor.attributes[1].bufferIndex = 0
    vertexDescriptor.layouts[0].stride = MemoryLayout<Vertex>.stride
    pipelineDescriptor.vertexDescriptor = vertexDescriptor

    do {
        pipeline = try device.makeRenderPipelineState(descriptor: pipelineDescriptor)
        return pipeline
    } catch _ as NSError {
        fatalError()
    }
}
