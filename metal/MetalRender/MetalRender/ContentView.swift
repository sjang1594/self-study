//
//  ContentView.swift
//  MetalRender
//
//  Created by Seungho Jang on 2/18/25.
//

import SwiftUI
import MetalKit

struct ContentView: UIViewRepresentable {
    let mtkView = MTKView()
    let device: MTLDevice
    
    init() {
        guard let device = MTLCreateSystemDefaultDevice() else {
            fatalError("Metal is not available")
        }
        self.device = device
    }
    
    func makeCoordinator() -> Renderer {
        return Renderer(device: device)
    }
    
    func makeUIView(context: UIViewRepresentableContext<ContentView>) -> MTKView {
        mtkView.device = device
        mtkView.delegate = context.coordinator // What this delegate does
        mtkView.preferredFramesPerSecond = 60  // FPS Setup
        mtkView.enableSetNeedsDisplay = true
        mtkView.framebufferOnly = false
        mtkView.drawableSize = mtkView.frame.size
        return mtkView
    }
    
    func updateUIView(_ uiView: MTKView, context: UIViewRepresentableContext<ContentView>) {}
}

#Preview {
    ContentView()
}
