#include <iostream>
using namespace std;

// 오늘의 주제 : 얕은 복사 vs 깊은 복사

class Pet
{
public:
	Pet(){cout << "Pet()" << endl;}
	~Pet(){cout << "~Pet()"<<endl;}
	Pet(const Pet& pet){cout<<"Pet(const Pet& pet)"<<endl;}
};


// Pet 을 포인터로 들고 있는 이유는, 만약 스택에 있는 거라면, Knight 가 생성 될때나 소멸될때 같이 생성과 소멸을 한다라는 점과
// Pet 이 방대한 data 를 들고 있다고 한다면 Knight 자체에 되게 많은 데이터를 가지고 있을수 있다.
class Knight
{
public:
	Knight(){};
	Knight(const Knight& knight)
	{
		_hp = knight._hp;
		_pet = new Pet(*(knight._pet));
	}
	Knight& operator=(const Knight& knight)
	{
		_hp = knight._hp;
		_pet = new Pet(*(knight._pet));
		return *this;
	}
	
	~Knight(){};

public:
	int _hp = 100; // c++11
	Pet* _pet; 
};


int main()
{
	Pet* pet = new Pet();

	Knight knight; // 기본생성자
	knight._hp = 200;
	knight._pet = pet;

	Knight knight2 = knight; // 복사 생성자 개입
	// Knight knight3(knight);

	Knight knight3;
	knight3 = knight; // 복사 대입연산자

	// [복사 생성자] & [복사 대입 연산자]
	// 둘 다 안 만들어주면 컴파일러 '암시적으로' 만들어준다.


	// 중간 결론) 컴파일러가 알아서 잘 만들어준다?
	// 수고하세요~ 다음 주제로 넘어 갈까요? << NO

	// [ 앝은 복사 Shallow Copy ]
	// 멤버  데이터를 비트열 단위로 '똑같이' 복사 (메모리 영역 값을 그대로 복사)
	// 포인터는 주소값 바구니 -> 주소값을 똑같이 복사 -> 동일한 객체를 가르키는 상태가 됨
	// Stack : Knight1 [ _hp, 0x1000(pet 주소)] --> Heap 0x1000 Pet[   ] 
	// Stack : Knight2 [ _hp, 0x1000(pet 주소)]
	// Stack : Knight3 [ _hp, 0x1000(pet 주소)]
	// Knight1 과 Knight2 가 똑같이 Pet 을 가르키고 있다.

	// 그말은 즉 triple pet.. 
	// Pet* pet = new Pet()
	// delete pet 
	// delete pet
	// delete pet 

	// [ 깊은 복사 deep Copy ]
	// 멤버 데이터가 참주(주소) 값이라면, 데이터를 새로 만들어준다 (원본 객체가 참조하는 대상까지 새로 만들어서 복사)
	// 포인터는 주소값 바구니 -> 새로운 객체를 생성 -> 상이한 객체 가르키는 상태가 됨	
	// Stack : Knight1 [ _hp, 0x1000(pet 주소)] --> Heap 0x1000 Pet[   ] 
	// Stack : Knight2 [ _hp, 0x2000(pet 주소)] --> Heap 0x2000 Pet[   ] 
	// Stack : Knight3 [ _hp, 0x3000(pet 주소)] --> Heap 0x3000 Pet[   ] 

	// 실험 ) 
	// - 암시적 복사 생성자 Steps
	// 1) 부모 클래스의 복사 생성자 호출
	// 2) 멤버 클래스의 복사 생성자 호출
	// 3) 멤버가 기본 타입일 경우 메모리 복사 (Shallow Copy)

	// - 명시적 복사 생성자 Steps --> 모든걸 Control 해야 한다.
	// 1) 부모 클래스의 기본 생성자 호출
	// 2) 멤버 클래스의 기본 생성자 호출
	// Knight(const Knight &knight) : Player(knight), _pet(knight._pet)
	//
	// - 암시적 복사 대입 연산자 Steps
	// 1) 부모 클래스의 복사 생성자 호출
	// 2) 멤버 클래스의 복사 생성자 호출
	// - 명시적 복사 대입 연산자 Steps
	return 0;
}