#include "Player.h"
#include "Monster.h"

void Player::KillMonster()
{
    _target->_hp = 0;

    // [주소] --> [[monsterId][_hp][_defence]]
    // 다시 말해서 monster _hp 에 관해서 알고 싶고 변경하고 싶다면
    // include "Monster.h" 가 필요하고 전방선언으로는 알수 없다.

    // 예를 들어서
    _target->KillMyself();
    // (*_target)._hp = 0;
}


