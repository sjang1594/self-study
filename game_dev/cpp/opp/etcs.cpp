#include <iostream>

using namespace std;

// 1) strcut vs class
// C++ 에서는 struct 나 class나 종이 한 장 차이다.
// struct는 기본접근 지정자가 public 이고, class는 private이다.
// C++ 는 C 언어에서 파생되어 발전했기 때문에, 호환성을 지키고 싶어

// 2) static 변수, static 함수 (static= 정적 = 고정된)
class Marine
{
public:
	void TakeDamage(int damage){ _hp -= damage; }
	static void Test() 
	{	
		// _hp 는 access 할수 없다.
		s_attack = 100;
	}
	int _hp;
	// 모든 마린들이 사용할수 있는.. 공통적인 attack
	static int s_attack; // 설계도 상으로만 존재
};

int Marine::s_attack = 0;

struct TestStruct
{
	int _a;
	int _b;
};

class TestClass
{
	int _a;
	int _b;	
};

class Player
{
public:
	int _id;
};

int GenerateId()
{	
	// 생명주기 : 프로그램 시작/종료(메모리에 항상 올라가 있음)
	// 가시범위 : 

	// 정적 지역 객체
	// 초기화되는게 아니라, 맨처음 `GenerateId` 가 호출될때 초기화되고,
	// 나머지는 계속 싸이게 된다.
	static int s_id = 1;
	return s_id++;
}

int main()
{
	// TestStruct ts;
	// ts._a = 1;


	// TestClass tc;
	// tc._b = 1;

	Marine m1;
	m1._hp = 40;
	// m1.s_attack = 6
	// 명시적으로 표현 static 이라는걸
	Marine::s_attack = 6;

	Marine m2;
	m2._hp = 40;
	m2.s_attack = 6;

	// 마린 공격력 업그레이드 완료! (Academy 에서 업그레이드 끝)
	m1.s_attack = 7;
	m2.s_attack = 7;

	Marine::Test();

	// Stack 에 있는게 아니라, .data 영역에 있다.
	stack int id = 10;
	int a = id;

	return 0;
}
