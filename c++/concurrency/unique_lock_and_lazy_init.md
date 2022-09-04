# Concurrent Programming 5


## Source Code
unique_lock_and_lazy_init.cpp

### Unique_lock and Lazy Initialization
Different lock kind like lock_guard, but the unique_lock gives a better flexability than the lock_guard.

```
    std::unique_lock<mutex> locker(_mu);
      _f << "From " << id << ": " << value << endl;
      locker.unlock();
```

You can also construct locker without constructing the locker by using `unique_lock`. In order to do that, you need to pass the parameter like below

```
  std::unique_lock<mutex> locker (_mu, std::defer_lock);
```
The mutex has not locked yet, so than later, you can lock the mutex as following.

```
  std::unique_lock<mutex> locker (_mu, std::defer_lock);
  locker.lock();
```

Also, you can lock the mutex in any time(arbitary number...), which you can not do with `lock_guard`. The wrapper class? `lock_guard` or `unique_lock` cannot be copied, but `unique_lock` can be moved, but `lock_guard` cannot. When you move `unique_lock`, you are transferring the ownership of a mutex from one `unique_lock` to another `unique_lock`.

Why do I want to use a locker at all. The flexibility of a unique lock is not free. The unique lock is a little bit more heavy weighted than a lock guard. So, if you are concern about the performance and you don't need the extra flexibility of the unique lock. You might just use the lock guard.

### Lazy Initialization
Example) Let's say that I have opened the log file in the constructor, but sometimes you don't want that. If it turns out that the `shared_print` has never been called, then I have opened the log file for nothing. Say I want to make sure the file will be opened only if the `shared_print` is called. Then instead of opening the file in the constructor, I am going to open it in the `shared_print` function. If file is not opened.

```
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
      if (!_f.is_open()){
        _f.open("log.txt");
      }
    }
};

```

This is known as Lazy Initialization or Initialization Upon First Use Idiom. Next thing we want to check is to make sure this program is thread safe. To do that, I need to use a mutex to synchronize the file opening process. We do not want to use `_mu` because it's used to print the message. `print` message could have been many times, but the file only needs to be open once.

Look at the following example to see if it's thread safe.

```
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
      if (!_f.is_open()){
        std::unique_lock<mutex> locker2(_mu_open);
        _f.open("log.txt");
      }
    }
};
```

The example above is not thread safe. Say if we have two threads are running; thread A and thread B. Thread A comes into `locker2` and found that the file is not opened. So, it goes ahead and lock the mutex. and start opening file. Before, it opens the file, Thread B also comes to `locker2`, and the file is not opened yet. So it also tried to lock the mutex. and B is blocked. Once the file is opened, the thread B gets into it. Thread B will open the file again. So the file opened twice by two threads. So not only the open functions needs to be synchronized, but also `is_open` function needs to be synchronized.

```
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

```
Even though this could be a solution, but this is very inefficient, because it will try to open file every time. In order to
