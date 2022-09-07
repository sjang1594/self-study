## Interface 

일단 추상 클래스는 '행위에 강조를 하는 클래스'다 
```c#
namespace CSharp
{
    class Monster
    {
        public virtual void Shout(){}
    }

    class Orc : Monster
    {
        public override void Shout()
        {
            Console.WriteLine("록타르 오가르!");
        }
    }

    class Skeleton : Monster
    {
        public override void Shout()
        {
            Console.WriteLine("꾸엑")
        }
    }
    class Program 
    {
        static void Main(string[] args)
        {

        }
    }
}
```

여기서 보면, override 를 정의해서 option 처럼 느낄수 있다. 예를들어서 Monster 를 상속받은 Skeleton class 안에 있는 함수 `public override voide Shout()`는 주석 처리나 없어도 상관없다. 하지만, 강요를 하려고 할때, 즉 제약을 두려고 할때, 반드시 `Shout()` 이라는 함수를 꼭 써야 한다고 정의 하려고 할때 `abstract` 라는걸 추가한다. 

```c#
namespace CSharp
{
    abstract class Monster
    {
        // 함수도 추상적으로 만들면 
        public abstract void Shout();
    }

    class Orc: Monster
    {
        public override void Shout()
        {
            Console.WriteLine("록타르 오가르!")
        }   
    }
    class Program
    {

    }
}
```

이렇게 함으로써, 반드시 `Monster` 를 상속받는 `Shout` 이라는 함수를 반드시 사용(강요) 해야한다. 

그럼 `interface` 란 ? `abstract void Shout()` member function 을 `Monster` 클래스를 상속 받는 클래스는 사용해야 한다고 했다. 이러한걸 생각해보면 `Orc` 클래스에서 abstract 함수를 무조건 사용해야한다는 signature 이 된다. 

예를들어서, 공중에 나는 몬스터를 표현하고 싶다고 하자. 

```c#
abstract class Flyable
{
    public abstract void Fly()
}

class Orc : Monster
{
    public override void Shout(){}
}

// C# 에서는 이 아래 다중상속이 되지않는다. 
// class FlyableOrc : Orc, Flyable
// {
// }

```

위의 주석에 코드에서 에러가 뜬다. 왜 C++ 에서는 다중상속이 되는데, C# 에서는 안된다. 이 문제를 보려면 죽음에 다이아몬드라는 말이 있다. 만약 맨위의 예제와 그다음의 예제를 들었을때, 혼정인 `SeletonOrc` 라는 객체를 생성하고 `Orc` `Skeleton` 이라는 객체를 상속 받았다고 했을때, 과연 `shout` 이라는 함수를 썻었을때 누가 호출이 되어야 되느냐에 문제가 생긴다. 

해결하는 방법은 무엇일까? 즉 인터페이스는 물려주고, 구현부는 물려주지 않고 알아서 결정할수 있게 할까 ?
```c#
namespace CSharp
{
    class Program
    {
        abstract class Monster 
        {
            public abstract void Shout();
        }

        //*****//
        interace iFlyable
        {
            // Pubic, private, abstract.. 안써도 됨.
            void Fly();
        }

        class Orc : Monster
        {
            public override void Shout()
            {
                Console.WriteLine("록타르 오가르");
            }
        }

        class Skeleton : Monster
        {
            public override void Shout()
            {
                Console.WriteLine("꾸엑");
            }
        }
        
        class FlyableOrc : Orc, iFlyable{
            pubic void Fly(){
                
            }
        }

        // 응용
        static void DoFly(iFlyable flyable){
            flyable.Fly();
        }

        static void Main(string[] args){
            iFlyable flyable = new FlyableOrc()

            // 또는
            FlyableOrc orc = new FlyableOrc()
            DoFly(orc)

        }
    }
}
```