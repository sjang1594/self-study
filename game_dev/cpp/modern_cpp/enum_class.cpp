#include <iostream>
#include <vector>

// modern c++11
// enum class (scoped enum)
// 1) 이름공간 관리 (scoped)
// 2) 암묵적인 변환 금지

// 고전적인 enum 은 enum 값 안에 있는 enum 값들이 전역으로 퍼져있다.
// 이런것을 unscoped enum 이라고 칭한다.
enum PlayerType_Unscoped
{
    Knight,
    Archer,
    Mage,
};

// 그래서 안겹치도록 PT 를 할 필요가 있었다
enum PlayerType : char
{
    PT_Knight,
    PT_Archer,
    PT_Mage,
};

enum PlayerType1
{
    PT_Knight,
    PT_Archer,
    PT_Mage,
};

// enum class -> modern cpp
enum class ObjectType
{
    Player,
    Monster,
    Projectile,
};

using namespace std;

int main()
{
    // 기본적으로 int size 로 잡힌다
    cout << sizeof(PlayerType) << endl;
    return 0;
}