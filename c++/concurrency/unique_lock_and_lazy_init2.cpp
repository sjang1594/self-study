#include <thread>
#include <string>
#include <mutex>
#include <iostream>
#include <fstream>
using namespace std;

class LogFile{
  std::mutex _mu;
  std::mutex _mu_open;
  ofstream _f;

  public:
    LogFile(){ _f.open("log.txt"); }
    void shared_print(string id, int value){
      {
        if (!_f.is_open()){
          std::unique_lock<mutex> locker2(_mu_open);
          _f.open("log.txt");
        }
      }

    }
};
