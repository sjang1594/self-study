#include <iostream>
using namespace std;

// TextRPG
enum PlayerType
{
  PT_Knight = 1,
  PT_Archer = 2,
  PT_Mage = 3,
};

enum MonsterType
{
  MT_Slime = 1,
  MT_Orc = 2,
  MT_Skeleton = 3,
};

struct ObjectInfo
{
  int type;
  int hp;
  int attack;
  int defence;
};

ObjectInfo playerInfo;
ObjectInfo MonsterInfo;

void EnterLobby();
void SelectPlayer();
void EnterField();
void CreateRandomMonster();
void EnterBattle();

int main()
{
  srand(time(0));
  EnterLobby();
  return 0;
}

void EnterLobby()
{
  while(true)
  {
    cout << "----------------------------" << endl;
    cout << "--------Enter Lobby!--------" << endl;
    cout << "----------------------------" << endl;

    SelectPlayer();

    cout << "---------------------------------" << endl;
    cout << "(1) Enter the field, (2) End Game" << endl;
    cout << "---------------------------------" << endl;

    int input;
    cin >> input;

    if(input == 1)
    {
      EnterField();
    }
    else
    {
      return;
    }
  }
}

void SelectPlayer()
{
  while(true){
    cout << "----------------------------" << endl;
    cout << "Select the Characeter's Job!" << endl;
    cout << "----------------------------" << endl;
    cout << "(1) Knight (2) Archer (3) Mage" << endl;
    cout << "> ";
    cin >> playerInfo.type;

    if (playerInfo.type == PT_Knight)
    {
      cout << "Creating the Knight...!" << endl;
      playerInfo.hp = 150;
      playerInfo.attack = 10;
      playerInfo.defence = 5;
      break;
    }
    else if (playerInfo.type == PT_Archer)
    {
      cout << "Creating the Archer...!" << endl;
      playerInfo.hp = 100;
      playerInfo.attack = 15;
      playerInfo.defence = 3;
      break;
    }
    else if (playerInfo.type == PT_Mage)
    {
      cout << "Creating the Mage...!" << endl;
      playerInfo.hp = 80;
      playerInfo.attack = 25;
      playerInfo.defence = 0;
      break;
    }
  }
}

void EnterField()
{
  while(true)
  {
    cout << "----------------------------" << endl;
    cout << "--------Enter Field!--------" << endl;
    cout << "----------------------------" << endl;
    cout << "[PLAYER] HP: "<< playerInfo.hp << " / ATT: " << playerInfo.attack << " / DEF: " << playerInfo.defence << endl;

    CreateRandomMonster();
    cout << "------------------" << endl;
    cout << "(1) Battle (2) Run" << endl;
    cout << "------------------" << endl;
    cout << ">";
    int input;
    cin >> input;
    if (input == 1)
    {
      EnterBattle();
      if (playerInfo.hp == 0)
        return;
    }
    else{
      return;
    }
  }
}

void CreateRandomMonster()
{
  // 1 - 3
  MonsterInfo.type = 1 + (rand() % 3);
  switch(MonsterInfo.type)
  {
    case MT_Slime:
    cout << "Spawning Slime ..! (HP:15 / ATT:5 /DEF:0)"<<endl;
    MonsterInfo.hp = 15;
    MonsterInfo.attack = 5;
    MonsterInfo.defence = 0;
    break;

    case MT_Orc:
    cout << "Spawning Orc ..! (HP:40 / ATT:10 /DEF:3)"<<endl;
    MonsterInfo.hp = 40;
    MonsterInfo.attack = 10;
    MonsterInfo.defence = 3;
    break;

    case MT_Skeleton:
    cout << "Spawning Skeleton ..! (HP:80 / ATT:15 /DEF:5)"<<endl;
    MonsterInfo.hp = 80;
    MonsterInfo.attack = 15;
    MonsterInfo.defence = 5;
    break;
  }
}

void EnterBattle()
{
  while(true)
  {
    int damage = playerInfo.attack - MonsterInfo.defence;
    if (damage < 0)
      damage = 0;

    MonsterInfo.hp -= damage;
    if (MonsterInfo.hp < 0)
      MonsterInfo.hp = 0;

    cout << "The Monster's HP" << MonsterInfo.hp << endl;
    if (MonsterInfo.hp==0)
    {
      cout << "The monster was killed!" <<endl;

      return;
    }

    damage = MonsterInfo.attack - playerInfo.defence;
    if (damage < 0)
      damage = 0;

      playerInfo.hp -= damage;
      if (playerInfo.hp < 0)
        playerInfo.hp = 0;

      cout << "The Player's HP " << playerInfo.hp << endl;
      if (playerInfo.hp == 0)
      {
        cout << "The Player was Killed... GameOver" << endl;
        return;
      }
  }
}
