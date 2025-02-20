//
//  ContentView.swift
//  ConstantBuffer
//
//  Created by Seungho Jang on 2/18/25.
//

import SwiftUI

struct ContentView: View {
    var body: some View {
        VStack {
            Text("Animating....")
            MetalView()
                .cornerRadius(20)
        }
        .padding()
    }
}

#Preview {
    ContentView()
}
