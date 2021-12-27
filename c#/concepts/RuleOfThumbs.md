# Rule of Thumbs (Syntax)

## Object Oriented Programming (OOP)



---

### **Deep Copy VS Shallow Copy**

Example Code :

```c#
/*
 * What are the main difference between struct and class ?
 * First, struct is going to be copy, and class will be ref
*/

using System;

namespace CSharp
{
    // OOP (Objected Oriented Programming)
    // Attribute : hp, attack, pos
    // Function : Move, Attack, Die

    // Ref
    class Knight
    {
        public int hp;
        public int attack;

        // Deep Copy
        public Knight Clone()
        {
            Knight knight = new Knight();
            knight.hp = hp;
            knight.attack = attack;
            return knight;
        }

        public void Move()
        {
            Console.WriteLine("Knight Move");
        }

        public void Attack()
        {
            Console.WriteLine("Knight Attack");
        }
    }

    // Copy
    struct Mage
    {
        public int hp;
        public int attack;
    }

    class Program
    {
        static void KillMage(Mage mage)
        {
            mage.hp = 0;
        }

        static void KillKnight(Knight knight)
        {
            knight.hp = 0;
        }

        static void Main(string[] args)
        {
            // Struct doesn't require new().
            Mage mage;
            mage.hp = 100;
            mage.attack = 50;

            KillMage(mage);
            // Mage's hp did not set to 0 --> Copy
            Console.WriteLine($"Mage hp :{mage.hp}");

            //Copy from other structure
            Mage mage2 = mage;
            mage2.hp = 0;
            Console.WriteLine($"Mage2 hp :{mage2.hp} and attack {mage2.attack}");

            Knight knight = new Knight();

            knight.hp = 100;
            knight.attack = 10;

            KillKnight(knight);

            Knight knight2 = knight;
            knight2.hp = 0;

            Console.WriteLine($"Knight 2 hp : {knight2.hp}");

            //Cloning
            Knight knight3 = knight.Clone();
            knight3.hp = 0;

            Console.WriteLine($"Knight 3 hp : {knight3.hp}");

            //knight.Move();
            //knight.Attack();


        }
    }
}

```

---

### **Constructor**

```c#
/*
 * Constructor :
 */
using System;

namespace CSharp
{
    // OOP (Objected Oriented Programming)
    // Attributes : hp, attack, pos
    // Function : Move, Attack, Die

    class Knight
    {
        public int hp;
        public int attack;

        // Constructor : default settings
        public Knight()
        {
            hp = 100;
            attack = 10;
            Console.WriteLine("Call Constructor");
        }

        // Call the Knight() constructor first,
        // then Knight(int hp).
        // This can be rewritten public Knight(int hp) : Knight()
        public Knight(int hp) : this()
        {
            // This keywords is the hp in the attributes of the class
            this.hp = hp;
            Console.WriteLine("int constructor is called");
        }
				public Knight(int hp, int attack)
        {
          this.hp = hp;
          this.attack = attack;
          Console.WriteLine("int, int constructor is called");
        }

        public Knight Clone()
        {
            Knight knight = new Knight();
            knight.hp = hp;
            knight.attack = attack;
            return knight;
        }

        public void Move()
        {
            Console.WriteLine("Knight Move");
        }

        public void Attack()
        {
            Console.WriteLine("Knight Attack");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Knight knight = new Knight(50, 5);
        }
    }
}

```

---

### **Who the hell are you ? Static ?**

It's good to observe the one that isn't static.

```c#
/*
 * Static :
 */
using System;

namespace CSharp
{
    class Knight
    {
        // These two are called field.
        public int hp;
        public int attack;

   			// Constructor
        public Knight()
        {
            hp = 100;
            attack = 10;
            Console.WriteLine("Call Constructor");
        }

        public Knight(int hp) : this()
        {
            this.hp = hp;
            Console.WriteLine("int constructor is called");
        }
				public Knight(int hp, int attack)
        {
          this.hp = hp;
          this.attack = attack;
          Console.WriteLine("int, int constructor is called");
        }

        public Knight Clone()
        {
            Knight knight = new Knight();
            knight.hp = hp;
            knight.attack = attack;
            return knight;
        }

        public void Move()
        {
            Console.WriteLine("Knight Move");
        }

        public void Attack()
        {
            Console.WriteLine("Knight Attack");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
          // When the instance is created,
          // knight can use the its hp and attack.
          // In other word, each instance can hold its
          // field.
          Knight knight = new Knight();
        }
    }
}

```

