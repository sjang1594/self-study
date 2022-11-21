#include <iostream>
using namespace std;

// Pointer Practice - Text RPG

struct StatInfo
{
	int hp; // +0 
	int attack; // +4
	int defence; // +8
};

void EnterLobby();
StatInfo CreatePlayer();
void CreateMonster(StatInfo* info);
bool StartBattle(StatInfo* player, StatInfo* monster);

int main()
{
	EnterLobby();
	return 0;
}

void EnterLobby()
{
	cout << "Enter the Lobby" << endl;
	
	StatInfo player;
	player = CreatePlayer();
	StatInfo monster;
	CreateMonster(&monster);
	bool victory = StartBattle(&player, &monster);
	
	if (victory)
		cout << "Victory" << endl;
	else
		cout << "Lost" << endl;
}

StatInfo CreatePlayer()
{
	StatInfo ret;
	
	cout << "Create the Player" << endl;
	ret.hp = 100;
	ret.attack = 10;
	ret.defence = 2;
	return ret;
}

void CreateMonster(StatInfo* info)
{
	cout << "Create the Moster" << endl;
	info->hp = 40;
	info->attack = 8;
	info->defence = 1;
}

bool StartBattle(StatInfo* player, StatInfo* monster)
{
	while (true)
	{
		int damage = player->attack - monster->defence;
		if (damage < 0)
			damage = 0;

		monster->hp -= damage;
		if (monster->hp < 0)
			monster->hp = 0;

		cout << "Monster HP: " << monster->hp << endl;
		
		if (monster->hp == 0)
			return true;

		damage = monster->attack - player->defence;
		if (damage < 0)
			damage = 0;

		cout << "Player HP: " << player->hp << endl;

		player->hp -= damage;
		if (player->hp < 0)
			player->hp = 0;

		if (player->hp == 0)
			return false;
	}
}