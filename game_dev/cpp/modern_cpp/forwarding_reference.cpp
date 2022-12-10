#include <iostream>
using namespace std;

// forwarding reference

class Knight
{
public:
	Knight() { cout << "Knight()" << endl; }
	Knight(const Knight&) { cout << "Knight&" << endl; }
	Knight(Knight&&) noexcept { cout << "Knight&&" << endl; }
};

void Test_RValueRef(Knight&& k) {} // 오른값 참조

void TestCopy(Knight k) {}

// 만약 Test_ForwardingRef(const T&& ) 일때는 전달참조로 작동 되지 않는다.
template<typename T>
void Test_ForwardingRef(T&& param) // 전달 참조
{
	// 왼값 참조라면 복사
	// 오른값 참조라면 이동
	TestCopy(std::forward<T>(param));

	// TODO
	// 왼값 참조라면 복사 
	TestCopy(param);

	// 오른값 참조라면 이동
	TestCopy(std::move(param));
}

// 그럼 만약 template 의 인자가 2 개가 존재 한다면?
// 함수를 다 만들어야되? 구지 그럴 필요 없음

int main()
{
	// universal reference
	// forwarding reference c++17

	// &&  &를 두 번 -> 오른값 참조
	Knight k1;

	Test_RValueRef(std::move(k1)); // rvalue_cast

	Test_ForwardingRef(std::move(k1));
	Test_ForwardingRef(k1); // 통과 되네? 

	// 참조는 참조인데 오른쪽 참조값 / 왼쪽 참조값
	// auto / template 일때 타입이 달라진다.
	auto&& k2 = k1;
	auto&& k3 = std::move(k1);

	// 공통점 : 형식 연역 (type deduction) 이 일어날때
	// 전달 참조를 구별하는 방법
	// ---------------------------------------------


	Knight& k4 = k1; // 왼값 참조
	Knight&& k5 = std::move(k1); // 오른값 참조

	// Test_RValueRef(k4); // 안됨
	// Test_RValueRef(k5); // 이것도 안됨

	// 오른값: 왼값이 아니다 = 단일식에서 벗어나면 사용 X
	// 오른값 참조 : 오른값만 참조할 수 있는 참조 타입

	// k5 의 타입은 오른값 참조이지만, k5 자체는 왼값이다.
	// Test_RValueRef(std::move(k5));


	// ---------------------------------------------
	Test_ForwardingRef(k1);
	Test_ForwardingRef(std::move(k1));

	return 0;
}