Let's make an assumption.

```c#
/*
 * Static :
 */
using System;

namespace CSharp
{
    class Knight
    {
        // These two are called field.
        public int hp;
        public int attack;

        //**STATIC**//
      	static public int a;

   			// Constructor
        public Knight()
        {
            hp = 100;
            attack = 10;
            Console.WriteLine("Call Constructor");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
          // When the instance is created,
          // knight can use the its hp and attack.
          // In other word, each instance can hold its
          // field.
          Knight knight1 = new Knight();

          Knight knight2 = new Knight();
          knight2.hp = 80;

          Knight knight3 = new Knight();
          knight3.hp = 200;

          // Then, what happen to an static variable a?
        }
    }
}
```

The static variable `a` means that each instance that are created(`knight1`,`knight2`,`knight3`) will "share" the variable name `a`. In other word, the variable `a` will be used as only one variable.("Existed as Only One ")

**Then, why do we need it ?**

Let's assume that we have a player id that we would like to increment

```c#
/*
 * Static :
 */
using System;

namespace CSharp
{
    class Knight
    {
        // These two are called field.

        public int hp;
        public int attack;
        public int id;

        //**STATIC**//
      	static public int counter = 1;

   			// Constructor
        public Knight()
        {
            id = counter;
            counter++;
            hp = 100;
            attack = 10;
            Console.WriteLine("Call Constructor");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
          // When the instance is created,
          // knight can use the its hp and attack.
          // In other word, each instance can hold its
          // field.
          Knight knight1 = new Knight();

          Knight knight2 = new Knight();
          knight2.hp = 80;

          Knight knight3 = new Knight();
          knight3.hp = 200;

          // Then, what happen to an static variable a?
        }
    }
}
```

Then, what about the function?

```c#
/*
 * Static
 */
using System;

namespace CSharp
{
    class Knight
    {
        // These two are called field.

        public int hp;
        public int attack;
        public int id;

        //**STATIC**//
      	static public int counter = 1;

        //Static Function & Non-static Function
        // The static function `staticTest()` is
        // subordinated by the class "knight"
        // Also, static function cannot access to the
        // attributes, but static variable can be accessed.
        static public void staticTest(){
          //ex. this can't be done.
          //this.hp = 30
          //this.attack = 100
          counter++;
        };

        // But, nonstatTest function can be accessed by
        // Any instances that are created. In other word, this function is dependent on each instance.
        public void nonstatTest(){};

        //** Just the fact that you put static in front of function does not mean that this function cannot access to instance.
        //Ex
        static public Knight CreateKnight(){
          Knight knight = new Knight();
          knight.hp = 100;
          knight.attack = 1;
          return knight
        }

   			// Constructor
        public Knight()
        {
            id = counter;
            counter++;
            hp = 100;
            attack = 10;
            Console.WriteLine("Call Constructor");
        }
    }


    class Program
    {
        static void Main(string[] args)
        {
          // When the instance is created,
          // knight can use the its hp and attack.
          // In other word, each instance can hold its
          // field.
          Knight knight1 = new Knight();

          Knight knight2 = new Knight();
          knight2.hp = 80;

          Knight knight3 = new Knight();
          knight3.hp = 200;

          //How to call the static function then?
          Knight knight = Knight.CreateKnight();
          knight.Move();

          // For example.
          // Console.WriteLine() --> static function
          // This is non-static function
          // Random rand = new Random();
          // rand.Next()
        }
    }
}
```

## The most important concept in OOP : Abstraction, Encapsulation, Hiding, Inheritance, and Polymorphism.

```c#
namespace CSharp
{
    class Mage
    {
        // Field
        static int counter = 1; // Only one
        public int hp;
        public int attack;
    }

    class Archer
    {
        // Field
        static int counter = 1; // Only one
        public int hp;
        public int attack;
    }

    class Knight
    {
        // Field
        static int counter = 1; // Only one
        public int hp;
        public int attack;
    }
```

