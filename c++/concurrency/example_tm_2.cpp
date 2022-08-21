#include <thread>
#include <string>
#include <mutex>
#include <iostream>
#include <fstream>
using namespace std;

class LogFile {
  std::mutex m_mutex;
  ofstream f;
  public:
    LogFile(){ f.open("log.txt"); }
    void shared_print(string id, int value){
      std::lock_guard<mutex> locker(m_mutex);
      f << "From " << id << ": " << value << std::endl;
    }
    // Never return f to the outside world
    // For example,
    // ofstream& getstream(){ return f; }
    // user will have an opportunity to access f without going through the mutex.
    // Never pass f as an argument to user provided function
    // void processf(void func(ofstream&)) {fun(f);}
    // user defined function `fun` can access to the f.
    // 1. the function can print without going through the lock.
    // 2. it can copy f to the global variable, so that everybody can
    //    access f freely.
    // 3. it can also close f, so that nobody can write into f anymore.
    // Therefore, the resource f is out of control.
};

// STL Container example
class stack {
    int * _data;
    std::mutex _mu;
  public:
    int& pop(); // pops off the item on top of the stack.
    int& top(); // returns the item on the top
    //..
};

void function_1(LogFile& log){
  for(int i=0; i>-100; i--)
  log.shared_print(string("From t1: "), i);
}

// void function_1(stack& st){
//   int v = st.pop();
//   //process(v);
// }

int main(){
  LogFile log;
  std::thread t1(function_1, std::ref(log));
  for (int i=0; i<100; i++)
    log.shared_print(string("From main: "), i);
  t1.join();
  return 0;
}
