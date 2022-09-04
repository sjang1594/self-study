#include <thread>
#include <string>
#include <mutex>
#include <iostream>
#include <fstream>
using namespace std;

class LogFile{
  std::mutex _mu;
  std::once_flag _flag;
  ofstream _f;

  public:
    LogFile(){ _f.open("log.txt"); }
    void shared_print(string id, int value){
      std::call_once(_flag, [&](){_f.open("log.txt"); }) // file will be opened only once by one thread
    }
};
