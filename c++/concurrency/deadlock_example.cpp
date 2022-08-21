#include <thread>
#include <string>
#include <mutex>
#include <iostream>
#include <fstream>
using namespace std;

class LogFile {
  std::mutex _mu; // security reason
  std::mutex _mu2; // file system reason
  ofstream _f;
  public:
    LogFile(){ _f.open("log.txt"); }
    void shared_print(string id, int value){
      std::lock_guard<mutex> locker(_mu);
      std::lock_guard<mutex> locker2(_mu2);
      _f << "From " << id << ": " << value << std::endl;
    }
    void shared_print2(string id, int value){
      std::lock_guard<mutex> locker2(_mu2);
      std::lock_guard<mutex> locker(_mu);
      _f << "From " << id << ": " << value << std::endl;
    }
};

void function_1(LogFile& log){
  for(int i=0; i>-100; i--)
  log.shared_print(string("From t1: "), i);
}

int main(){
  LogFile log;
  std::thread t1(function_1, std::ref(log));
  for (int i=0; i<100; i++)
    log.shared_print2(string("From main: "), i);
  t1.join();
  return 0;
}
