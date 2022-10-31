#include <iostream>
using namespace std;
#include "Player.h"
// Forward Declaration

int main()
{
    // Player 는 몇 바이트인지?
    // int 2개 8 바이트

    // sizeof(Monster*) --> 무조건 4 bytes or 8 bytes
    // Player [hp][_attack][ address ]

    Player p1; // 지역변수 (stack)
    Player p2 = new Player(); // 동적 할당 (heap)
    p1._target = p2;

    return 0;
}
