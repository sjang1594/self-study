#include <iostream>
using namespace std;

// Initialize list
// 멤버 변수의 초기화 ? 다양한 문법이 존재

// 초기화를 왜 해야되는지..? 귀찮다
// - 버그 예방에 중요
// - 포인터 등 주소값이 연루됭어있는 경우

// 초기화 방법
// 1. 생성자 내에서
// 2. 초기화 리스트
// 3. c++11 문법

// 초기화 리스트
// - 일단 상속 관계에서 원하는 부모를 생성자 호출할때 필요하다
// - 생성자 내에서 초기화 vs 초기화 리스트
// - 일반 변수는 별 차이 없음
// - 멤버 타입이 클래스인 경우 차이가 난다.
// - 정의함과 동시에 초기화가 필요한 경우 (참조 타입, const type)

class Inventory
{
public:
    Inventory() { cout << "Inventory() " << endl;}
    Inventory(int size) { _size = size; }
    ~Inventory(){ cout << "~Inventory() " << endl;}
public:
    int _size = 100;
};

// Is-A (Knight Is-A Player?) Ok --> 상속
// Has-A (Knight Has-A inventory?) Ok --> 포
//
class Player
{
public:
    Player();
    Player(int id) {}
};

class Knight : public Player
{
public:
    Knight : Player(1), _hp(100), _inventory(20), _hpRef(_hp), _hpConst(100)
    {
        /*
         * 선처리 영역
         * _inventory = Inventory()
         * 아래에서 inentory 에 해당되는 클래스를 만들면
         * 선처리영역에서 하나만든이후에 소멸자를 콜하고, 다시 재정의해서 소멸시킨다. --> 않좋음 그래서 위와 같이 한다.
         */
        // or
        // _hp = 100
        //_inventory = Inventory(20)
    }
public:
    int _hp; // 쓰레기 값
    Inventory _inventory;
    int& hpRef;
    const int _hpConst;
    // c++11 에서는
    // int& hpRef = _hp;
    // const int _hpConst = 10  ;
};

int main()
{
    Knight k;
    cout << k._hp << endl;
    return 0;
}
