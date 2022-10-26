#include <iostream>
#include <time.h>
using namespace std;

enum ItemType
{
	IT_WEAPON = 1,
	IT_ARMOR = 2,
};

class Knight
{
public:
	int _hp = 0;	
};


class Item
{
public:
	Item(){cout << "Item()" << endl;}
	Item(int itemType) : _itemType(_itemType) {};
	Item(const Item& item){cout << "Item(const: item&" << endl;}
	~Item(){ cout << "~Item()" << endl;}
	virtual void Test(){cout << "Test Item " << endl;}
public:
	int _itemType = 0;
	int _itemdbid = 0;

	char _dummy[4096] = {};
};

class Weapon : public Item
{
public:
	Weapon() : Item(IT_WEAPON){ cout << " Weapon() " << endl; _damage = rand() % 100 + 1;} 
	~Weapon(){ cout << "~Weapon()" << endl; }
public:
	int _damage = 0;
};

class Armor : public Item
{
public:
	Armor() : Item(IT_ARMOR){ cout << " Armor() " << endl;}
	~Armor(){ cout << " ~Armor() " << endl;}
public:
	int _defence = 0;
};

int main()
{
	// 연관성이 없는 클래스 사이의 포인터 변환 테스트
	{
		// Stack[주소] --> Heap [ _hp(4) ]
		Knight* knight = new Knight();
		
		// 암시적으로는 NO
		// 명시적으로는 OK
		// Stack [주소]
		Item* item = (Item*)knight;
		item->_itemdbid =1 ;

		delete knight;
	}

	// 부모 -> 자식 변환 테스트
	{
		Item* item = new Item();
		// [  [item]  ]
		// [ _damaage ]
		// Weapon* weapon = (Weapon*)item;
		// weapon->_damage = 10;
		delete item;
	}

	// 자식 -> 부모 변환 테스트
	{
		Weapon *weapon = new Weapon();
		// 암시적으로 된다!
		Item* item = weapon;
		delete weapon;
	}

	// 명시적으로 타입 변환할 때는 항상 항상 조심해야 한다!
	// 명시적으로 될 때는 안전하다?
	// -> 평생 명시적으로 타입 변환(캐스팅) 은 안하면 되는거 아닌가?

	Item* inventory[20] = {};
	srand((unsigned int) time(nullptr));
	for (int i=0; i < 20; i++)
	{
		int randValue = rand() % 2; 

		switch(randValue)
		{
			case 0:
			inventory[i] = new Weapon(); 
			break;

			case 1:
			inventory[i] = new Armor();
			break;
		}
	}

	for (int i =0; i < 20; i++)
	{
		Item* item = inventory[i];
		if (item == nullptr)
			continue;

		if (item->_itemType == IT_WEAPON)
		{
			Weapon* weapon = (Weapon*)item;
			cout << "Weapon Damage: " << weapon->_damage <<endl;
		}

	}

	// --------------------- 매우 중요 중요 ---------------------
	for (int i =0; i < 20; i++)
	{
		Item* item = inventory[i];
		if (item == nullptr)
			continue;
		// Weapon 의 소멸자도 호출 해야하는데 ~Item 만 호출된다 그래서..
		// delete item;
		// 자식에 대한 것도 풀어줘야한다.
		if (item->_itemType == IT_WEAPON)
		{
			Weapon* weapon = (Weapon*)item;
			delete weapon;
		}
		else
		{
			Armor *armor = (Armor*)item;
			delete armor;
		}
	}

	// [결론]
	// - 포인터 vs 일반타입 : 차이를 이해하자
	// - 포인터 사이의 타입 변환(캐스팅)을 할 때는 매우 매우 조심해야한다.
	// - 부모-자식 관계에서 부모 클래스의 소멸자에는 까먹지 말고 virtual를 붙이자 ! --> 단골 주제

	return 0;
}
