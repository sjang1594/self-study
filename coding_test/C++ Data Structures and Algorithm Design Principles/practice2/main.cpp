#include <iostream>
#include <list>
#include <vector>

// Card Game Simulation
// Within a card game, there are 4 players. Each player is dealt 13 cards from a standard deck of 52 cards.

struct card
{

};

int main(int argc, char* argv[])
{
    int num_players = 4;
    int num_cards = 13;

    std::list<int> p1(num_cards);
    std::list<int> p2(num_cards);
    std::list<int> p3(num_cards);
    std::list<int> p4(num_cards);


    return 0;
}