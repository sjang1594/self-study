```c#
namesapce CSharp
{
  class Program
  {
    class Monster
    {
      public int id;
      
      Monster(int _id) {this.id = _id}
    }
    
    static void Main(string[] args)
    {
      Dictionary<int, Monster> dic = new Dictionary<int, Monster>();
      
      for (int i = 0; i < 10000; i++)
      {
        dic.Add(i, new Monster(i));
      }
      // Not a good idea 
      // Monster mon = dic[5000];
      
      Monster mon;
      bool found = dicTryGetValue(2000, out mon);
      
      dic.Remove(2000);
      dic.Clear();
    }
  }
}
```

