#include <iostream>
using namespace std;

// override, final
// override -> C# 에서는 자주 사용되는 문법이다. (반드시)
// final -> 더이상 override 하지 않겠다 라는
class Creature
{
public:
};


class Player : public Creature
{
public:
	// 만약 여기서 override 를 한다고 하면 ? Creature Attack 이라는 애가 없으니까
	// 에러가 뜬다.
	virtual void Attack()
	{
		cout << "Player !" << endl;
	}

	virtual void Defence() {}
};

class Knight : public Player
{
public:
	// virtual 로 작동 하는데 이왕이면, 명시적으로 보여지는게 좋다.
	// 만약 void Attack() const 를 만들었다면 또 다른 signature 자체가 달라진다.

	// override 를 사용하게 된다면, Attack() 이라는 함수가 최초로 선언된게 
	// 부모 또는 부모의 부모라는 힌트를 준다. 
	// 가독성도 좋다.
	virtual void Attack() override
	{
		cout << "Knight !" << endl;
	}

	// 마지막으로 상속 받겠다
	virtual void Defence() final {}

private:
	int _stamina = 100;

	// 오버로딩 (overloading) : 함수 이름의 재사용
	/*void Attack(int a) {}*/
};

// 만약 Knight 라는 Class 를 읽었을때, 과연 최초로 virtual 를 사용하는 곳이 어디인지 모를수도 있다.

int main()
{
	// 재정의 (override)

	Knight* knight = new Knight();
	knight->Attack();

	Player* player = new Knight();
	player->Attack();

	Creature* c = new Knight();
	return 0;
}