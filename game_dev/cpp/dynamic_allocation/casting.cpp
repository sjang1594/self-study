#include <iostream>
using namespace std;

// casting
// 1) static_cast
// 2) dynamic_cast
// 3) const_cast
// 4) reinterpret_cast

void PrintName(char* str)
{
    cout << str << endl;
}

class Player
{
public:
    Player(){}
    virtual ~Player(){}
};

class Knight : public Player
{
public:
};

class Archer : public Player
{
public:

};

class Dog
{

};

int main()
{
    // static_cast : 타입 원칙에 비춰볼때, 상식적인 캐스팅만 허용 해준다.
    // 1) int <--> float
    // 2) Player* <--> Knight* (다운 캐스팅)
    int hp = 100;
    int maxHp = 200;
    float ratio = static_cast<float>(hp) / maxHp;

    // 부모 --> 자식, 자식 --> 부모
    // 위험
    Player* p = new Player();
    // downcasting --> 단 안정성 보장 못함
    Knight*k1 = static_cast<Knight*>(p); //Knight* k1 = (Knight*)p;

    // 통과
    Knight k2 = new Knight();
    Player* p2 = static_cast<Player*>(k2); //Player* p2 = k;

    // dynamic_cast : 상속관계에서의 안전 형변환
    // RTT : (RunTime Type Information)
    // 다형성을 활용하는 방식
    // - virtual 함수를 하나라도 만들면, 객체의 메모리에 가상함수 테이블(.vftable) 주소가 기입된다
    // - 만약 잘못된 타입으로 캐스팅 했으면, nullptr 로 반환 ******
    // 이를 이용해서 맞는 타입으로 캐스팅을 했는지 확인이 유용하다.
    Knight k3 = dynamic_cast<Knight*>(p1);

    // const_cast : const 를 붙이거나 때거나 할
    PrintName(const_cast<char*>('Nick')); // c style PrintName((char*) "Nick");

    // reinterpret_cast
    // 가장 위험하고 강력한 형태의 캐스팅
    // - 포인터랑 전혀 관계 없는 다른 타입으로 변환
    __int64 address = reinterpret_cast<int>(k2); // c style (__int64)k2;

    Dog* dog = reinterpret_cast<Dog*>(k2);
    return 0;
}