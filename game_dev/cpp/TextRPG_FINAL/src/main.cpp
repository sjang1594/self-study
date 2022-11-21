#include <iostream>
#include "Game.h"
using namespace std;

int main()
{

	srand((unsigned int) time(nullptr));

	Game game;
	game.init();

	while(true)
	{
		game.Update();
	}

	return 0;
}