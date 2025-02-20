//
//  MetalView.swift
//  ConstantBuffer
//
//  Created by Seungho Jang on 2/18/25.
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
        
        // Set device
        guard let device = MTLCreateSystemDefaultDevice() else {
            fatalError("No GPU is connected")
        }
        
        mtkView.device = device
        mtkView.preferredFramesPerSecond = 60
        mtkView.enableSetNeedsDisplay = false
        mtkView.framebufferOnly = false
        mtkView.drawableSize = mtkView.frame.size
        return mtkView
    }
    
    func updateUIView(_ uiView: MTKView, context: UIViewRepresentableContext<MetalView>) {}
}

#Preview {
    MetalView()
}
