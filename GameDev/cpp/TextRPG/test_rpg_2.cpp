#include <iostream>
using namespace std;

// main
// - Enter Lobby
// -- CreatePlayer
// -- EnterGame
// --- Create Monsters
// --- EnterBattle

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

struct StatInfo
{
    int hp = 0;
    int attack = 0;
    int defence = 0;
};

void EnterLobby();
void PrintMessage(const char* );
void CreatePlayer(StatInfo *);
void PrintStatInfo(const char*, const StatInfo& );
void EnterGame(StatInfo*);
void CreateMonsters(StatInfo monsterInfo[], int);
bool EnterBattle(StatInfo*, StatInfo*);

int main()
{
    srand((unsigned) time(nullptr));
    EnterLobby();
    return 0;
}

void EnterLobby()
{
    while (true)
    {
        PrintMessage("Entering the Lobby");

        // Player!
        StatInfo playerInfo;
        CreatePlayer(&playerInfo);
        PrintStatInfo("player", playerInfo);
        EnterGame(&playerInfo);
    }
}

void PrintMessage(const char* msg)
{
    cout << "***********************" << endl;
    cout << msg << endl;
    cout << "***********************" << endl;
}

void CreatePlayer(StatInfo* playerInfo)
{
    bool ready = false;
    while(ready == false)
    {
        PrintMessage("Creating the Character");
        PrintMessage("[1] Soldier [2] Archer [3] Mage");
        int input;
        cin >> input;

        switch (input)
        {
            case PT_Knight:
                playerInfo->hp = 100;
                playerInfo->attack = 10;
                playerInfo->defence = 5;
                ready = true;
                break;
            case PT_Archer:
                playerInfo->hp = 80;
                playerInfo->attack = 15;
                playerInfo->defence = 3;
                ready = true;
                return;
            case PT_Mage:
                playerInfo->hp = 50;
                playerInfo->attack = 25;
                playerInfo->defence = 1;
                ready = true;
                break;
        }
    }
}

void PrintStatInfo(const char* name, const StatInfo& info)
{
    cout << "***********************" << endl;
    cout << name << " : HP=" << info.hp << " ATT=" << info.attack << " DEF=" << info.defence << endl;
    cout << "***********************" << endl;
}

void EnterGame(StatInfo* playerInfo)
{
    const int monsterCount = 2;
    PrintMessage("Entering the Game");

    while(true)
    {
        StatInfo monsterInfo[monsterCount];
        CreateMonsters(monsterInfo, monsterCount);
        // print the monster info
        for (int i=0; i < monsterCount; i++)
            PrintStatInfo("Monster", monsterInfo[i]);
        PrintStatInfo("Player", *playerInfo);
        PrintMessage("[1] Battle [2] Battle [3] Run Away");
        int input;
        cin >> input;

        if (input == 1 || input == 2){
            int index = input - 1;
            bool victory = EnterBattle(playerInfo, &monsterInfo[index]);
            if (victory == false)
                return;
        }
    }
}

void CreateMonsters(StatInfo monsterInfo[], int count)
{
    for(int i=0; i < count; i++)
    {
        int randValue = 1 + rand() % 3;
        switch (randValue)
        {
            case MT_Slime:
                monsterInfo[i].hp = 30;
                monsterInfo[i].attack = 5;
                monsterInfo[i].defence = 1;
                break;
            case MT_Orc:
                monsterInfo[i].hp = 40;
                monsterInfo[i].attack = 8;
                monsterInfo[i].defence = 2;
                break;
            case MT_Skeleton:
                monsterInfo[i].hp = 50;
                monsterInfo[i].attack = 15;
                monsterInfo[i].defence = 3;
                break;
        }
    }
}
bool EnterBattle(StatInfo* playerInfo, StatInfo* monsterInfo)
{
    while(true)
    {
        int dmg = playerInfo->attack - monsterInfo->defence;
        if (dmg < 0)
            dmg = 0;
        monsterInfo->hp -= dmg;
        if (monsterInfo->hp < 0)
            monsterInfo->hp = 0;
        PrintStatInfo("Monster", *monsterInfo);

        if (monsterInfo->hp == 0)
        {
            PrintMessage("You beat the monster");
            return true;
        }

        dmg = monsterInfo->attack - playerInfo->defence;
        if (dmg < 0)
            dmg = 0;
        playerInfo->hp -= dmg;
        if (playerInfo->hp < 0)
            playerInfo->hp = 0;

        PrintStatInfo("Player", *playerInfo);
        if (playerInfo->hp == 0)
            PrintMessage("Game Over");
            return false;
    }
}