The code above shows that repetition of variables in each different class. In other words, it would not be efficient to store the data is repeated in class. What would be the resolution to this ? **One solution would be the inheritence.**

```c#
namespace CSharp
{
    class Player // Parent Class or Base Class
    {
        // Field
        static int counter = 1; // Only one
        public int hp;
        public int attack;
    }
    // All these clases are inherited from the class "Player". Also these are called "Child" class or "derived " class
		class Mage : Player{}
    class Archer : Player{}
    class Knight : Player{}
```

Then, let's test it out

```c#
/*
 * OOP: Hiding/Inheritance/Polymorphism
 */
using System;

namespace CSharp
{
    class Player
    {
        // Field
        static int counter = 1; // Only one
        public int hp;
        public int attack;

        public Player() { Console.WriteLine("Player Constructor is called"); }
    }

    class Mage : Player
    {
        public Mage() { Console.WriteLine("Mage Constructor is called"); }
    }

    class Archer : Player
    {
        public Archer() { Console.WriteLine("Archer Constructor is called"); }
    }

    class Knight : Player
    {
        public Knight() { Console.WriteLine("Knight Constructor is called");}

        static public Knight CreateKnight()
        {
            Knight knight = new Knight();
            knight.hp = 100;
            knight.attack = 10;
            return knight;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Knight knight = new Knight();
        }
    }
}
```

The output looks like this

```c#
Player Constructor is called
Knight Constructor is called
```

So, what is happening right here is that the parent class `Player` is called first since the ` Knight` is derived from `Player`.

Then what if I have a different constructor in parent class.

```c#
  /*
 * OOP: Hiding/Inheritance/Polymorphism
 */
using System;

namespace CSharp
{
    class Player
    {
        // Field
        static int counter = 1; // Only one
        public int hp;
        public int attack;

        public Player() { Console.WriteLine("Player Constructor is called"); }

      	// Overloading //
        public Player(int hp, int attack)
        {
            this.hp = hp;
            this.attack = attack;
            Console.WriteLine($"The new 'Player's called with parameters);
        }
    }

    class Mage : Player
    {
        public Mage() { Console.WriteLine("Mage Constructor is called"); }
    }

    class Archer : Player
    {
        public Archer() { Console.WriteLine("Archer Constructor is called"); }
    }

    class Knight : Player
    {
        // Variable in Parent Class
        base.hp = 100
        // Use the keyword for base, which is for 'Player'(Parent) Class
        public Knight() : base(100, 50)
        { Console.WriteLine("Knight Constructor is called"); }

        static public Knight CreateKnight()
        {
            Knight knight = new Knight();
            knight.hp = 100;
            knight.attack = 10;
            return knight;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Knight knight = new Knight();
        }
    }
}


```

### **Function**

```c#
/*
 * OOP: Hiding/Inheritance/Polymorphism
 */
using System;

namespace CSharp
{
    class Player
    {
        // Field
        static int counter = 1; // Only one
        public int hp;
        public int attack;

        public Player() { Console.WriteLine("Player Constructor is called"); }

        public void Move() { Console.WriteLine("Player moved"); }
        public void Attack() { Console.WriteLine("Player attacked"); }
    }

    class Knight : Player
    {
        public Knight()
        { Console.WriteLine("Knight Constructor is called"); }

        static public Knight CreateKnight()
        {
            Knight knight = new Knight();
            knight.hp = 100;
            knight.attack = 10;
            return knight;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Knight knight = new Knight();
            knight.Move();
            knight.Attack();
        }
    }
}
```

---

## **Hiding**

Why do we need to hide ? The purpose of this is not giving the permission or access to the data or calculation inside. This is why we need to hide things. For example, there are handle, wheels, some etcs that can be visible for drivers. However, the manufacturers are required to hide how the engines works with other devices to secure from drivers.

### **Access Modifier**

| Access Modifier | Explanation                                                  |
| --------------- | :----------------------------------------------------------- |
| Public          | This type(class, structure, interface, delegates) can be access by any external class(including child class) |
| Internal        | This can be accessed within same or similar assembly. But it can't be accessed by other assembly |
| Protected       | This type can be accssed by derived or child class           |
| Private         | This type can only be accessed by the member in same class or structure |

### Examples

