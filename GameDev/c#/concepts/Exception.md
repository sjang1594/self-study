# Exception

```c#
using System;
using System.Collections;
using System.Collections.Generic;

namespace CSharp
{
  class Program
  {
    // Exception 을 상속 받고 
    class TestException : Exception
    {
      
    }
    static void Main(string[] args)
    {
      try
      {
        // 1. 0 으로 나눌때
        // 2. 잘못된 메모리를 참조 (null 을 접근 했을때)
        // 3. TypeCasting 을 못했었을때
        // 4. Overflow 가 이루어졌을때
        int a = 10;
        int b = 0;
        int result = a / b;
        
        // 이런식으로 던져도 된다
        throw new TextException();
      }
      // 만약 DivideByZeroException 이 실행되면, Exception e 로 안간다.
      catch (DivideByZeroException e){}
      catch (Exception e){}
      // Error 가 마지막으로 Finally 로 확인이 가능하다.
      finally{
        // 예: DB, 파일정리
      }
    }
  }
}
```

