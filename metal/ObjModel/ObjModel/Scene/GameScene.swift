//
//  GameScene.swift
//  ObjModel
//
//  Created by Seungho Jang on 2/22/25.
//

import Foundation
import SwiftUI

class GameScene : ObservableObject {
    @Published var player: Camera
    
    init(){
        player = Camera(
            position: [0, 0, -2],
            rotation: [0, 0, 0] )
    }
    
    func update() {
        player.update() // update for each axis 
    }
}
