//
//  ViewController.swift
//  randomColorGenerator
//
//  Created by Seungho Jang on 2/10/25.

import UIKit

class ViewController: UIViewController {

    private let backgroundView = UIView()
    private let colorLabel = UILabel()
    private let changeColorBtn = UIButton(type: .system)
    private let resetBtn = UIButton(type: .system)
    private let defaultColorString = "R: 255, G: 255, B: 255"
    
    override func viewDidLoad() {
        super.viewDidLoad()
        /* Main Layout */
        setupMainLayout()
        /* Actions Setup */
        setupActions()
    }

    private func setupMainLayout(){
        setupBackgroundView()
        setupColorLabel()
        setupButtons()
    }
    
    private func setupBackgroundView() {
        view.addSubview(backgroundView)
        // AutoLayout, not Frame-Based-Layout (true)
        backgroundView.translatesAutoresizingMaskIntoConstraints = false;
        // to remove redunant .isActive
        NSLayoutConstraint.activate([
            backgroundView.topAnchor.constraint(equalTo: self.view.safeAreaLayoutGuide.topAnchor),
            backgroundView.leadingAnchor.constraint(equalTo: self.view.safeAreaLayoutGuide.leadingAnchor),
            backgroundView.trailingAnchor.constraint(equalTo: self.view.safeAreaLayoutGuide.trailingAnchor),
            backgroundView.bottomAnchor.constraint(equalTo: self.view.safeAreaLayoutGuide.bottomAnchor)
        ])
        backgroundView.backgroundColor = .white
    }
    
    private func setupColorLabel() {
        backgroundView.addSubview(colorLabel)
        colorLabel.translatesAutoresizingMaskIntoConstraints = false;
        // to remove redunant .isActive
        NSLayoutConstraint.activate([
            colorLabel.centerXAnchor.constraint(equalTo: self.backgroundView.safeAreaLayoutGuide.centerXAnchor),
            colorLabel.centerYAnchor.constraint(equalTo: self.backgroundView.safeAreaLayoutGuide.centerYAnchor)
        ])
        
        colorLabel.text = defaultColorString
        colorLabel.textAlignment = .center
    }
    
    private func setupActions() {
        changeColorBtn.addTarget(self, action: #selector(changeColor), for: .touchUpInside)
        resetBtn.addTarget(self, action: #selector(resetColor), for: .touchUpInside)
        /* Closure way
        changeColorBtn.addAction(UIAction { [weak self] _ in
            self?.changeColor() }, for: .touchUpInside)
        resetBtn.addAction(UIAction { [weak self] _ in
            self?.resetColor()}, for: .touchUpInside) */
    }
    
    private func setupButtons() {
        // quick way to add two buttons into subview
        [changeColorBtn, resetBtn].forEach { button in
            backgroundView.addSubview(button)
            button.translatesAutoresizingMaskIntoConstraints = false;
        }
        changeColorBtn.setTitle("Change Color", for: .normal)
        changeColorBtn.configuration = .borderedProminent()
        resetBtn.setTitle("Reset", for: .normal)
        resetBtn.configuration = .borderedProminent()

        // to remove redunant .isActive
        NSLayoutConstraint.activate([
            changeColorBtn.leadingAnchor.constraint(equalTo: self.backgroundView.safeAreaLayoutGuide.leadingAnchor, constant:20),
            changeColorBtn.bottomAnchor.constraint(equalTo: self.backgroundView.safeAreaLayoutGuide.bottomAnchor, constant:-20),
            resetBtn.trailingAnchor.constraint(equalTo: self.backgroundView.safeAreaLayoutGuide.trailingAnchor, constant:-20),
            resetBtn.bottomAnchor.constraint(equalTo: self.backgroundView.safeAreaLayoutGuide.bottomAnchor, constant:-20),
            changeColorBtn.widthAnchor.constraint(equalTo:
                                                    resetBtn.safeAreaLayoutGuide.widthAnchor)
        ])
    }
    
    @objc private func changeColor() {
        // normalized for all color
        let r = CGFloat.random(in: 0...1)
        let g = CGFloat.random(in: 0...1)
        let b = CGFloat.random(in: 0...1)
        let randColor = UIColor(red:r, green:g, blue:b, alpha:1.0)
        backgroundView.backgroundColor = randColor
        colorLabel.text = "R: \(Int(r * 255)), G: \(Int(g*255)), B: \(Int(b*255))"
    }
    
    @objc private func resetColor() {
        backgroundView.backgroundColor = .white
        colorLabel.text = defaultColorString
    }
}

#if DEBUG
import SwiftUI

struct MyVCRepresentable: UIViewControllerRepresentable {
    // UI View Controller Setup
    @available(iOS 18.0, *)
    func makeUIViewController(context: Context) -> some UIViewController {
        return ViewController()
    }
    
    // update UI ViewController
    func updateUIViewController(_ uiViewController: UIViewControllerType, context: Context) {
    }
}

@available(iOS 18.0, *)
struct MyVCRepresentable_Previews: PreviewProvider {
    static var previews: some View {
        MyVCRepresentable()
    }
}


#endif
