//
//  EnvironmentObject.swift
//  SwiftfulThinking
//
//  Created by Seungho Jang on 2/25/25.
//

import SwiftUI

// What if all child view want to access the Parent  View Model.
// Then use EnvironmentObject.
// You can certainly do pass StateObject / ObservedObject, but what
// if you have a hierchy views want to access the parent views.
// but might be slow
class EnvironmentViewModel: ObservableObject {
    @Published var dataArray: [String] = []
    
    init() {
        getData()
    }
    
    func getData() {
        self.dataArray.append(contentsOf: ["iPhone", "AppleWatch", "iMAC", "iPad"])
    }
}

struct EnvironmentBootCampObject: View {
    @StateObject var viewModel: EnvironmentViewModel = EnvironmentViewModel()
    
    var body: some View {
        NavigationView {
            List {
                ForEach(viewModel.dataArray, id: \.self) { item in
                    NavigationLink(
                        destination: DetailView(selectedItem: item),
                        label: {
                            Text(item)
                        })
                }
            }
            .navigationTitle("iOS Devices")
        }
        .environmentObject(viewModel)
    }
}

struct DetailView : View {
    let selectedItem: String
    var body: some View {
        ZStack {
            Color.orange.ignoresSafeArea()
            
            NavigationLink(
                destination: FinalView(),
                label: {
                    Text(selectedItem)
                        .font(.headline)
                        .foregroundColor(.orange)
                        .padding()
                        .padding(.horizontal)
                        .background(Color.white)
                        .cornerRadius(30)
                })
        }
    }
}

struct FinalView: View {
    @EnvironmentObject var viewModel: EnvironmentViewModel
    var body: some View {
        ZStack {
            LinearGradient(gradient: Gradient(colors: [.blue, .red]),
                           startPoint: .topLeading,
                           endPoint: .bottomTrailing)
            .ignoresSafeArea()
            
            ScrollView {
                VStack(spacing: 20) {
                    ForEach(viewModel.dataArray, id: \.self) { item in
                        Text(item)
                    }
                }
            }
            .foregroundColor(.white)
            .font(.largeTitle)
        }
    }
}

#Preview {
    EnvironmentBootCampObject()
}
