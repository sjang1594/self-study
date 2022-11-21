# **Delegate**

Delegate 이란 대리자 라는 의미를 내포 하고 있다. 예시를 들자.

만약 대기업 사장님과 미팅을 해야한다고 치자. 그렇다고 한다면, 우리는 분명 연락을 취하려고 사장님의 비서와 연락을 취하겠고
(직렬적) 나중에 용건이 끝났을때 우리의 미팅을 하는 용건과 연락처를 남겨달라고 (거꾸로) call_back 을 달라고 한다. 주로
UI 쪽 만들때 구현을 한다.


```c#
using System;
using System.Collections;
using System.Collections.Generic;

namespace CSharp
{
  class Program
  {
    static void ButtonPressed()
    {

    }

    static void Main(string[] args)
    {

    }
  }
}
```

만약 UI 와 게임의 동작을 같이 했을때의 문제가 생각 보다 많다. 그리고 reliablity 의 측면에 있어서, 설계를 할시
두개의 함수는 independent 하지만, 안에서 작동하는 서로 연관 되어있는 dependent 구조 일수도 있다. 그래서 이걸 구현하려면
어떤 call_back 하는 함수들이 필요하며, call_back 을 하려면, 인자를 함수 자체로 넘겨주는게 맞을것이다.

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
