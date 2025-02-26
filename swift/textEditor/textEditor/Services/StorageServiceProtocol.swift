//
//  StorageService.swift
//  Protocol
//  Created by Seungho Jang on 2/26/25.

import Foundation
import Combine

protocol StorageManageServiceProtocol {
    func save(_ data: Data, forKey key: String)
    func load(forKey key: String) -> AnyPublisher<Data, Never>
}
