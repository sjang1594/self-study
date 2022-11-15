#include <iostream>
using namespace std;

const int ROCK = 1;
const int SCISSORS = 2;
const int PAPER = 3;

int main()
{
  int hp = 100;
  int dmg = 100;

  hp -= dmg;
  bool isDead = (hp <= 0); // kill

  if (isDead)
    cout << "You killed the monster" << endl;
  else if (hp <= 20)
    cout << "The monster is running away" << endl;
  else
    cout << "You were killed by the monster" << endl;

  int input = ROCK;
  // Switch Case
  switch(input)
  {
    case ROCK:
      cout << "ROCK" << endl;
      break;
    case PAPER:
      cout << "PAPER" << endl;
      break;
    case SCISSORS:
      cout << "SCISSORS" << endl;
      break;
    default:
      cout << "Not existed" << endl;
      break;
  }

}
