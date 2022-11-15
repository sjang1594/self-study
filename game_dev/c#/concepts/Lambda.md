# Lambda

한줄로 요약하자면, 일회용 함수를 만드는데 사용하는 문법이다.


```c#
namespace CSharp
{
  enum ItemType
  {
    Weapon,
    Armore,
    Amulet,
    Ring
  }

  enum Rarity
  {
    Normal,
    Uncommon,
    Rare,
  }

  class Item
  {
    public ItemType ItemType
    public Rarity Rarity
  }

  class Program
  {
    static List<Item> _items = new List<item>();

    static Item FindWeapon()
    {
      foreach(Item item in _items)
      {
        if (item.ItemType == ItemType.Weapon)
        return item;
      }
      return null;
    }

    static Item FindRareItem()
    {
      foreach(Item item in _items)
      {
        if(item.Rarity == Raity.Rare)
        return item;
      }
      return null;
    }

    static void Main(string[] args)
    {
      _items.Add(new Item() { ItemType = ItemType.Weapon, Rarity = Rarity.Normal })
      _items.Add(new Item() { ItemType = ItemType.Armore, Rarity = Rarity.Uncommon })
      _items.Add(new Item() { ItemType = ItemType.Ring, Rarity = Rarity.Rare })
    }
  }
}
```

위와 같이 `FindWeapon` 나 `FindRareItem` 을 통해서, foreach 구문을 돌아가서, 내가 찾고자 하는 아이템을 찾아야하는 귀찮은 일들이 벌어진다. 이것을 해결하려면 `delegate` 이라는 keyword 를 사용해야 하는데... 한번 아래와 같이 바꿔보자.

```c#
namespace CSharp
{
  enum ItemType
  {
    Weapon,
    Armore,
    Amulet,
    Ring
  }

  enum Rarity
  {
    Normal,
    Uncommon,
    Rare,
  }

  class Item
  {
    public ItemType ItemType
    public Rarity Rarity
  }

  class Program
  {
    static List<Item> _items = new List<item>();

    delegate bool ItemSelector(Item item)

    static Item FindItem(ItemSelector selector)
    {
      foreach(Item item in _items)
      {
        if(selector(itme))
        return item
      }
      return null;
    }

    static bool isWeapon(Item item)
    {
      return item.ItemType == ItemType.Weapon;
    }

    static Item FindRareItem()
    {
      foreach(Item item in _items)
      {
        if(item.Rarity == Raity.Rare)
        return item;
      }
      return null;
    }

    static void Main(string[] args)
    {
      _items.Add(new Item() { ItemType = ItemType.Weapon, Rarity = Rarity.Normal })
      _items.Add(new Item() { ItemType = ItemType.Armore, Rarity = Rarity.Uncommon })
      _items.Add(new Item() { ItemType = ItemType.Ring, Rarity = Rarity.Rare })

      Item item = FindItem(isWeapon);
    }
  }
}
```

하지만 여기까지, 했을때면 좋다. 하지만 2% 정도 부족하다. 왜 부족 하느냐 ?!?!

- 일단 ItemSelector() 라는 함수를 만들어야 한다.
- 조건을 만들때마다, `isWeapon` 처럼 코드가 늘어난다.

그러면, 더 좋은 조건 또는 룰이 뭐가 있을까? 라고 생각을 해보자. 아래의 코드 segement 부분을 보자

```c#

Item item = FindItem(delegate (Item item){return item.ItemType == ItemType.Weapon})

```
이렇게 된다면, `isWeapon` 함수가 필요 없을 것이다. 이거는 무형함수 / 익명함수(Anonymous Function) 이라고 한다. 이게 초창기의 문법이다.

그렇다면 labmda 를 사용해서 해보자
```c#
static void Main(string[] args)
{
  _items.Add(new Item() { ItemType = ItemType.Weapon, Rarity = Rarity.Normal })
      _items.Add(new Item() { ItemType = ItemType.Armore, Rarity = Rarity.Uncommon })
      _items.Add(new Item() { ItemType = ItemType.Ring, Rarity = Rarity.Rare })

  Item item = FindItem((Item item) => {return item.ItemType == ItemType.Weapon; });
}
```

아래 `Item item = FindItem((Item, item) => {return item.ItemType == ItemType.Weapon;});` 이 부분을 보면, 이게 labmda 식으로 돌아가는것이다.

---

이 코드를 조금 세련되게 만든다고 가정을 하자면,

```c#
class Program
{
  static List<Item> _item = new List<Item>();

  delegate Return ItemSelector<T, Return>(T item);

  static Item FindItem(ItemSelector<Item, bool> selector){}

  static void Main(string[] args){
    //...
    MyFunc<Item, bool> selector = (Item item) => { return item.ItemType == ItemType.Weapon; };
  }
}
```

`delegate Return ItemSelector<T, Return>(T item)` 이 부분을 보자면, delegate type 안에도 generic 형태의 형식을 사용할 수 있다. 일반적으로 사용 할수 있는 `T` 를 사용해서 `Return` 형식으로 반환 할수 있게 선언한다.

하지만 만약 인자가 여러개가 필요하다고 하면, 함수의 overriding 을 사용해서... 예를 들어서 반환이 필요없는 함수를 만든다고 했을때, 이런식으로 만들어주면된다.
`delegate Return ItemSelector<Return>(T item)`

또한 `delegate Return ItemSelector<T1, T2, Return>(T1 t1, T2 t2)`

다른거 comment 를 남길건, delegate 를 직접 선언하지 않아도, 이미 만들어진 애들이 존재한다.
반환 타입이 있을 경우 Func 를 사용하고, 반환 타입이 없으면 Action 을 사용한다.
