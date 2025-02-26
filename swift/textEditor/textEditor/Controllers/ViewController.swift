//
//  ViewController.swift
//  textEditor
//
//  Created by Seungho Jang on 2/11/25.
//

import UIKit
import Combine
import Then

// View
class ViewController: UIViewController {
    // MARK: - Properties
    private var viewModel: MemoViewModel
    // MARK: - Combine
    private var cancellables = Set<AnyCancellable>()
    
    private lazy var tableView = UITableView().then {
        $0.delegate = self
        $0.dataSource = self
        $0.frame = view.bounds
        $0.backgroundColor = UIColor.white
        $0.register(UITableViewCell.self, forCellReuseIdentifier: "cell")
        $0.translatesAutoresizingMaskIntoConstraints = false
    }
    
    init(viewModel: MemoViewModel = MemoViewModel()){
        self.viewModel = viewModel
        super.init(nibName: nil, bundle: nil)
    }
    
    /* Incase, support storyboard or NSCoding Protocol
       When the view is created by the code and if programmer uses init(frame:),
       compiler will require us to write init(coder:)
       NSObject -> UIResponder() -> UIView() */
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    // MARK: - Life Cycle
    override func viewDidLoad() {
        super.viewDidLoad()
        configurationUI()
        bindViewModel()
    }
    
    // MARK: - UI Configuration: Subview
    private func configurationUI(){
        view.addSubview(tableView)
        setTableViewConstraints()
        let header = StretchyTableHeaderView(frame: CGRect(x:0, y:0, width: view.frame.size.width, height: view.frame.size.width))
        header.setImage(UIImage(systemName: "text.document"))
        tableView.tableHeaderView = header
        
        configureNavigationBar()
    }
    
    // MARK: - TableView Constraints
    private func setTableViewConstraints() {
        NSLayoutConstraint.activate([
            tableView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor),
            tableView.leadingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leadingAnchor),
            tableView.trailingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.trailingAnchor),
            tableView.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor)
        ])
    }
    
    // MARK: - UI configuration: NavigationBar
    private func configureNavigationBar() {
        navigationItem.title = "Memo Editor"
        // Link to addMemo Action
        navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .add, target: self, action: #selector(addMemo))
    }
    
    // MARK: - Bind View Model
    private func bindViewModel() {
        viewModel.$memos
            .receive(on: DispatchQueue.main)
            .sink { [weak self] _ in
                self?.tableView.reloadData()
            }
            .store(in: &cancellables)
    }
    
    // MARK: - Actions for Adding Memo
    @objc func addMemo() {
        let alert = UIAlertController(title: "New Memo",
                                      message: "Enter New Memo",
                                      preferredStyle: .alert)
        
        alert.addTextField { textField in textField.placeholder = "Memo Content"}
        
        let addAction = UIAlertAction(title: "Add", style: .default) { [weak self] _ in
            /*
            if let textFields = alert.textFields,
                let firstTextField = textFields.first,
                let content = firstTextField.text, {
                    if !content.isEmpty {
                    }
                }
            */
        
            if let content = alert.textFields?.first?.text, !content.isEmpty {
                self?.viewModel.addMemo(content: content)
                self?.tableView.reloadData()
            }
        }
        
        let cancelAction = UIAlertAction(title: "Cancel", style: .cancel, handler: nil)
        
        alert.addAction(addAction)
        alert.addAction(cancelAction)
        // show the alert view controller to this view controller
        self.present(alert, animated: true, completion: nil)
    }
}

extension ViewController: UITableViewDelegate, UITableViewDataSource {
     // Return the number of rows
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return viewModel.memos.count
    }
    
    // Asks the data source for a cell to insert in a particular location of the table view
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "cell", for: indexPath)
        
        /* Data */
        let memo = viewModel.memos[indexPath.row]
        let dateFormatter = DateFormatter()
        dateFormatter.dateStyle = .short
        dateFormatter.timeStyle = .short
        
        cell.textLabel?.text = "\(memo.content) \t \(dateFormatter.string(from: memo.createdAt))"
        return cell
    }
    
    func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCell.EditingStyle,
                   forRowAt indexPath: IndexPath) {
        if editingStyle == .delete {
            viewModel.deleteMemo(at: IndexSet(integer: indexPath.row))
            tableView.deleteRows(at: [indexPath], with: .automatic)
        }
    }
}

extension ViewController : UIScrollViewDelegate {
    func scrollViewDidScroll(_ scrollView: UIScrollView) {
        guard let header = tableView.tableHeaderView as? StretchyTableHeaderView else { return }
        header.scrollViewDidScroll(scrollView: scrollView)
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
