//
//  StretchHeader.swift
//  textEditor
//
//  Created by Seungho Jang on 2/11/25.
//

import Foundation
import UIKit

final class StretchyTableHeaderView: UIView {
    // MARK: - Properties
    public let imageView = UIImageView().then {
        $0.translatesAutoresizingMaskIntoConstraints = false
        $0.clipsToBounds = true
        $0.contentMode = .scaleAspectFill
    }
    lazy var containerView = UIView().then {
        $0.translatesAutoresizingMaskIntoConstraints = false
    }
    
    private var imgViewHeightConstraint = NSLayoutConstraint()
    private var imgViewBottomConstraint = NSLayoutConstraint()
    private var containerViewHeightConstraint = NSLayoutConstraint()
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        setupViews()
    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
    private func setupViews() {
        addSubview(containerView)
        // add imageview into containerview
        containerView.addSubview(imageView)
        setViewConstraints()
    }
    
    private func setViewConstraints(){
        NSLayoutConstraint.activate([
            widthAnchor.constraint(equalTo: containerView.widthAnchor),
            centerXAnchor.constraint(equalTo: containerView.centerXAnchor),
            heightAnchor.constraint(equalTo: containerView.heightAnchor),
        ])
        
        containerView.widthAnchor.constraint(equalTo: imageView.widthAnchor).isActive = true
        containerViewHeightConstraint = containerView.heightAnchor.constraint(equalTo: self.heightAnchor)
        containerViewHeightConstraint.isActive = true
        
        imgViewBottomConstraint = imageView.bottomAnchor.constraint(equalTo: containerView.bottomAnchor)
        imgViewBottomConstraint.isActive = true
        imgViewHeightConstraint = imageView.heightAnchor.constraint(equalTo: containerView.heightAnchor)
        imgViewHeightConstraint.isActive = true
    }
    
    func setImage(_ image: UIImage?) {
        imageView.image = image
    }
    
    public func scrollViewDidScroll(scrollView: UIScrollView){
        containerViewHeightConstraint.constant = scrollView.contentInset.top
        let offsetY = -(scrollView.contentOffset.y + scrollView.contentInset.top)
        containerView.clipsToBounds = offsetY <= 0
        imgViewBottomConstraint.constant = offsetY >= 0 ? 0 : -offsetY / 2
        imgViewHeightConstraint.constant = max(offsetY + scrollView.contentInset.top, scrollView.contentInset.top)
    }
}
