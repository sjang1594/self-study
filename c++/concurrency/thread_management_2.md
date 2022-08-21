# Concurrent Programming 3


## Source Code
thread_management_2.cpp
example_tm_2.cpp

### Data Race and Mutex
In stiuation like two threads are running together, two threads are racing for the common ressource (such as cout).

```
void function_1(){ cout ... }

int main(){ cout ...}
```

The outcome of a program depends on the relative execution order of one or more threads and typically the race condition is not good for the regular program. Avoid as possible as you can.

One way to solve or avoid this race condition is using mutex to synchronize the access of the common resource. In this case, the example would be `cout` statement.

Using the mutex, the `cout` statement on code above won't conflict to each other. In otherword, the mutex will lock and print one `cout` statement and it will unlock the mutex so that the other thread can lock the mutex, and print their message. Now the access of the common resource `cout` is synchronized with the mutex. It should never happend that two threads are using the `cout` statement at the same time.

But, what if there are error occured in the `cout` statement, the mutex is locked forever. So, it is not recommended not to use the mutex lock and unlock function directly. Instead, it is better to use keyword `lock_guard <std::mutex>`, which is resource aqusition is initialization. (So, called RAII). Whenever the guard is out of scope, the mutex, `mu` will always unlock.

There is a problem with the code below, the `cout` is not completely protected by the mutex because `cout` is a global variable so that the other function can easily access or use `cout` directly. This means that the function, `cout` must be protected by the mutex.

```
void shared_print(string msg, int id){
  std::lock_guard<std::mutex> guard(mu);
  cout << msg << id << endl;
}
---

More realistic example would be follwing;
```
#include <thread>
#include <string>
#include <mutex>
using namespace std;

class LogFile{
  std::mutex m_mutex;
  ofstream f;

  public:
    LogFile(){
      f.open("log.txt");
    } // Need destructor to close file
    void shared_print(string id, int  value){
      std::lock_guard<mutex> locker(m_mutex);
      f << "From" << id << ": " << value << endl;
    }
};


```

Look at the following code below, we have an STL example below. The code below is not safely protected by the mutex. Assuming that this code is running, the first element that pops will do process twice, which means that this is more operation problem such as this is what we are not intended to. Instead of seperating the top, pop and process, we can merge top and pop process just like pop and top fucntion returns at the same time as it pops the element.

```
class stack {
  int * _data;
  std::mutex _mu;

  public:
    void pop();
    int& top();
};

void function_1(stack&st){
  int v = st.top();
  st.pop();
  process(v);
}

```

To avoid the data race, couping things we can do.
1. Use mutex to synchronize the data acess
2. Never leak a handle of data to outside
3. Design the interface appropriately.
