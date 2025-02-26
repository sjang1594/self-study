//
//  ObjModelApp.swift
//  ObjModel
//
//  Created by Seungho Jang on 2/21/25.
//

import SwiftUI

@main
struct ObjModelApp: App {
    @StateObject private var gameScene = GameScene()
    var body: some Scene {
        WindowGroup {
            ContentView()
        }
    }
}
