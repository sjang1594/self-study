//
//  StateBootCamp.swift
//  SwiftfulThinking
//
//  Created by Seungho Jang on 2/25/25.
//

import SwiftUI

struct StateBootCamp: View {
    @State var backgroundColor: Color = Color.green
    @State var myTitle: String = "My Title"
    @State var count: Int = 0
    
    var body: some View {
        ZStack {
            backgroundColor
                .edgesIgnoringSafeArea(.all)
            
            VStack(spacing: 20) {
                Text(myTitle)
                    .font(.title)
                Text("Count: \(count)")
                    .font(.headline)
                    .underline()
                
                HStack(spacing: 20) {
                    Button("Button 1") {
                        backgroundColor = .red
                        myTitle = "Button 1 was pressed"
                        count += 1
                    }
                    
                    Button("BUTTON 2") {
                        backgroundColor = .blue
                        myTitle = "BUTTON 2 was pressed"
                        count -= 1
                    }
                }
            }
            .foregroundColor(.white)
        }
    }
}

#Preview {
    StateBootCamp()
}
