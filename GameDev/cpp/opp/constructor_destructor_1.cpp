#include <iostream>
using namespace std;

// Constructor & Destructor
// 클래스에 '소속'된 함수들을 멤버 함수라고 함.
// 이 중에서 굉장히 특별한 함수 2개가 있는데, 바로 [시작] 과 [끝]을 알리는 함수들
// - 시작(탄생) -> 생성자 (여러개 존재 가능)
// - 끝(소멸) -> 소멸자 (오직 1개만 가능)

// [암시적(implicit) 생성자]
// 생성자를 명시적으로 만들지 않으면,
// 아무 인자도 받지 않는 [기본 생성자]가 컴파일러에 의해 자동으로 만들어짐
// --> 그러나 우리가 명시적(Explicit)으로 아무 생성자 하나 만들면,
// 자동으로 만들어지던 [기본 생성자]는 더이상 만들어지지 않음
class Knight
{
public:
    //[1] 기본 생성자, 인자가 있을수도 있고 없을수 있다.
    Knight()
    { 
        cout << "Knight() 기본생성자 called" << endl;
        _hp = 100;
        _attack = 10;
        _posX = 0;
        _posY = 0;
    }

    // 기타 생성자 --> 만약 기본생성자가 없다가, Knight instantiate 하면 기본생성자가 없다고 Error
    Knight(int hp)
    {
        cout << "Knight(int ) called" << endl; 
        _hp = hp;
        _attack = 10;
        _posX = 0;
        _posY = 0;
    }

    //[2] 복사 생성자, 자기 자신의 클래스 참조 타입을 인자로 받음
    // 일반적으로 '똑같은' 데이터를 지닌 객체가 생성되길 기대한다
    Knight(const Knight& knight)
    {
        _hp = knight._hp;
        _attack = knight._attack;
        _posX = knight._posX;
        _posY = knight._posY;
    }
    
    //[3] 소멸자
    ~Knight(){cout << "Knight() 소멸자 called" << endl;}

    void Move(int y, int x);
    void Attack();
    void Die(int hp)
    {
        this->_hp = 0;
        cout << "Die" << endl;
    }

public:
    int _hp;
    int _attack;
    int _posX;
    int _posY;
};

int main()
{
    Knight k1;
    k1._hp = 100;
    k1._attack = 20;
    
    return 0;
}