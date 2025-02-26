//
//  SceneDelegate.swift
//  textEditor
//
//  Created by Seungho Jang on 2/11/25.
//

import UIKit

class SceneDelegate: UIResponder, UIWindowSceneDelegate {

    var window: UIWindow?
    func scene(_ scene: UIScene, willConnectTo session: UISceneSession, options connectionOptions: UIScene.ConnectionOptions) {
        // downcasting if failed, return
        guard let windowScene = (scene as? UIWindowScene) else { return }
        self.window = UIWindow(windowScene: windowScene)
        let mainViewController = ViewController()
        let navigationController = UINavigationController(rootViewController: mainViewController)
        self.window?.rootViewController = navigationController
        self.window?.makeKeyAndVisible()
    }
}
