# Nullable

```c#
    public static void Main(string[] args)
    {
        // Nullable -> Null + able
        // This variable number can be nullable
        int? number = null;

        //If number is not null, put it into b, otherwise 0.
        int b = number ?? 0;
        Console.WriteLine(b);

        if (number != null)
        {
            int a = number.Value;
            Console.WriteLine(a);
        }

        if (number.HasValue)
        {
            int a = number.Value;
            Console.WriteLine(a);
        }
    }
}
```
```c#
    class Monster
    {
        public int id { get; set; }
    }
    public static void Main(string[] args)
    {
        // Nullable -> Null + able
        Monster monster = null;
        if (monster != null)
        {
            int monster_id = monster.id;
        }

        int? id = monster?.id;
    }
}
```
