```c#

using System;
using System Collection gneric;

namespace CSharp
{
    class Program
    {
        class MyIntList
        {
            int[] arr = new int[10];
        }

        class MyFloatList
        {
            int[] arr = new float[10];
        }

        class MyShortList
        {
            int [] arr = new short[10]
        }
        class MyMonsterList
        {
            Monster[] arr = new Monster[10];
        }

        class Monster
        {

        }
        static void Main(string[] args)
        {
            // obj 어떤 type 이든 소화가 가능 하다.
            // object type 은 참조 타입 즉 힙에 들어가고, 예를들어서 int, string 들은 다 stack 에 들어간다.
            object obj = 3;
            object obj = "Hello World";
            int num = (int)obj;
            string str = (string)obj;

            //What about var?
            //compiler will make a decision depending on the assigned value, but object type is object type itself.
            //var obj3 = 3;
            //var obj4 = "Hellow world";
        }
    }
}
```

---
So, what is generic type ? Let's look at some example
```c#
namespace CSharp
{
    class Program
    {
        class MyList<T>
        {
            T[] arr = new T[10];
            
            public T GetItem(int i)
            {
                return arr[i];
            }
        }

        // **This is special one for c#, not in c++

        // The value T doesnt matter what type it is, but T should be some format of struct
        class MyList<T> where T : struct
        {
            T[] arr = new T[20];
        }
        
        
        //If it needs to be reference type
        class MyList<T> where T : class
        {
            T[] arr = new T[10];
        }

        // 어떠한 인자가 없는 기본 constructor 이여만 한다.
        class MyList<T> where T : new()
        {
            ''''
        }
        // T 를 어떤거든 넣을수 있지만, 단 T 는 Monster 혹은 Monster 를 상속 받는 클래스이여야 한다.
        class MyList<T> where T : Monster
        {

        }

        class Monster
        {
            ''''
        }

        // Applied into function
        static void Test<T>(T input)
        {
            Test<int>(3);
            Test<float>(3.0f);
        }

        static void Main(string[] args)
        {
            MyList<int> myIntList = new MyList<int>()
            int item = MyIntList.GetItem(0);
            MyList<short> myShortList = new MyList<short>
            MyList<Monster> myMonsterList = new MyList<Monster>();
        }
    }
}
```
