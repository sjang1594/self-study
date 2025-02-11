//
//  StretchHeader.swift
//  textEditor
//
//  Created by Seungho Jang on 2/11/25.
//

import Foundation
import UIKit
import Then

final class StretchyTableHeaderView: UIView {
    public let imageView = UIImageView().then {
        $0.translatesAutoresizingMaskIntoConstraints = false
        $0.clipsToBounds = true
        $0.contentMode = .scaleAspectFill
    }
    
    private var imgViewHeight = NSLayoutConstraint()
    private var imgViewBottom = NSLayoutConstraint()
    // Container for ImageView
    
    lazy var containerView = UIView().then {
        $0.translatesAutoresizingMaskIntoConstraints = false
    }
    
    private var containerViewHeight = NSLayoutConstraint()
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        createViews()
        setViewConstraints()
    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
    private func createViews() {
        addSubview(containerView)
        // add imageview into containerview
        containerView.addSubview(imageView)
    }
    
    private func setViewConstraints(){
        NSLayoutConstraint.activate([
            widthAnchor.constraint(equalTo: containerView.widthAnchor),
            centerXAnchor.constraint(equalTo: containerView.centerXAnchor),
            heightAnchor.constraint(equalTo: containerView.heightAnchor)
        ])
        
        containerView.widthAnchor.constraint(equalTo: imageView.widthAnchor).isActive = true
        containerViewHeight = containerView.heightAnchor.constraint(equalTo: self.heightAnchor)
        containerViewHeight.isActive = true
        
        imgViewBottom = imageView.bottomAnchor.constraint(equalTo: containerView.bottomAnchor)
        imgViewBottom.isActive = true
        imgViewHeight = imageView.heightAnchor.constraint(equalTo: containerView.heightAnchor)
        imgViewHeight.isActive = true
    }
    
    public func scrollViewDidScroll(scrollView: UIScrollView){
        containerViewHeight.constant = scrollView.contentInset.top
        let offsetY = -(scrollView.contentOffset.y + scrollView.contentInset.top)
        containerView.clipsToBounds = offsetY <= 0
        imgViewBottom.constant = offsetY >= 0 ? 0 : -offsetY / 2
        imgViewHeight.constant = max(offsetY + scrollView.contentInset.top, scrollView.contentInset.top)
    }
}
