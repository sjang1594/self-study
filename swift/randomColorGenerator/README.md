## Objective: Create the Random Color Generator 

## Key Result

![Random Color Generator](<.gif/2025-02-10 22.04.40.gif>)

### Steps.
1. Create UIView, UILabel in the middle to represent the color ("R", "G", "B"), UIButton for change & reset the color for UIView
2. Use UIColor for randomize color (randomize range would be 0...1, which is normalized color)
3. change the background color(UIView), update the color value on UILabel
4. connect event actions for change & reset color.

## Things I've learned 

**UIButton Action**

Regular way would be to use `AddTarget()` but you can add closure to UIButton.
* [UI Button Event Closure](https://ios-development.tistory.com/1237)
* [Stack Overflow](https://stackoverflow.com/questions/25919472/adding-a-closure-as-target-to-a-uibutton)

Example Code:
```swift
let action = UIAction(title: "") { action in
    print("Button tapped!")
}

UIButton(type: .system, primaryAction: action)
```

**NoStoryboard vs Storyboard**
So, it's best not to use storyboard. To make it short.
```markdown
Storyboards fail at runtime, not at compile time:

You have a typo in a segue name or connected it wrong in your storyboard? It will blow up at runtime. You use a custom UIViewController subclass that doesn't exist anymore in your storyboard?

Storyboards add two extra liabilities to your project:

(1) The Storyboard Editor tool that generates the storyboard XML and (2) the runtime component that parses the XML and creates UI and controller objects from it. Both parts can have bugs that you can't fix.

Storyboards don't allow you to enable Auto Layout for individual View(-Controller)s:

By checking/unchecking the Auto Layout option in a Storyboard, the change is applied to ALL controllers in the Storyboard.
...
``` 

* [Redit](https://www.reddit.com/r/swift/comments/vufo89/storyboard_or_no_storyboard/?rdt=53535)

* [Not to use Storyboard](https://www.quora.com/Are-there-any-advantages-to-not-using-storyboards-when-developing-an-iOS-app-with-Swift)

* [To Set Up Env w/ Storyboard](https://tdcian.tistory.com/424)