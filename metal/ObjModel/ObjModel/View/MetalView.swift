//
//  MetalView.swift
//  ObjModel
//
//  Created by Seungho Jang on 2/24/25.
//

import SwiftUI
import MetalKit

struct MetalView: UIViewRepresentable {
    @EnvironmentObject var gameScene: GameScene
    
    func makeCoordinator() -> Coordinator {
        <#code#>
    }
    
    func makeUIView(context: UIViewRepresentableContext<MetalView>) -> MTKView {
        <#code#>
    }
    
    func updateUIView(_ uiView: MTKView, context: UIViewRepresentableContext<MetalView>) {
        <#code#>
    }
}
