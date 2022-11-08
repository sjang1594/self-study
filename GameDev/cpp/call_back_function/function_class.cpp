#include <iostream>
using namespace std;

void PrintHello()
{
    cout << "Hello World" << endl;
}

void PrintHelloNumber(int number)
{
    cout << number << endl;
}

// 상태를 가질 수 없다는 예시
// _hp 가 100 이라는 상태를 가지고 있다, 하지만 같은 knight 를 가진다고 하더란들, 다른 각기 knight _hp 가 0 일수도 있고 다르다.
class Knight
{
public:
    void AddHp(int addHp)
    {
        _hp += addHp;
    }
private:
    int _hp = 100;
};

// 함수 객체
class Functor
{
public:
    void operator()()
    {
        cout << "Functor Test" << endl;
        cout << _value << endl;
    }

    // 상태가 저장됨
    bool operator()(int num)
    {
        cout << "Functor Test" << endl;
        cout << _value + num << endl;
    }
private:
    int _value = 0;
};

class MoveTask
{
public:
    void operator()()
    {
        cout << "Move Task" << endl;
    }
public:
    int _playerId;
    int _posX;
    int _posY;
};

int main()
{
    // 함수 객체(functor): 함수처럼 동작하는 객체
    // 함수 포인터의 단점
    // 1) 시그니쳐(signature) 가 안맞으면 사용할수 없다.
    // 2) 상태를 가질수 없다.
    // 함수 포인터
    void (*pfunc)(void);
    pfunc = &PrintHello;
    (*pfunc)();
    // pfunc = &PrintHelloNumber //-> 단점의 예

    // ** 함수의 객체란 무엇인가 **
    // [함수처럼 동작]하는 객체
    // 함수처럼 정의 또는 run 을 하려면 () 연산자가 필요하다.
    // () 연산자 오버로딩
    Functor functor;
    functor();
    bool ret = functor(3);

    // MMORPG 에서 함수 객체를 사용하는 예시
    // 클라 <-> 서버
    // 서버 : 클라가 보내준 네트워크 패킷을 받아서 처리
    // ex) 클라: 나 (5, 0) 좌표로 이동 시켜줘
    MoveTask task;
    task._playerId = 100;
    task._posX = 5;
    task._posY = 0;

    // 나중에 여유가 될때 일감을 실행한다. --> command pattern
    task();
    return 0;
}