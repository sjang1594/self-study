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
      std::lock(_mu, _mu2);
      // This will tell locker that `_mu` is already locked.
      // tell locker that adapt the ownership of that mutex.
      // Then we need to unlock the mutex when it's out of scope.
      std::lock_guard<mutex> locker(_mu, std::adopt_lock);
      std::lock_guard<mutex> locker2(_mu2, std::adopt_lock);
      _f << "From " << id << ": " << value << std::endl;
    }
    void shared_print2(string id, int value){
      std::lock_guard<mutex> locker(_mu);
      /// ....
    }
    /* Then run other thing
    //{
    //  std::lock_guard<mutex> locker2(_mu2, std::adopt_lock);
    //  _f << "From " << id << ": " << value << std::endl;
    //}
    */
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
