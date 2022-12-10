#include <iostream>
using namespace std;

// rvalue 참조와 std::move
// core library 만들었을때

class Pet
{

};

class Knight
{
public:
	Knight() { cout << "Knight()" << endl; }
	// 복사 생성자
	Knight(const Knight& knight) { cout << "const Knight&" << endl; }

	// 이동 생성자
	Knight(Knight&& knight)
	{

	}
	~Knight() { if (_pet) delete _pet; }

	// 복사 대입 연산자
	void operator=(const Knight& knight)
	{
		cout << "Operator=(const Knight&)" << endl;
		// 얕은 복사
		// 상대방의 pet 을 공유?
		_hp = knight._hp;
		//_pet = knight._pet;
		// 그래서 공유를 안할려면
		// 깊은 복사 --> cost 가 높을수 있다
		if (knight._pet)
			_pet = new Pet(*knight._pet);
	}
	void PrintInfo() const {} // read-only

	// 이동 대입 연산자
	// knight 를 아무렇게나 사용해
	void operator=(Knight&& knight) noexcept
	{
		cout << "operator=(Knight&&)" << endl;
		// 얕은복사
		_hp = knight._hp;
		_pet = knight._pet;
		// 소유권을 뺏아와서

		knight._pet = nullptr;
	}
public:
	int _hp = 100;
	Pet* _pet;
};

void TestKnight_Copy(Knight knight) { }
void TestKnight_LValueRef(Knight& knight) { }
// 원본을 수정하면 안되! 읽는것만 하락되 
void TestKnight_ConstLValueRef(const Knight& knight) { knight.PrintInfo(); }
// 참조는 참조인데 오른쪽 값을 받는 참조
// 너가 멋대로 해도 되 : 사용이 끝난 이후로, knight 자체는 사용하지 않을꺼야
// 즉 -> 이동 대상이 되!
void TestKnight_RValueRef(Knight&& knight) {}
int main()
{
	// 왼갑(lvalue) vs 오른값(rvalue)
	// - lvalue : 단일식을 넘어서 계속 지속되는 개체
	// - rvalue : lvalue 가 아닌 나머지 (입시 값, 열거형, 람다, i++ 등)
	int a = 3;

	Knight k1;
	TestKnight_Copy(k1);
	// 원본 변화
	TestKnight_LValueRef(k1);
	// const 가 붙지 않은 참조값에 대한 초기값은 lvalue 여야 한다.
	// 임시의 Knight() 값
	// TestKnight_LValueRef(Knight());

	TestKnight_ConstLValueRef(Knight());

	TestKnight_RValueRef(Knight());

	// 원본을 고칠수 있다 
	TestKnight_RValueRef(static_cast<Knight&&>(k1));


	// Test
	Knight k2;
	k2._pet = new Pet();
	k2._hp = 1000;

	Knight k3;
	// [DEBUG]
	// k3 = static_cast<Knight&&>(k2);

	// k2 의 모든것을 다 뺏어와서, k2 를 날려버려 (소유권)
	// 원본은 나려려도 된다 << 는 Hint 를 주는 쪽에 가깝다

	// static_cast 보다는 
	k3 = std::move(k2); // 오른값 참조로 캐스팅
	// std::move 의 본래 이름 후보 중 하나가 rvalue_cast
	// 성능적으로 좋음


	// 포인터는 포인터인데 unique 한 친구
	std::unique_ptr<Knight> uptr = std::make_unique<Knight>();
	// std::unique_ptr<Knight> uptr2 = uptr; // error 
	// 사용하려면
	std::unique_ptr<Knight> uptr2 = std::move(uptr);

	return 0;
}