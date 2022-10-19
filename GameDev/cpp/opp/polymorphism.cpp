#include <iostream>
using namespace std;

// Polymorphism = 겉은 똑같은데, 기능이 다르게 동작한다.
// - 오버로딩(Overloading) = 함수 중복 정의 = 함수 이름의 재사용
// - 오버라이딩(Overriding) = 재정의 = 부모 class method 를 사용해서 자식클래스에서 재정의

// Binding - 묶는다.
// - 정적 바인딩(static binding) - compiler 시점에 결정
// - 동적 바인딩(dynamic binding) - 실행 시점에 결정

// 일반함수는 정적 바인드를 사용
// 동적 바인딩을 원한다면? --> 가상함수를 사용(virtual function)

// 그런데 실제 객체가 어떤 타입인지 어떻게 알고 있어서 가상함수를 호출해주는걸까?
// - 가상함수 테이블 (vftable)
// .vftable [] 4 바이트(32) 8 바이트(64)
// [VMove] []
// 참고 .vftable cosntructor = 선처리를 통해서, 덮어쓴다.

// 순수 가상함수: 구현은 없고, '인터페이스' 만 전달하는 용도로 사용하고 싶을 경우
// 순수 가상함수를 만들었을 경우, 빌드를 시켰을때, 그 method 가 있는 클래스는 abstract class 가 된다.
// 추상 클래스 (abstract class) : 순수 가상함수가 1개이상 존재 하거나 포함되면 바로 추상 클래스로 간주
// - 직접적으로 객체를 만들수 없게 됨

class Player
{
public:
    Player() {_hp =100 ;}
    // Overloading
    void Move(){cout << "Move" << endl; }
    // -- > void Move(int hp) { cout << "Move (int)" << endl; }
    virtual void VMove() { cout << "VMove" << endl;}
    virtual void VAttack() = 0; // 순수 가상함수
public:
    int _hp;
};

class Knight : public Player
{
public:
    Knight() {_stamina = 100; }
    // Overriding
    void Move(){cout << "Move Knight" << endl;}
    // 가상함수는 재정의를 하더라도 가상함수이다 .
    virtual void VMove() { cout << "VMove Knight" << endl;}
    virtual void VAttack(){cout << "VAttack Knight" << endl;}
public:
    int _stamina;
};

class Mage : public Player
{
public:
    int _mp;
};

void MovePlayer(Player* player)
{
    player->VMove();
}

//void MoveKnight(Knight* knight)
//{
//    knight->Move();
//}

// [ [player] ]
// [  knight  ]
int main()
{
    // Player p; // 추상클래스기때문에 instantiate 할수 없다.
    //MovePlayer(&p); // player is player
    //MoveKnight(&p); // Error --> player is knight

    Knight k;
    //MoveKnight(&k) // Knight is Knight
    // 뭉뚱그려서 관리 해도 된다, 즉 Move Knight 이라는 함수를 작성 안해도 된다.
    //MovePlayer(&p ); // knight is player
    // 일반함수일때 (정적 바인딩일때) Player 를 call 하지만
    // 가상함수일때는 (동적 바인딩 --> virtual) 이기때문에, knight 를 찾아간다. 어떻게??
    return 0;
}
