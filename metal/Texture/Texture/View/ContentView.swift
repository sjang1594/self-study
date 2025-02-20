//
//  ContentView.swift
//  Shader
//
//  Created by Seungho Jang on 2/20/25.
//

import SwiftUI

struct ContentView: View {
    var body: some View {
        VStack {
            MetalView()
                .cornerRadius(20)
        }
        .padding()
    }
}

#Preview {
    ContentView()
}
