#include <thread>
#include <string>
#include <mutex>
#include <iostream>
#include <fstream>
using namespace std;

class LogFile{
  std::mutex _mu;
  ofstream _f;

  public:
    LogFile(){ _f.open("log.txt"); }
    void shared_print(string id, int value){
      //std::lock_guard<mutex> locker_(_mu);
      // Another way to lock
      // std::unique_lock<mutex> locker(_mu);
      std::unique_lock<mutex> locker(_mu, std::defer_lock);
      // do something else

      locker.lock();

      _f << "From " << id << ": " << value << endl;
      locker.unlock();
      // ...
      locker.lock();

      std::unique_lock<mutex> locker2 = std::move(locker);
    }
};
