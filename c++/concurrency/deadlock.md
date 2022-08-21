# Concurrent Programming 4


## Source Code
deadlock.cpp

### Deadlock

```
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

```
If you run this code, the fileout won't print all the way up to 100 on `log.txt`, which means that the process hung somewhere.

The t1 locks the mutex `_mu` before t1 go ahead and lock the `_mu2`, and the main thread locks the `_mu2`. So, t1 is waiting for main thread to release the `_mu2`, and the main thread is waiting for t1 to release `_mu`. This situation is called the deadlocks.

To avoid the deadlocks, everybody is locking the mutexes on the same order like code below.

```
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
      std::lock_guard<mutex> locker(_mu);
      std::lock_guard<mutex> locker2(_mu2);
      _f << "From " << id << ":#include <thread>
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
      std::lock_guard<mutex> locker(_mu);
      std::lock_guard<mutex> locker2(_mu2);
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
 " << value << std::endl;
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

```

The C++ library provides a better solution using `std::lock()`.
This will lock arbitrary number of lockable object, such as mutex using certain deadlock avoidance algorithm.

In order to avoid the deadlock
1. Prefer locking single mutex.
