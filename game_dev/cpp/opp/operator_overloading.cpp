#include <iostream>
using namespace std;

// 연산자 오버로딩(Operator Overloading)
// 연산자 vs 함수
// 연산자는 피연산자의 개수/타입이 고정되어있음

// 연산자 오버로딩
// 일단 [연산자 함수]를 정의 해야함
// 함수도 멤버 함수 / 전역 함수가 있는 것처럼, 연산자 함수도 두가지 방식으로 만들수 있음

// 멤버 연산자 함수 -- version
// -- a or b 형태에서 왼쪽으로 기준으로 실행됨 (a 가 클래스여야 가능 a 를 기준 연산자라고함)
// -- 한계) a 가 클래스가 아니면 사용못함

// 전역 연산자 함수
// -- a or b 형태라면 a 와 b 모두를 피연산자로 만들어야 함)

// 언제 사용하냐??
// - 대표적으로 대입 연산자 (a = b)는 전역 연산자로 version 으로 만든다.

// 복사 대입 연산자
// - 대입 연산자가 나온 김에 [복사 대입 연산자]에 대해 알아보자.
// 용어가 조금 헷갈린다. [복사 생성자] [대입 연산자] [복사 대입 연산자]
// - 복사 대입 연산자 = 대입 연산자 중, 자기 자신의 참조 타입을 인자로 받는것

// 기타
// - 모든 연산자를 오버로딩 할수 있는건 아니다.(:: . .* 이런건 안됨)
// - 모든 연산자가 두개의 항이 있는것이 아니다 ++, -- --> 단한 연산자
// - 증감 연산자(++, --) 어떻게 구현 해야하는가?
// - 전위형(++a) operator++()
// - 후위형(a++) operator++(int)

class Position
{
public:
    Position operator+(const Position& arg)
    {
        Position pos;
        pos._x = _x + arg._x;
        pos._y = _y + arg._y;
        return pos;
    }
    Position operator+(int arg)
    {
        Position pos;
        pos._x = _x + arg;
        pos._y = _y + arg;
    }

    bool operator==(const Position &arg)
    {
        return _x == arg._x && _y == arg._y;
    }

    Position& operator=(int arg)
    {
        _x = arg;
        _y = arg;
        return *this;
    }

    // [복사 생성자] [복사 대입 연산자] 등 특별 대우 받는 이유?
    // 말 그대로 객체가 '복사'되길 원하기 특징 때문
    Position& operator=(const Position& arg)
    {
        _x = arg._x;
        _y = arg._y;
        return *this;
    }

    Position& operator++()
    {
        _x++;
        _y++;
        return *this;
    }

    Position operator++(int)
    {
        Position ret = *this;
        _x++;
        _y++;
        return ret;
    }

public:
    int _x;
    int _y;
};

Position operator+(int a, Position &b)
{
    Position ret;
    ret._x = b._x + a;
    ret._y = b._y + a;
    return ret;
}


int main()
{
    Position pos;
    pos._x = 0;
    pos._y = 0;

    Position pos2;
    pos2._x = 1;
    pos2._y = 1;

    // Can't do it
    // this is why you need operator overloading
    Position pos3 = pos + pos2;
    // pos3 = pos.operator+(pos2)

    Position pos4 = pos3 + 3;
    // Position ps4 = 1 + pos3 // 안됨 왼쪽이 클래스여야하며, 기준 대상자여야하기 때문에.. --> 전역함수로

    bool isSame = (pos3==pos2);

    Position pos5;
    pos3 = (pos5 = 5);
    ++(++pos3);

    Position pos6;
    // (Pos&) 를 줘   (pos) 복삿값을 줘
    // --> (const Pos&) 문법적으로 통과
    pos6 = pos3++;
    pos3.operator++(1);

    return 0;
}