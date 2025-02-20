//
//  Texturable.swift
//  TextureImpl
//
//  Created by Seungho Jang on 2/20/25.
//

import MetalKit

class Material {
    let texture: MTLTexture
    let sampler: MTLSamplerState
    
    init(device: MTLDevice, allocator: MTKTextureLoader, filename: String){
        let options: [MTKTextureLoader.Option: Any] = [
            .SRGB: false,
            .generateMipmaps: true
        ]
        
        do {
            texture = try allocator.newTexture(name: filename, scaleFactor: 1.0, bundle: Bundle.main, options: options)
        } catch {
            fatalError()
        }
        
        let samplerDesc = MTLSamplerDescriptor()
        samplerDesc.sAddressMode = .repeat
        samplerDesc.tAddressMode = .repeat
        samplerDesc.minFilter = .linear
        samplerDesc.magFilter = .linear
        samplerDesc.mipFilter = .linear
        samplerDesc.maxAnisotropy = 8
        
        sampler = device.makeSamplerState(descriptor: samplerDesc)!
    }
}
