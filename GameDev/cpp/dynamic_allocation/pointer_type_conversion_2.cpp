#include <iostream>
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
	Item(int itemType) : _itemType(_itemType);
	Item(const Item& item){cout << "Item(const: item&" << endl;}
	~Item(){ cout << "~Item()" << endl;}
public:
	int _itemType = 0;
	int _itemdbid = 0;

	char _dummy[4096] = {};
};

class Weapon : public Item
{
	Weapon(){ _itemType}
	~Weapon(){}
};

class Armor : public Item
{
	Armor(){}
	~Armor(){}
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
	return 0;
}
