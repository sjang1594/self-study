#include <iostream>
using namespace std;

// function pointer
// 함수에 대한 타입?
//
int Add(int a, int b)
{
    return a + b;
}

class Item
{
public:
public:
    int _itemId;
    int _rarity;
    int _ownedId;
};

// 중복 적인 조건이 계속 생긴다면 별로 좋지 않다.
// Item* FindItemByItemId(Item item[], int itemCount, int itemId)
// {
//     for (int i=0; i < itemCount; i++)
//     {
//         Item* item = &item[i];
//         if (item->_itemId== itemId)
//             return item;
//     }
//     return nullptr;
// }

bool isRareItem(Item* item, int value)
{
    return item->_rarity >= 2;
}

bool isOwnerItem(Item* item, int ownerId)
{
    return item->isOwnerItem == ownerId;
}

typedef bool(ITEM_SELECTOR)(Item *item, int);

// 동작 또는 조건 별로 함수의 타입을 지정할수 있다.
Item* FindItem(Item item[], int itemCount, ITEM_SELECTOR* selector, int value)
{
    for (int i=0; i < itemCount; i++)
    {
        Item* item = &item[i];
        if (selector(item))
            return item;
        // ToDo 조건
    }

    return nullptr;
}

int main()
{
    int a = 10;
    // 바구니 주소
    // pointer[주소] --> 주소 []

    // 1) pointer
    // 2) variable name --> pointer
    // 3) data type  int
    typedef int DATA
    DATA* pointer = &a;
    // 이 위의 포인터를 타고 가면 함수가 있어요 라는걸 어떻게 표현 할지 ?

    // 함수
    typedef int(FUNC_TYPE)(int, int); // 이런식으로 저장해야 한다.
    //using FUNC_TYPE int(int a, int b); // modern c++

    // 1) pointer
    // 2) variable name _fn
    // 3) data type -> function (parameter:  int, int)
    FUNC_TYPE* _fn;

    // 함수 포인터 개념
    _fn = Add;
    // 함수의 이름은 함수의 시작 주소를 들고 있고, (배열과 유사한 관계)

    int result = _fn(3, 1); // basic one
    cout << result << endl;

    int result = (*_fn)(3, 1) // 함수 포인터는 *(접근 연산자) 붙여도 함수 주소를 뜻함

    Item items[10] = {};
    items[3]._rarity = 2;
    Item* rareItem = FindItem(items, 10, isRareItem(), 0;
    Item* ownedItem = FindItem(items, 10, isOwnerItem, 100);
    return 0;
}
