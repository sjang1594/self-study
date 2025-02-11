//
//  ViewController.swift
//  Counter
//
//  Created by Seungho Jang on 2/10/25.
//

import UIKit
import Then

class ViewController: UIViewController {
    private var count : Int = 0
    
    // Setup UILabel
    lazy var counterLabel = UILabel().then {
        $0.text = "0"
        $0.font = UIFont.systemFont(ofSize: 48, weight: .bold)
        $0.textAlignment = .center
        $0.translatesAutoresizingMaskIntoConstraints = false
    }
    
    // Setup plusButton & Action
    lazy var plusBtn = UIButton().then {
        $0.setTitle("+", for: .normal)
        $0.setTitleColor(.black, for: .normal)
        $0.backgroundColor = .white
        $0.layer.cornerRadius = 3
        $0.translatesAutoresizingMaskIntoConstraints = false
        $0.addAction(UIAction {[weak self] _ in self?.incrementCount()}, for: .touchUpInside)
    }
    
    // Setup minusButton
    lazy var minusBtn = UIButton().then {
        $0.setTitle("-", for: .normal)
        $0.setTitleColor(.black, for: .normal)
        $0.backgroundColor = .white
        $0.layer.cornerRadius = 3
        $0.translatesAutoresizingMaskIntoConstraints = false
        $0.addAction(UIAction { [weak self] _ in
            self?.decrementCount()}, for: .touchUpInside)
    }
    
    // Setup resetButton
    lazy var resetBtn = UIButton().then {
        $0.setTitle("Reset", for: .normal)
        $0.setTitleColor(.black, for: .normal)
        $0.backgroundColor = .white
        $0.layer.cornerRadius = 3
        $0.translatesAutoresizingMaskIntoConstraints = false
        $0.addAction(UIAction { [weak self] _ in
            self?.resetCount()}, for: .touchUpInside)
    }
    
    // Setup StackView including all btns
    private lazy var btnStackView = UIStackView(arrangedSubviews: [minusBtn, plusBtn, resetBtn]).then {
        $0.axis = .horizontal
        $0.distribution = .equalSpacing
        $0.alignment = .center
        $0.translatesAutoresizingMaskIntoConstraints = false
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }
    
    // LifeCycles
    override func loadView() {
        //* Becareful *//
        super.loadView()
        configurationUI()
    }

    fileprivate func configurationUI(){
        self.view.addSubview(counterLabel)
        self.view.addSubview(btnStackView)
        NSLayoutConstraint.activate([
            counterLabel.centerYAnchor.constraint(equalTo: self.view.centerYAnchor),
            counterLabel.centerXAnchor.constraint(equalTo: self.view.centerXAnchor),
            btnStackView.topAnchor.constraint(equalTo: counterLabel.bottomAnchor, constant: 20),
            btnStackView.centerXAnchor.constraint(equalTo: self.view.centerXAnchor)
        ])
        
    }

    // Logic
    private func incrementCount() {
        count += 1
        updateCount()
    }
    
    private func decrementCount() {
        count -= 1
        updateCount()
    }
    
    private func resetCount(){
        count = 0
        updateCount()
    }
    
    private func updateCount() {
        if count < -10 {
            count = -10
        } else if count > 10 {
            count = 10
        }
        
        minusBtn.isEnabled = count > -10;
        plusBtn.isEnabled = count < 10;
        counterLabel.text = "\(count)"
    }
}

#if DEBUG
import SwiftUI
struct Preview: PreviewProvider {
    static var previews: some View {
        ViewController()
            .toPreview()
    }
}
#endif
