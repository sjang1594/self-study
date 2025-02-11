## Objective: Create the Counter App

## Key Result

![Counter App](<.gif/2025-02-11 00.26.21.gif>)

### Steps.
1. Create UILabel in the middle to represent the color `counter Value`, three UIButtons for `+`, `-` & `reset` to increment, decrement and reset the counter value
2. Add Label Logic to set the bound for counter value and disable the buttons(`+`, `-`)

## Things I've learned
* [UINavigationController](https://ios-daniel-yang.tistory.com/entry/iOSSwift-UINavigationController-%EC%82%B4%ED%8E%B4%EB%B3%B4%EA%B8%B0)

**Lazy Var**
> * Lazy var (to use, 'lazy' you need to use var) because `lazy var` is related to memory, which will not be in the memory until we actually use it. But when it's loaded, then it will be loaded and allocated to memory.
  * The lazy bar can be used only in this data type (struct / class), and can't be used as `Computed Property`. This feels like some constant property (like use it when i need to use it, else don't use this)
  * To use the lazy var, this should be done in self.

```swift
class Person {
    var name:String
    
    lazy var greeting:String = {
        return "Hello my name is \((self.name))"
    }()

    lazy var greeting: ()->String = { [weak self] in
        return "Hello my name is \(((self?.name))!)"
    }
  
    init(name:String){
        self.name = name
    }
}

var me = Person(name:"John")

print(me.greeting // Hello my name is John

me.name = "James"

print(me.greeting // Hello my name is John
```

* [Lazy var](https://www.avanderlee.com/swift/lazy-var-property/)
* [Lazy var](https://abhimuralidharan.medium.com/lazy-var-in-ios-swift-96c75cb8a13a)
  
**Then Package**
Usage of then package is to simplify closures for SwiftUI. which can be useful in some what way. But this can be unncessary to bind dependency in a way
* [Usage of Then Package](https://www.youtube.com/@dev_jeongdaeri)
* [Then](https://github.com/devxoul/Then)

**Life Cycle View Controller**
```
loadView (System Call) -> viewDidLoad(after view is loaded, then execute once) -> viewWillAppear(right before view is projected, when view comes back, the task continues) -> View -> viewDidAppear(After View is projected, then task continues) -> viewWilldisAppear(right before view disappear, the task continues, memory still existed) -> view disappear -> viewDidDisappear(when view is completely gone, then taks continues) -> deinit(release memory)
```

**Warning**

> You can override this method in order to create your views manually. If you choose to do so, assign the root view of your view hierarchy to the view property. The views you create should be unique instances and should not be shared with any other view controller object. Your custom implementation of this method should not call super. [emphasis added]

* [Life Cycle Viw Controller](https://ios-daniel-yang.tistory.com/entry/iOSSwift-Life-Cycle%EC%9D%98-loadView)
* [super loadView()](https://stackoverflow.com/questions/9105450/should-super-loadview-be-called-from-loadview-or-not)
