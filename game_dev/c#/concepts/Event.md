# Event

Delegate 이란 문법은 물론 좋다, 하지만 단점이 있다. 아래의 예를 보자.


```c#
namespace CSharp
{
  class Program
  {
    //** delegate **//
    // 함수가 아니라, 형식이다. 하나의 형식이라는 말은 (type) 과 같다
    // 형식은 형식인데, 함수 자체로 인자로 넘겨주는 그런 형식
    // return int, input 은 없다.
    // OnClicked 이 delegate 형식의 이름이다!
    delegate int OnClicked();

    static void ButtonPressed(OnClicked clickedFunction)
    {
      clickedFunction();
    }

    static int TestDelegate()
    {
      Console.WriteLine('Hello Dellegate');
      return 0;
    }

    static void Main(string[] args)
    {
      Console.WriteLine();

      // 왜 구지 귀찮게, 객체를 만드느냐 ?
      // 객체를 만들면, 다른 함수를 집어 넣을수 있기 떄문이다.
      OneClicked clicked = new OneClicked(TestDelegate);
      // 덫붙인다는 의미가 결국엔, chaining 을 한다는 뜻
      clicked += TestDelegate2

      ButtonPressed(clicked)

      clicked();
    }
  }
}
```

위의 코드와 같이, clicked() 라는 함수를 어디든지에서 계속 불러올것이다. 다시말하자면, 중요한건 `ButtonPressed` 를 통해서, 마우스클릭을 delegate 문법을 사용해서 clicked 를 만들었지만, clicked() 라는 함수를 호출 할수 있으므로, 이건 좋은 설계가 아닐것이다.

그래서 이 문법을 보완하기 위해서, `Event` 라는 keyword 를 사용 해야된다.

```c#
//InputManager.cs

using System;
using System.Collections.Generic;
using System.Text;

namespace CSharp
{
  // 사용자가 mouse 나 keyboard 를 catch 해서, 다른 로직 / 프로그램에 넘겨주는 역활을 한다. (중간 매개 역활을 하는 클래스)
  class InputManager
  {
    public delegate void OnInputKey();
    public event OnInputKey InputKey;

    public void Update()
    {
        if(Console.KeyAvailable == false)
          return;

        ConsoleKeyInfo info = Console.ReadKey();

        // If key 'A' was pushed / selected
        if(info.Key == ConsoleKey.A)
        {
          // 모두에게 알려준다!
          InputKey();
        }
    }
  }
}
```

```c#
using System;
using System.Collections;
using System.Collections.Generic;

namespace CSharp
{
  class Program
  {
    void OnInputTest()
    {
      Console.WriteLine("Input Received!")
    }

    static void Main(string[] args)
    {
      InputManager inputManager = new InputManager();

      // 구독 신청을 해야된다
      inputManager.InputKey += OnInputTest;

      while(true)
      {
        inputManager.Update();
      }

      //inputManger.InputKey();
    }
  }
}

```
`delegate` 과 달리 `Event` 를 사용함으로써, `inputManager.InputKey()` 가 안된다. 구독자를 `public event OnInputKey InputKey`를 모집을 한 이후에, 특정 key 가 발동했을때, 그 구독자들에게 뿌리는 역활 처리를 할수 있게 한다. 이러한 pattern 을 `observer` pattern 이라고 한다.
