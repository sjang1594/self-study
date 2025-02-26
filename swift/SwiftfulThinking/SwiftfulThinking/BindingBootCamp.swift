//
//  BindingBootCamp.swift
//  SwiftfulThinking
//
//  Created by Seungho Jang on 2/25/25.
//

import SwiftUI

struct BindingBootCamp: View {
    // Parent View
    @State var backgroundColor: Color = .green
    @State var title: String = "Title"
    var body: some View {
        ZStack {
            backgroundColor
                .edgesIgnoringSafeArea(.all)
            VStack {
                Text(title)
                    .foregroundStyle(.white)
                ExtractedView(backgroundColor: $backgroundColor, title: $title)
            }
        }
    }
}

#Preview {
    BindingBootCamp()
}

// Subview
struct ExtractedView: View {
    @Binding var backgroundColor: Color
    @Binding var title: String
    @State var buttonColor: Color = .blue
    var body: some View {
        Button (action: {
            backgroundColor = .orange
            buttonColor = Color.pink
            title = "Changed!"
        }, label: {
            Text("Button")
                .foregroundColor(.white)
                .padding()
                .padding(.horizontal)
                .background(buttonColor)
                .cornerRadius(10)
        })
    }
}
