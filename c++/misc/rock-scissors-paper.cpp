#include <iostream>
using namespace std;

const int ROCK = 1;
const int PAPER = 2;
const int SCISSORS = 3;


int main()
{
  srand(time(0));
  int wins = 0;
  int total = 0;

  while(true)
  {
    cout << "Select Rock(1), Paper(2) Scissors(3)" <<endl;
    cout << "> ";

    if (total == 0){
      cout << "no probability on winning" << endl;
    }
    else{
      int winPercentage = (wins*100) / total;
      cout << "The current winning percentage is : "<< winPercentage << endl;
    }

    int computerValue = 1 + (rand() % 3);
    int input;
    cin >> input;
    if (input == ROCK)
    {
      switch (computerValue)
      {
      case ROCK:
        cout << "ROCK(USER) vs ROCK(USER), You tied";
        total++;
        break;
      case PAPER:
        cout << "ROCK(USER) vs PAPER(COMPUTER), You Lost" << endl;
        total++;
        break;
      case SCISSORS:
        cout << "ROCK(USER) vs SCISSOR(COMPUTER), You Won" << endl;
        wins++;
        total++;
        break;
      }
    }
    else if(input == PAPER)
    {
      switch(computerValue)
      {
        case ROCK:
        cout << "PAPER(USER) vs ROCK(USER), You Won";
        wins++;
        total++;
        break;
      case PAPER:
        cout << "PAPER(USER) vs PAPER(COMPUTER), You tied" << endl;
        total++;
        break;
      case SCISSORS:
        cout << "PAPER(USER) vs SCISSOR(COMPUTER), You Lost" << endl;
        total++;
        break;
      }
    }
    else
    {
      switch(computerValue)
      {
        case ROCK:
        cout << "SCISSOR(USER) vs ROCK(USER), You Lost";
        total++;
        break;
      case PAPER:
        cout << "SCISSOR(USER) vs PAPER(COMPUTER), You Win" << endl;
        wins++;
        total++;
        break;
      case SCISSORS:
        cout << "SCISSOR(USER) vs SCISSOR(COMPUTER), You tied" << endl;
        total++;
        break;
      }
    }
  }
  return 0;
}
