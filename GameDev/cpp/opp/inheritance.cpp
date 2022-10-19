#include <iostream>
using namespace std;

// Mem
// [ [ player ] ]
// [   knight   ]

// Inheritance
// 생성자(N)/소멸자(1)
// - Knight를 생성하면 -> Player의 생성자? Knight?
// - 그냥 둘다 호출하자
class Player
{
public:
    Player(){ _hp=0; _attack=0, _defence=0; cout << "player constructor" << endl; }
    Player(int hp){ _hp = hp; }
    ~Player(){ cout << "player destructor" << endl; }
    void Move() { cout << "Player " << endl; }
    void Attack() { cout << "Player Attack" << endl; }
    void Die() { cout << "Player Die " << endl; }

public:
    int _hp;
    int _attack;
    int _defence;
};

class Knight : public Player
{
public:
    Knight() {
        /*
         * 선(처리) 영역
         * - 여기서 Player() 생성자 호출
         */
        _stamina=0;
        cout << "Knight Constructor" << endl;
    }
    Knight(int stamina) : Player(100)
    {
        //

        /*
         * 선(처리) 영역
         * - 여기서 Player() 생성자 호출
         */
        _stamina=stamina;
        cout << "Knight Constructor" << endl;
    }
    ~Knight() {cout << "Knight Desturctor" << endl; }
    /*
     * 후처리영역
     * - 여기서 Player() 소멸자 호출
     */
    void Move() { cout << "Knight Move" << endl; }
public:
    int _stamina;
};

class Mage : public Player
{
public:
    int _mp;
};


int main()
{
    Knight k;
    k._hp = 100;
    k._attack = 20;
    k._defence = 10;

    k.Move();   // child move
    k.Player::Move(); // Parent Class 의 Move

    return 0;
}
