//
//  UserModel.swift
//  textEditor
//
//  Created by Seungho Jang on 2/26/25.
//

import UIKit

struct Memo : Codable {
    var id: String = UUID().uuidString
    let content: String
    let createdAt: Date
    
    init(content: String, createdAt: Date = Date()) {
        self.content = content
        self.createdAt = createdAt
    }
}
