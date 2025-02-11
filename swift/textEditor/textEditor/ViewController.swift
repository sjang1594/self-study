//
//  ViewController.swift
//  textEditor
//
//  Created by Seungho Jang on 2/11/25.
//

import UIKit
import Then

struct Memo : Codable {
    let content: String
    let createdAt: Date
}

class ViewController: UIViewController, UITableViewDelegate, UITableViewDataSource, UIScrollViewDelegate {
    
    // MARK: - Properties
    var memoList: [Memo] = []
    
    lazy var tableView = UITableView().then {
        $0.backgroundColor = UIColor.white
        $0.register(UITableViewCell.self, forCellReuseIdentifier: "cell")
        $0.translatesAutoresizingMaskIntoConstraints = false
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        configurationUI()
    }
    
    private func configurationUI(){
        view.addSubview(tableView)
        tableView.delegate = self
        tableView.dataSource = self
        tableView.frame = self.view.bounds
        
        let header = StretchyTableHeaderView(frame: CGRect(x:0, y:0, width: self.view.frame.size.width, height: self.view.frame.size.width))
        header.imageView.image = UIImage(systemName: "text.document")
        tableView.tableHeaderView = header
        setupNavigationBar()
    }
    
    func setupNavigationBar() {
        navigationItem.title = "Memo Editor"
        let addBtn = UIBarButtonItem(barButtonSystemItem: .add, target: self, action: #selector(addMemo))
        navigationItem.rightBarButtonItem = addBtn
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return memoList.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "cell", for: indexPath)
        
        let memo = memoList[indexPath.row]
        
        let dateFormatter = DateFormatter()
        dateFormatter.dateStyle = .short
        dateFormatter.timeStyle = .short
        
        cell.textLabel?.text = "\(memo.content) \t \(dateFormatter.string(from: memo.createdAt))"
        return cell
    }
    
    func tableView(_ tableView: UITableView, commit editingSytle: UITableViewCell.EditingStyle, forRowAt indexPath: IndexPath){
        
        if editingSytle == .delete {
            memoList.remove(at: indexPath.row)
            tableView.deleteRows(at: [indexPath], with: .automatic)
        }
    }
    
    func scrollViewDidScroll(_ scrollView: UIScrollView) {
        guard let header = tableView.tableHeaderView as? StretchyTableHeaderView else {
            return
        }
        header.scrollViewDidScroll(scrollView: tableView)
    }
    
    // Mark: - Actions
    @objc func addMemo() {
        let alert = UIAlertController(title: "New Memo", message: "Enter New Memo", preferredStyle: .alert)
        alert.addTextField { textField in textField.placeholder = "Memo Content"}
        
        let addAction = UIAlertAction(title: "Add", style: .default) { [weak self] _ in
            if let content = alert.textFields?.first?.text, !content.isEmpty {
                
                let newMemo = Memo(content: content, createdAt: Date())
                self?.memoList.append(newMemo)
                self?.tableView.reloadData()
            }
        }
        
        let cancelAction = UIAlertAction(title: "Cancel", style: .cancel, handler: nil)
        
        alert.addAction(addAction)
        alert.addAction(cancelAction)
        self.present(alert, animated: true, completion: nil)
    }
    
    func saveData() {
        do {
            let data = try JSONEncoder().encode(memoList)
            UserDefaults.standard.set(data, forKey: "memoList")
        } catch {
            print("Failed to save memos: \(error)")
        }
    }
    
    func loadData() {
        if let savedData = UserDefaults.standard.data(forKey: "memoList") {
            do {
                memoList = try JSONDecoder().decode([Memo].self, from: savedData)
                tableView.reloadData()
            } catch {
                print("Failed to load memos: \(error)")
            }
        }
    }
}

#if DEBUG
import SwiftUI

struct Preview: PreviewProvider {
   static var previews: some View {
       UINavigationController(rootViewController: ViewController())
           .toPreview()
   }
}
#endif
