#include <iostream>
using namespace std;

// Encapsulation (Data Hiding)
// 몰라도 되는 것은 깔끔하게 숨기겠다!
// 숨기는 이유?
// - 1) 정말 위험하고 건드리면 안되는 경우
// - 2) 다른 경로로 접근하길 원하는 경우

// 자동차
// - Handle
// - Pedal
// - Engine
// - Various Wire
// - Door

// 일반 구매자 입장에서 사용하는 것?
// - Handle/Pedal/Door
// 몰라도됨 (오히려 건드리면 큰일 남)
// - 엔진, 각종 전기선

// public / protected / private
// - public     : 누구한테나 실컷 사용하세요
// - protected  : 나의 자손들한테만 허락
// - private    : 나만 사용할께 << class Car 내부에서만

// 상속 접근 지정자: 다음 세대한테 부모님의 유산을 어떻게 물려줄지?
// 부모님한테 물려받은 유산을 꼭 나의 자손들한테도 독같이 물려줘야 하지 않음
// - public     : 공개적으로 상송? 부모님의 유산 설계 그대로 ~ (public -> public, protected -> protected)
// - protected  : 보호받은 상속? 내 자손들한테만 물려줄꺼야 (pubic -> protected, protected -> protected)
// - private    : 개인적인 상속? 나까지만 잘쓰고 -> 자손들에게 아예 안물려줄꺼야 (public->private, protected->private)

class Car
{
public: // 접근 지정자
    void MoveHandle() {}
    void PushPedal() {}
    void OpenDoor() {}

    void TurnKey(){ RunEngine(); }

protected:
    void DisassembleCar() {}
    void RunEngine() {}
    void ConnectCircuit() {}
};

class SuperCar : public Car // 상속 접근 지정자
{
public:
    void PushRemoteController(){ RunEngine(); }
};

// 내부에서는 잘사용된다.
class SuperSuperCar : private Car
{
public:
    void PushRemoteController(){ RunEngine(); }
};

// 만약 상속 접근 지정자를 안했을 경우 private 으로 인식한다.
class TestSuperSuperCar : public SuperSuperCar
{
    public:
    void Test()
    {
        // .. DisassembleCar(); // Can't do it
    }
};

// "캡슐화"
// 연관된 데이터와 함수를 논리적으로 묶어 놓은것

class Berserker
{
public:
    int GetHp() { return _hp; }
    void SetHp(int hp)
    {
        _hp = hp;
        if (_hp <= 50) SetBerserkerMode();
    }

private:
    int _hp = 100;
    void SetBerserkerMode(){ cout << "Getting Stronger" << endl; }
};

int main()
{
    Car car;
    // Nooooo, User is not supposed to disassembe
    TestSuperSuperCar Testcar;
    Testcar.PushRemoteController();

    Berserker berserker;
    berserker.SetHp(20);
    return 0;
}
