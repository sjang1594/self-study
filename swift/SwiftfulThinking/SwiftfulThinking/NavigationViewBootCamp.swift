//
//  NavigationViewBootCamp.swift
//  SwiftfulThinking
//
//  Created by Seungho Jang on 2/25/25.
//

import SwiftUI

struct NavigationViewBootCamp: View {
    var body: some View {
        NavigationView {
            ScrollView{
                NavigationLink("Hello World!", destination: MySubView())
                Text("Hello, World!")
                Text("Hello, World!")
                Text("Hello, World!")
            }
            .navigationTitle("All Inboxes")
            .navigationBarTitleDisplayMode(.automatic)
            .navigationBarItems(
                leading: Image(systemName: "person.fill"),
                trailing:
                    NavigationLink(destination: MySubView(),
                                   label: {
                                       Image(systemName: "gear")
                                   })
                    .accentColor(.red)
            )
        }
    }
}

struct MySubView: View {
    @Environment(\.presentationMode) var presentationMode
    
    var body: some View {
        Color.green.edgesIgnoringSafeArea(.all)
            .navigationTitle("Green Screen")
            .navigationBarHidden(true)
        
        VStack {
            Button("Back Button"){
                presentationMode.wrappedValue.dismiss()
            }
            NavigationLink("Click Here", destination: Text("3rd screen"))
        }
    }
}

#Preview {
    NavigationViewBootCamp()
}
