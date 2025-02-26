//
//  StorageManager.swift
//  The service to save the data / retrieve data 
//
//  Created by Seungho Jang on 2/26/25.
//

import Foundation
import Combine

class UserDefaultStorageService: StorageManageServiceProtocol {
    private let defaults = UserDefaults.standard
    
    func save(_ data: Data, forKey key: String) {
        defaults.set(data, forKey: key)
    }
    
    func load(forKey key: String) -> AnyPublisher<Data, Never> {
        return Just(defaults.data(forKey: key) ?? Data())
            .eraseToAnyPublisher()
    }
}
