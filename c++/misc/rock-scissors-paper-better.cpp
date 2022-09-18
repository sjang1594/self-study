#include <iostream>
using namespace std;

enum ENUM_SRP
{
  ENUM_ROCK = 1,
  ENUM_SCISSOR,
  ENUM_PAPER
};

// # preprocessing 지시문
// #include <isotream> 이라는 파일을 찾아서 해당 내용을 복붙!
// 1) 전처리 2) 컴파일 3) 링크
// #define DEFINE_ROCK 1

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
    if (input == ENUM_ROCK)
    {
      switch (computerValue)
      {
      case ENUM_ROCK:
        cout << "ROCK(USER) vs ROCK(USER), You tied";
        total++;
        break;
      case ENUM_PAPER:
        cout << "ROCK(USER) vs PAPER(COMPUTER), You Lost" << endl;
        total++;
        break;
      case ENUM_SCISSOR:
        cout << "ROCK(USER) vs SCISSOR(COMPUTER), You Won" << endl;
        wins++;
        total++;
        break;
      }
    }
    else if(input == ENUM_PAPER)
    {
      switch(computerValue)
      {
        case ENUM_ROCK:
        cout << "PAPER(USER) vs ROCK(USER), You Won";
        wins++;
        total++;
        break;
      case ENUM_PAPER:
        cout << "PAPER(USER) vs PAPER(COMPUTER), You tied" << endl;
        total++;
        break;
      case ENUM_SCISSOR:
        cout << "PAPER(USER) vs SCISSOR(COMPUTER), You Lost" << endl;
        total++;
        break;
      }
    }
    else
    {
      switch(computerValue)
      {
        case ENUM_ROCK:
        cout << "SCISSOR(USER) vs ROCK(USER), You Lost";
        total++;
        break;
      case ENUM_PAPER:
        cout << "SCISSOR(USER) vs PAPER(COMPUTER), You Win" << endl;
        wins++;
        total++;
        break;
      case ENUM_SCISSOR:
        cout << "SCISSOR(USER) vs SCISSOR(COMPUTER), You tied" << endl;
        total++;
        break;
      }
    }
  }
  return 0;
}
