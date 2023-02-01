#include "Creature.h"

void Creature::OneAttacked(Creature *attacker)
{
    int damage = attacker->_attack - _defence;
    if (damage < 0)
        damage = 0;
    _hp -= damage;
    if(_hp < 0)
        _hp = 0;
}