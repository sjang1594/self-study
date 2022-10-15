#include <iostream>
using namespace std;

// data + manipulation (logic, run)

class Knight
{
public:
    // Member Function
    void Move(int y, int x);
    void Attack();
    // 함수가 정의된곳에 구현부를 추가해도 됨
    void Die(int hp)
    {
        _hp = 0;
        cout << "Die" << endl;
    }

public:
    // Member Variable
    int _hp;
    int _attack;
    int _posX;
    int _posY;
};

// Knight 에 속해있는 함수.
void Knight::Move(int y, int x)
{
    _posY = y;
    _posX = x;
    cout << "Move" << endl;
}

void Move(Knight* knight, int y, int x)
{
    knight->_posX = x;
    knight->_posY = y;
}

void Knight::Attack()
{
    cout << "Attack" << _attack << endl;
}

int main()
{
    // Instantiate
    Knight k1;
    k1._hp = 100;
    k1._attack = 10;
    k1._posX = 0;
    k1._posY = 0;
    
    Move(&k1, 2, 2);

    k1.Move(3, 3);
    k1.Attack();

    Knight k2;
    k2._hp = 80;
    k2._attack = 5;
    k2._posX = 1;
    k2._posY = 1;
    
    return 0;
}