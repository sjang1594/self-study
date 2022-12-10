#include <iostream>
#include <vector>
using namespace std;

// lambda
// 함수 객체를 빠르게 만드는 문법

enum class ItemType
{
	None,
	Armor,
	Weapon,
	Jewelry,
	Consumable
};

enum class Rarity
{
	Common, 
	Rare,
	Unique
};

class Item
{
public:
	Item() {};
	Item(int itemId, Rarity rarity, ItemType type)
		: _itemId(itemId), _rarity(rarity), _type(type)
	{

	}

public:
	int _itemId = 0;
	Rarity _rarity = Rarity::Common;
	ItemType _type = ItemType::None;
};

int main()
{
	vector<Item> v;
	v.push_back(Item(1, Rarity::Common, ItemType::Weapon));
	v.push_back(Item(2, Rarity::Common, ItemType::Armor));
	v.push_back(Item(3, Rarity::Rare, ItemType::Jewelry));
	v.push_back(Item(4, Rarity::Unique, ItemType::Weapon));

	// 람다 = 함수 객체를 손쉽게 만드는 문법
	// 람다 자체로 c++11 에 '새로운' 기능이 들어간 것은 아니다.
	{
		struct IsUniqueItem
		{
			bool operator()(Item& item)
			{
				return item._rarity == Rarity::Unique;
			}
		};
		auto findIt = std::find_if(v.begin(), v.end(), IsUniqueItem());
		if (findIt != v.end())
			cout << "Item ID: " << findIt->_itemId << endl;
	}

	// lambda 이용 version
	{
		//lambda []() {} // 선언 (익명 함수
		//auto isUniqueLambda = [](Item& item) { return item._rarity == Rarity::Unique; }; // lambda expression
		auto findIt = std::find_if(v.begin(), v.end(), [](Item& item) { return item._rarity == Rarity::Unique; });
		if (findIt != v.end())
			cout << "Item ID: " << findIt->_itemId << endl;
	}

	{
		// 클로저 (closure) = 람다에 의해 만들어진 실행 시점 객체
		auto isUniqueLambda = [](Item& item) { return item._rarity == Rarity::Unique; };

		struct FindItemByItemId
		{
			FindItemByItemId(int itemid) : _itemId(itemid){}
			
			bool operator()(Item& item)
			{
				return item._itemId == _itemId;
			}

			int _itemId;
		};

		int itemId = 4;
		auto findItem = std::find_if(v.begin(), v.end(), FindItemByItemId(itemId));
		if (findItem != v.end())
			cout << "Item ID: " << findItem->_itemId << endl;

		// lambda expression
		// [] 캡처(capture) : 함수 객체 내부에 변수를 저장하는 개념과 유사
		// 사진을 찰칵 [캡처] 하듯... 일종의 스냅샷을 찍는다고 이해
		// 기본 캡처 모드 : 값(복사) 방식(=) 참조 방식(&)

		auto findItemById = [=](Item& item) { return item._itemId == itemId; };
		auto findItem2 = std::find_if(v.begin(), v.end(), findItemById);

		// 참조 방식은
		auto findItemById2 = [&](Item& item) { return item._itemId == itemId; };
		// FindItemByItemId struct 안에 있는 모든게 & 참조의 값을 넣어준거나 마찬가지이다.

		itemId = 10; // [Break Point]

		// itmemID 가 10 번으로 바꾸어진다 --> 그래서 못찾는다.
		auto findItem3 = std::find_if(v.begin(), v.end(), findItemById);
		if (findItem3 != v.end())
			cout << "Item ID: " << findItem3->_itemId << endl;

	}

	{
		struct FindItem
		{
			FindItem(int itemId, Rarity rarity, ItemType type)
				: _itemId(itemId), _rarity(rarity), _type(type)
			{

			}
			bool operator()(Item& item)
			{
				return item._itemId == _itemId && item._rarity == _rarity && item._type == _type;
			}

			int _itemId;
			Rarity _rarity;
			ItemType _type;
		};

		auto findItem4 = std::find_if(v.begin(), v.end(), FindItem(4, Rarity::Unique, ItemType::Weapon));
		if (findItem4 != v.end())
			cout << "Item ID: " << findItem4->_itemId << endl;

		// lamda expression
		int itemId = 4;
		Rarity rarity = Rarity::Unique;
		ItemType type = ItemType::Weapon;

		auto findByItem5 = [=](Item& item) {return item._itemId == itemId && item._rarity == rarity && item._type == type; };
		

		// 변수마다 캡처 모드를 지정해서 사용가능 : 값 방식(name), 참조 방식(&name)
		auto findByItem5 = [&itemId, rarity, type](Item& item) {return item._itemId == itemId && item._rarity == rarity && item._type == type; };
		
		// 예를 들어서 도 가능 하다. 즉 마지막 type 만 참조 방식으로
		// [itemId, &type](Item& item) {return item._itemId == itemId && item._rarity == rarity && item._type == type; };
		// C++ 에서는 모든 애들을 참조나 값방식을 지양하라고 권고 했다.
		{
			class Knight
			{
			public:
				auto ResetHpJob()
				{
					auto f = [this]() // f = [=] 는 결국 this 와 같다
					{
						this->_hp = 200;
					};
					return f;
				}
			public:
				int _hp = 100;
			};


			// 딱 이런 상황과 같다
			class Functor
			{
			public:
				Functor(Knight* k) : _knight(k){}

				void operator()() { _knight->_hp - 200; }
			public:
				Knight* _knight;
			};

			Knight* k = new Knight();
			auto job = k->ResetHpJob();
			//delete k; // 소멸됨 --> this pointer 가 날라감 (메모리 오염) 그래서 조심해야된다.
			//job();
		}
	}

	// 
	// [캡처](인자 값) {구현부}
	return 0;
}
