//
//  Error.swift
//  ConstantBuffer
//
//  Created by Seungho Jang on 2/19/25.
//

enum MetalError : Error {
    case deviceCreateFailed
    case commandQueueCreateFailed
    case libraryCreateFailed
    case pipelineStateCreateFailed
    case commandbufferCreateFailed
    case commandEncoderCreateFailed
    case bufferCreateFailed
    case descriptorFactoryCreateFailed
    case renderPipelineDescriptorCreateFailed
    
    var localizedDescription: String {
        switch self {
        case .deviceCreateFailed:
            return "Failed to Create GPU Device"
        case .commandQueueCreateFailed:
            return "Failed to Create Command Queue"
        case .libraryCreateFailed:
            return "Failed to Create Metal Library"
        case .commandbufferCreateFailed:
            return "Failed to Create Command Buffer"
        case .commandEncoderCreateFailed:
            return "Failed to Create Command Encoder"
        case .pipelineStateCreateFailed:
            return "Failed to Create Pipeline State"
        case .descriptorFactoryCreateFailed:
            return "Failed to Create Descriptor"
        case .bufferCreateFailed:
            return "Failed to Create Buffer"
        case .renderPipelineDescriptorCreateFailed:
            return "Failed to Create Render Pipeline Descriptor"
        }
    }
}
