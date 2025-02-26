//
//  Camera.swift
//  ObjModel
//
//  Created by Seungho Jang on 2/22/25.
//

import Foundation
import MetalKit

class Camera {
    var position: simd_float3 // 3d
    var rotation: simd_float3
    var forwardVector: simd_float3
    var upVector: simd_float3
    var rightVector: simd_float3
    
    init(position: simd_float3 = .zero,
         rotation: simd_float3 = .zero,
         forwardVector: simd_float3 = .zero,
         upVector: simd_float3 = .zero,
         rightVector: simd_float3 = .zero) {
        
        self.position = position
        self.rotation = rotation
        self.forwardVector = forwardVector
        self.upVector = upVector
        self.rightVector = rightVector
    }
    
    func update() {
        forwardVector = [ cos(toRadian(rotation.z)) * sin(toRadian(rotation.y)),
                          sin(toRadian(rotation.z)) * sin(toRadian(rotation.y)),
                          cos(toRadian(rotation.y)) ]
        
        let globalUp: simd_float3 = [0.0, 0.0, 1.0]
        rightVector = simd.normalize(simd.cross(globalUp, forwardVector))
        upVector = simd.normalize(simd.cross(forwardVector, rightVector))
    }
    
}
