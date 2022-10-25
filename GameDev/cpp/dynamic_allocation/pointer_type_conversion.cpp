#include <iostream>
using namespace std;

class Item
{
public:
	Item(){cout << "Item()" << endl;}
	Item(const Item& item){cout << "Item(const: item&" << endl;}
	~Item(){ cout << "~Item()" << endl;}
public:
	int _itemType = 0;
	int _itemObid = 0;

	char _dummy[4096] = {};
};

void TestItem(Item item)
{

}

void TestItemPtr(Item* item)
{

}

int main()
{
	// 복습
	{
		// Stack [ type(4), dbid(4), dummy(4096)] // 생성자 & 소멸자 호출
		Item item;
		// Stack [ 주소(4~8)] --> Heap 주소 [ type(4) dbid(4) dummy(4096)] 
		Item* item2 = new Item();

		TestItem(item);
		TestItem(*item2);

		TestItemPtr(&item);
		TestItemPtr(item2);

		// Memory Leak -> 점점 가용 메모리가 줄어들어서 crash
		delete item2;
	}

	// 배열
	{
		cout << "---------------------------------" << endl;
		// 진짜 아이테이 100 개 있는 것 (스택 메모리에 올라와 있는)
		Item item3[100] = {};

		cout << "---------------------------------" << endl;
		// 아이템이 100 개 있을까요?
		// 아이템을 가르키는 바구니가 100개 실제 아이템은 1개도 없을 수 있음
		Item* item4[100] = {};
	}

	return 0;
}