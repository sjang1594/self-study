# Reflection

한줄로 요약하자면, X-ray 를 찍는것과 같다

```c#
using System;
using System.Reflection;

// Reflection 를 사용하게 되면 X-Ray 찍는것 과 같이,
// Monster 에 대한 Class 를 들여다보고 수정할수 있다라는 뜻과 같다
// All the monster's atributes will be yield within run time.

namespace CSharp
{ 
    class Important : System.Attribute
    {
        string message;

        public Important(string message) { this.message = message;  }
    }

    class Monster
    {
        [Important("Very Important")]
        public int hp;
        protected int attack;
        private float speed;
        void Attack() { }
    }

    class Program
    {
        public static void Main(string[] args)
        {
            // Reflection : X-Ray
            Monster monster = new Monster();

            // From C#, you can access or use the object type.
            // That's why there is .GetType()
            Type type = monster.GetType();

            var fields = type.GetFields(System.Reflection.BindingFlags.Public
                | System.Reflection.BindingFlags.NonPublic
                | System.Reflection.BindingFlags.Static
                | System.Reflection.BindingFlags.Instance);

            foreach(FieldInfo field in fields)
            {
                string acess = "protected";

                if (field.IsPublic)
                    acess = "public";
                else if (field.IsPrivate)
                    acess = "private";

                var attributes = field.GetCustomAttributes();

                Console.WriteLine($"{acess} {field.FieldType.Name} {field.Name}");
            }
        }
    }
}

```

