#include <iostream>
using namespace std;

// Array
struct StatInfo
{
    int hp;
    int attack;
    int defence;
};

int main()
{
    // 배열의 크기는 상수 이어야 함
    const int monsterCount = 10;
    StatInfo monsters[monsterCount];

    // 배열의 이름은 곧 배열의 시작 주소
    // 정확히는 시작 위치를 가르키는 Type* pointer
    auto WhoAmI = monsters;
    // StatInfo[] (12 bytes) .. * 10
    // monster_0[] --> 첫번째  시작 주소.
    StatInfo* monster_0 = monsters;
    monster_0->hp = 100;
    monster_0->attack = 10;
    monster_0->defence = 10;

    StatInfo* monster_1 = monsters + 1;
    monster_1->hp = 200;
    monster_1->attack = 20;
    monster_1->defence = 2;

    // 포인터와 참조는 자유자재로 변환 가능하다.
    // StatInfo[ ] StatInfo [ ] 주소 [ ]
    // monster_2 [주소]
    StatInfo& monster_2 = *(monsters + 2);
    monster_2.hp = 300;
    monster_2.attack = 30;
    monster_2.defence = 3;

    // data --> temp[] 복사의 의미.
    StatInfo temp = *(monsters + 2);
    temp.hp = 300;
    temp.attack = 30;
    temp.defence = 3;

    for (int i=0; i<monsterCount; i++)
    {
        StatInfo& monster = *(monsters + 2);
        monster.hp = 100 * (i+1);
        monster.attack = 10 * (i+1);
        monster.defence = (i+1);
    }

    // Better Readability Version
    for (int i=0; i<monsterCount; i++)
    {
        monsters[i].hp = 100 * (i+1);
        monsters[i].attack = 10 * (i+1);
        monsters[i].defence = (i*1);
    }

    // Array Initialization
    int number[5] = {}; // 다 0 으로 밀어 버린다.
    int numbers1[10] = {1, 2, 3, 4, 5}; // 10 이라는 사이즈에 만들고, 나머지는 0
    int numbers2[] = {1, 2, 3, 4, 5, 10}; // 데이터 개수만큼 사이즈를 맞춰준다.
  return 0;
}
