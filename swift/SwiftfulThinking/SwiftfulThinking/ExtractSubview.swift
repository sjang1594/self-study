//
//  ExtractSubview.swift
//  SwiftfulThinking
//
//  Created by Seungho Jang on 2/25/25.
//

import SwiftUI

struct ExtractSubview: View {
    var body: some View {
        ZStack {
            Color(.white).edgesIgnoringSafeArea(.all)
            contentLayer
        }
    }
    
    var contentLayer: some View {
        HStack {
            MyItem(title: "Apples", count: 1, color: .red)
            MyItem(title: "Orange", count: 1, color: .orange)
            MyItem(title: "Bananas", count: 1, color: .yellow)
        }
    }
}

struct MyItem: View {
    let title: String
    let count: Int
    let color: Color
    
    var body: some View {
        VStack {
            Text("\(count)")
            Text(title)
        }
        .padding()
        .background(color)
        .cornerRadius(10)
    }
}

#Preview {
    ExtractSubview()
}
