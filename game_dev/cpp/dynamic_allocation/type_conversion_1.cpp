#include <iostream>
using namespace std;

// 타입 변환
//malloc -> void*을 반환하고, 이를 우리가 (타입 변환)을 통해 사용했었음

class Knight
{
public:
	int _hp = 10;
};

class Dog
{
public:
	Dog(){}
	Dog(const Knight& knight){ _age = knight._hp;}

	// 타입 변환 연산
	operator Knight()
	{
		return (Knight)(*this);
	}
public:
	int _age = 1;
	int _cuteness = 2;
};

class BullDog : public Dog
{
public:
	bool _french; // French bulldog
}

int main()
{	
	// ---------- 타입 변환 유형 (비트열 재구성 여부) ------
	// [1] 값 타입 변환
	// 특징) 의미를 유지하기 위해서 원본 객체와 다른 비트열 재구성
	{
		int a = 123456789; // 2 의 보수
		float b = (float) a; // 부동 소수점 (지수 + 유효 숫자)
		cout << b << endl;
	}

	// [2] 참조 타입 변환
	// 특징) 비트열을 재구성하지 않고, '관점'만 바꾸는것
	// 거의 쓸일은 없지만, 포인터 타입변환도 '참조타입변환' 
	// 동일한 룰을 따르니까 일석 이조로 공부하자
	{
		int a = 123456789; // 2 의 보수
		float b = (float&)a; // 부동소주점(지수 + 유효숫자)
		cout << b << endl;
	}

	// ------------ 안전도 분류 ------------
	// [1] 안전한 변환
	// 특징) 의미가 항상 100% 완전히 일치하는 경우
	// 같은 타입이면서 크기만 더 큰 바구니로 이동
	// 작은 바구니 -> 큰바구니로 이동 OK (upcasting)
	// ex) char -> short, short-> int, int ->__int64
	{
		int a = 123456789;
		__int64 b = a;
		cout << b << endl;
	}

	// [2] 불안전한 변환
	// 특징) 읨가ㅏ 항상 100% 일치한다고 보장 하지 못하는 경우
	// 타입이 다르거나 
	// 같은 타입이자만 큰 바구니 -> 작은 바구니 이동 (down casting)
	// 데이터 손실.. 
	{
		int a = 123456789;
		float b = a;
		short c = a;
	}

	// ------------ 프로그래머 의도에 따라 분류 ------------

	// [1] 암시적 변환
	// 특징) 이미 알려진 타입 변환 규칙에 따라서 컴파일러 '자동'으로 타입 변환
	{
		int a = 12345689;
		float b = a; //암시적으로 
	}

	// [2] 명시적 변환
	{
		int a = 12345689;
		int *b = (int*)a; // 명시적
		cout << b << endl; 
	}

	// ------------ 아무런 연관 관계가 없는 클래스 사이의 변환 ------------
	// [1] 연관 없는 클래스 사이의 '값 타입' 변환
	// 특징) 일반적으로 안됨 (예외: 타입 변환 생성자, 타입 변환 연산자 )
	{
		Knight knight;
		Dog dog = (Dog)knight; //
		Knight knight2 = dog; 
	}

	// [2] 연관없는 클래스 사이의 참조 타입 변환
	// 특징) 명시적으로는 OK
	{
		Knight knight;
		// 어셈블리  : 포인터 = 참조

		// [ 주소 ] -> [ Dog ]
		Dog& dog = (Dog&)knight;
		dog._cuteness = 12;
	}

	// ------------ 상속 관계에 있는 클래스 사이의 변환 ------------
	// 특징) 자식->부모 OK / 부모->자식 NO
	// [1] 상속 관계 클래스의 값 타입 변환
	{
		//Dog dog;
		//BulllDog bulldog = dog; // 이건 불가능 

		BullDog bulldog;
		Dog dog = bulldog; // 이건 가능
	}

	// [2] 상속 관게 클래스의 참조 타입 변환
	{
		//Dog dog;
		//BullDog& bulldog = (BullDog&) dog;

		BullDog bulldog;
		Dog& dog = bulldog; // 안전하게 통과
	}

	// 결론)
	// [값 타입 변환] : 진짜 비트열도 바꾸고 -> 논리적으로 말이 되게 바꾸는 변환
	// - 논리적으로 말이 된다 (ex BullDog -> Dog) Ok
	// - 논리적으로 말이 안 된다 (ex Dog -> BulllDog, Dog -> Knight) 안됨
	// [참조 타입 변환] : 비트열은 냅두고 우리의 '관점'만 바꾸는 변환
	// - 땡강 부리면(명시적 요구) 해주긴 하는데, 말 안해도 '그냥' (암시적)으로 해주는지는 안정선 여부를 연관 있음
	// -- 안전하다? (ex BullDog -> Dog&) '그냥' (암시적으로) Ok
	// -- 위험하다? (ex Dog -> BullDog&)
	// -- 메모리 침범 위험이 있는 경우는 '그냥' (암시적으로) 해주진 않음 (위험하니까)
	// -- 명시적으로 정말 정말 하겠다고 최종 서명을 하면 OK
	return 0;
}