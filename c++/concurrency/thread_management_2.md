# Concurrent Programming 3


## Source Code
thread_management_2.cpp

### Data Race and Mutex
In stiuation like two threads are running together, two threads are racing for the common ressource (such as cout).

```
void function_1(){ cout ... }

int main(){ cout ...}
```

The outcome of a program depends on the relative execution order of one or more threads and typically the race condition is not good for the regular program. Avoid as possible as you can.

One way to solve or avoid this race condition is using mutex to synchronize the access of the common resource. In this case, the example would be `cout` statement.

Using the mutex, the `cout` statement on code above won't conflict to each other. In otherword, the mutex will lock and print one `cout` statement and it will unlock the mutex so that the other thread can lock the mutex, and print their message. Now the access of the common resource `cout` is synchronized with the mutex. It should never happend that two threads are using the `cout` statement at the same time.

But, what if there are error occured in the `cout` statement, the mutex is locked forever. So, it is not recommended not to use the mutex lock and unlock function directly. Instead, it is better to use keyword `lock_guard <std::mutex>`, which is resource aqusition is initialization. (So, called RAII)

---
