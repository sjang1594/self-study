#include "Game.h"
#include <iostream>
#include "Player.h"
#include "Field.h"
using namespace std;

// namespace Nick
// {
// 	class Test();
// }

Game::Game() : _player(nullptr), _field(nullptr)
{
	//Nick::Test();
}

Game::~Game()
{	
	if (_player != nullptr)
		delete _player;
	if (_field != nullptr)
		delete _field;
}

void Game::Init()
{
	_field = new Field();

}

void Game::Update()
{
	// 매 frame 마다 수행
	if (_player == nullptr)
		Game::CreatePlayer();

    if (_player->isDead())
    {
        delete _player;
        _player = nullptr;
        CreatePlayer();
    }
	_field->Update(_player);

}

void Game::CreatePlayer()
{
	while(_player == nullptr)
	{
		std::cout << "---------------------------" << std::endl;
		std::cout << " 		Create Player 		 " << std::endl;
		std::cout << "1) Knight 2) Archer 3) Mage" << std::endl;
		std::cout << "---------------------------" << std::endl;
		cout << "> ";
		int input = 0;
		cin >> input;

		if (input == PT_Knight)
		{
			_player = new Knight();
		}
		else if (input == PT_Archer)
		{
			_player = new Archer();
		}
		else if (input == PT_Mage)
		{
			_player = new Mage();
		}

	}
}