```c#
class Mage
    {
        private int skillNum;
        protected int skillTree;

        private void spawnSecretWeapon()
        {
            // Ultimate number should be 3;
            skillNum = 3;
            Console.WriteLine("Spawning.. Secret Weapon");
        }

        // Setter & Getter
        public void SetSkillNum(int skillNum)
        {
            this.skillNum = skillNum;
        }

    }

    class Sorcerer : Mage
    {
        void setSkillTree()
        {
            skillTree = 2;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Knight knight = new Knight();

            Mage mage = new Mage();
            // Access the private member
            // mage.skillNum = 3;

            mage.SetSkillNum(1);
        }
    }
}
```

---

### **Transform the Class Type**

```c#
/*
 * OOP: Class Type
 */
using System;

namespace CSharp
{
    class Player
    {
        protected int hp;
        protected int attack;
    }

    class Knight : Player
    {

    }

    class Mage : Player
    {
        public int mp;
    }

    class Program
    {
        // Why this line of code doesnt work(it crash) after
        // Main calles EnterGame(knight)
        // static void EnterGame(Player player)
        // {
        // Mage mage = (Mage)Player;
        // Mage.mp = 10;
        // }

        static void EnterGame(Player player)
        {
            // How to access to mp in Mage class ?
            bool isMage = (player is Mage);
            if (isMage)
            {
                Mage mage = (Mage)player;
                mage.mp = 10;
            }

            // Other way use a 'as' keyword
            // Mage mage (player as Mage)
            // if (mage != null){
            // mage.mp = 10;
            // }
            // If the knight is the parameter, then mage
            // will be come null.
        }


        static void Main(string[] args)
        {
            // 'new' will create Knight object in the heap
            //  Then, knight in the stack will use reference to
            //  the object in the heap
            Knight knight = new Knight();
            Mage mage = new Mage();

            // Mage type -> Player type
            // Player type -> Mage type ? --> Not really..
            Player magePlayer = mage;
            // Type Casting
            Mage mage2 = (Mage)magePlayer;

            EnterGame(knight);
            EnterGame(mage);
        }
    }
}

```

### **Example of 'Null'**

```c#
static Player FindPlayerByid(int id){
  // Search the player by ID

  // If not found, return null
  return null;
}
```

---

## **Polymorphism**

```c#
/*
 * OOP: Polymorphism
 */

using System;

namespace CSharp
{
    class Player
    {
        protected int hp;
        protected int attack;

        public virtual void Move()
        {
            Console.WriteLine("Player Moved");
        }
    }

    // Overloading(Reuse the function name)
    // Overriding(Used in Polymorphism)
    class Knight : Player
    {
        public override void Move()
        {
            //Parent Move
            base.Move();

            Console.WriteLine("Knight Moved");
        }
    }

    class SuperKnight : Knight
    {
        // Sealed, don't override the function from this to other child
        public sealed override void Move()
        {
            Console.WriteLine("Super Knight Moved");
        }
    }

    class Mage : Player
    {
        public int mp;

        public override void Move()
        {
            Console.WriteLine("Mage Moved");
        }

    }

    class Program
    {
        static void EnterGame(Player player)
        {
            player.Move();
            bool isMage = (player is Mage);
            if (isMage)
            {
                Mage mage = (Mage)player;
                mage.mp = 10;
            }
        }


        static void Main(string[] args)
        {
            Knight knight = new Knight();
            Mage mage = new Mage();

            EnterGame(knight);
            EnterGame(mage);

        }
    }
}
```

---

## String (Character Array)

```c#
using System;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;

namespace CSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            string name = "Harry Potter";

            // 1. Search
            bool foundName = name.Contains("Harry");
            Console.WriteLine(foundName);

            // 2. Find the Index
            // Return -1 if not found
            int index = name.IndexOf('P');

            // 3. Add and Delete
            name = name + "Junior";
            Console.WriteLine(name);

            // 4. Change to lowercase & uppercase
            string lowercase = name.ToLower();
            string uppercase = name.ToUpper();

            // 5. Replace
            string newname = name.Replace('r', 'l');

            // 6. Split
            string[] names = name.Split(new char[] { ' ' });

            // 7. Substring
            string subName = name.Substring(5);

        }
    }
}

```

