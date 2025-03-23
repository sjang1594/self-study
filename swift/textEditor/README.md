## Objective: Notepad (textEditor, what I called)

## Key Result
![Notepad](<.gif/2025-02-11 17.21.06.gif>)

### Steps
1. Set as `ViewController()` as rootViewController to `UINavigationController`.
2. Create UITableView, StretcyTableHeaderView() (this is from the Youtube Source which contains imageview())
3. Set UserData as struct
   1. content (String)
   2. createdAt (Date)
4. Add AddMemoAction (when AddMemoAction is triggered.)
   1. insert `UIAlertController` in order to insert user-defined data (content)
   2. bridged between `UIAlertAction` to update the `memoList`, then update the `reloadData()`
5. Use `UITableViewDelegate` to enable `delete` function by swiping gesture.
6. save `memoList` into UserDefaults.
7. load `memoList` from UserDefaults when app is reloaded by user.

## Things I Learned 
* [Stretchy TableView](https://www.youtube.com/watch?v=ur7UsnCVPjc&t=183s&ab_channel=iOSAcademy)
* [TableView Setup](https://medium.com/@sarinyaswift/easy-tableview-setup-tutorial-swift-4-ad48ec4cbd45)
* [Insert Icon as Image](https://www.youtube.com/watch?v=Giq8jRnh0Gk&t=396s&ab_channel=SwiftfulThinking)
* [Save App Data with UserDefault](https://www.youtube.com/watch?v=1QOLiELlpGk&t=529s&ab_channel=SwiftfulThinking)
* [MVVM](https://github.com/cristydobson/CryptoMarket_iOS_MVVM_Combine/tree/main)