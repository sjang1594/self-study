//
//  MetalView.swift
//  Shader
//
//  Created by Seungho Jang on 2/20/25.
//

import MetalKit
import SwiftUI

struct MetalView : UIViewRepresentable {
    func makeCoordinator() -> Renderer {
        Renderer(self)
    }
    
    func makeUIView(context: UIViewRepresentableContext<MetalView>) -> MTKView {
        let mtkView = MTKView()
        mtkView.delegate = context.coordinator
        
        guard let device = MTLCreateSystemDefaultDevice() else {
            fatalError("No GPU is connected")
        }
        
        mtkView.device = device
        mtkView.preferredFramesPerSecond = 60
        mtkView.enableSetNeedsDisplay = false // renderloop for MTKView
        mtkView.framebufferOnly = false
        mtkView.drawableSize = mtkView.frame.size
        return mtkView
    }
    
    func updateUIView(_ uiView: MTKView, context: UIViewRepresentableContext<MetalView>) {}
}

#Preview {
    MetalView()
}
