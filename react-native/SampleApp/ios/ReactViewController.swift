//
//  ReactViewController.swift
//  SampleApp
//
//  Created by Seungho Jang on 2/14/25.
//
import UIKit
import React_RCTAppDelegate

class ReactViewController : UIViewController
{
  override func viewDidLoad() {
    super.viewDidLoad()
    let factory = (RCTSharedApplication()?.delegate as? RCTAppDelegate)?.rootViewFactory
    self.view = factory?.view(withModuleName: "HelloWorld")
  }
}
