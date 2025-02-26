//
//  MemoViewModel.swift
//  textEditor
//
//  Created by Seungho Jang on 2/26/25.
//

import UIKit
import Combine

class MemoViewModel : ObservableObject {
    @Published private(set) var memos: [Memo] = []
    private let storageService: StorageManageServiceProtocol
    private var cancellables = Set<AnyCancellable>()    // Combine -> subscription managing
    
    init(storageService: StorageManageServiceProtocol = UserDefaultStorageService()) {
        self.storageService = storageService
        loadMemos()
    }
    
    func addMemo(content: String) {
        let newMemo = Memo(content: content)
        memos.append(newMemo)
        saveMemos()
    }
    
    func deleteMemo(at indexSet: IndexSet){
        memos.remove(atOffsets: indexSet)
        saveMemos()
    }
    
    private func loadMemos() {
        storageService.load(forKey: "memos")
            .map { data in
                (try! JSONDecoder().decode([Memo].self, from: data))
            }
            .assign(to: \.memos, on: self)
            .store(in: &cancellables)
    }
    
    private func saveMemos() {
        do {
            let data = try JSONEncoder().encode(memos)
            storageService.save(data, forKey: "memos")
        } catch {
            print("Failed to save memo: \(error)")
        }
    }
}
