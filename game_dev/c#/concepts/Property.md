# **Property**

## 객체지향의 은닉성 이란 (What is hiding?)

예를 들어서 설명을 하자, 아래와 같이 코드가 있다고 한다면, 만약 Knight 를 instantiate 한다고 한다면, 모든 코드 사용자가 이 Knight 클래스 안에 `hp` 를 사용 할수 있을거다. 그렇다고 하면, 누가 modify 했는지도 모를수도 있다.
```c#
    class Knight
    {
      public int hp;
    }
```

그래서 위의 코드를 은닉성의 형태로 바꾼다고 하면 아래와 같다.
```c#
namespace CSharp
{
  class program
  {
    class Knight
    {
      protected int _hp;

      public void SetHp(int hp){this._hp = hp;}

      public int GetHp(){return _hp;}
    }
  }

}
```

물론 c++ 에서는 이런식으로 했다고 치자, 하지만 c# 에서는 property 라는 녀석이 있다. 이거에 대해 조금 알아보자

```c#
namespace CSharp
{
  class Program
  {
    class Knight
    {
      protected int _hp;

      // Property
      public int Hp
      {
        get { return _hp; }
        set { this._hp = value; }
      }
    }
  static void Main(string[] args)
  {
    Knight knight = new Knight();
    knight.Hp = 100;

    int hp = knight.Hp;

  }
  }
}
```

자동으로 property 지정해주는 것도 있다
```c#

class Knight
{
  public int Hp{ get; set; }
}
```

또한 default 로 지정도 가능하다
```c#
class Knight
{
  public int Hp{ get; set; } = 100;
}
```
