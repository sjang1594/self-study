#pragma once

// 선언만 하는거
class Monster;

class Player
{
public:
    void KillMonster();
    void KillMonster2();
    // 최대한 이쪽에서는 구현부를 안하는게 좋다.
public:
    int _playerId;
    int _hp;
    int _attack;

    // Monster* _target;
    // 또는
    // class Monter* _target;

    // 만약 pvp 같은게 있다고 한다면 ?
    // Player _target;
    // 뭔가 이상하다, 자기자신의 설계도를 또가지고 있다?
    // 만약에 포인터를 붙인다면
    Player *_target;
};
