//
//  ViewModel.swift
//  SwiftfulThinking
//
//  Created by Seungho Jang on 2/25/25.
//

import SwiftUI

struct FruitModel : Identifiable {
    let id: String = UUID().uuidString
    let name: String
    let count: Int
}

class FruitViewModel : ObservableObject {
    @Published var fruitArray: [FruitModel] = [] // state in class (alert to ViewModel)
    @Published var isLoading: Bool = false
    
    init() {
        getFruits()
    }
    
    func getFruits() {
        let fruit1 = FruitModel(name: "Banana", count: 2)
        let fruit2 = FruitModel(name: "Watermelon", count: 9)
        
        isLoading = true
        DispatchQueue.main.asyncAfter(deadline: .now() + 3.0){
            self.fruitArray.append(fruit1)
            self.fruitArray.append(fruit2)
            self.isLoading = false
        }
    }
    
    func deleteFruit(index: IndexSet) {
        fruitArray.remove(atOffsets: index)
    }
}

struct ViewModel: View {
    // vs ObservableObject.
    // @StateObject is persist, it's basically not changing, it will not refresh
    // @StateObject -> Uset This on CREATION / INIT
    // @ObservableObject Use this for subview
    @StateObject var fruitViewModel: FruitViewModel = FruitViewModel()
    
    var body: some View {
        NavigationView {
            List {
                if fruitViewModel.isLoading {
                    ProgressView()
                    
                } else {
                    ForEach(fruitViewModel.fruitArray) { fruit in
                        HStack {
                            Text("\(fruit.count)")
                                .foregroundColor(.red)
                            Text(fruit.name)
                                .font(.headline)
                                .bold()
                        }
                    }
                    .onDelete(perform: fruitViewModel.deleteFruit)
                }
            }
            .listStyle(.grouped)
            .navigationTitle("Fruit List")
            .navigationBarItems(
                trailing: NavigationLink(destination: SecondScreen(fruitViewModel: fruitViewModel), label: { Image(systemName: "arrow.right")
                    .font(.title)})
            )
        }
    }
}

struct SecondScreen : View {
    @Environment(\.presentationMode) var presentationMode
    @ObservedObject var fruitViewModel: FruitViewModel
    var body: some View {
        ZStack {
            Color.green.ignoresSafeArea()
            VStack {
                Button(action: {
                    presentationMode.wrappedValue.dismiss()
                }, label: {
                    Text("Go Back")
                        .foregroundColor(.white)
                        .font(.largeTitle)
                        .fontWeight(.semibold)
                })
                
                VStack {
                    ForEach(fruitViewModel.fruitArray) { fruit in
                        Text(fruit.name)
                            .foregroundColor(.white)
                            .font(.headline)
                    }
                }
            }
        }
    }
}

#Preview {
    ViewModel()
}
