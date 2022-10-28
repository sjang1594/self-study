#include "Field.h"
#include <cstdlib>
#include "Creature\Monster.h"
#include "Creature\Player.h"

Field::Field() : _monster(nullptr)
{

}

Field::~Field()
{
	if (_monster != nullptr)
		delete _monster;
}

void Field::Update(Player* player)
{
	if (_monster == nullptr)
		CreateMonster();
}

void Field::CreateMonster()
{
	int randValue = 1 + rand() % 3;
	switch(randValue)
	{
		case MT_SLIME:
			_monster = new Slime();
			break;
		case MT_ORC:
			_monster = new Orc();
			break;
		case MT_SKELETON:
			_monster = new Skeleton();
			break;
	}

}

void Field::StartBattle(Player *player)
{
	while(true)
	{
		
	}
}