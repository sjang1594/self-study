# Concurrent Programming 2

## Source Code
thread_management.cpp

1. Thread can be created using any callable object; Functor, function, and lambda function

### Note
```
// The most vexing(annoying) syntax of c++
  // what if I just want to create t1 with arguments of Functor()
  std::thread t1(Fuctor()) //--> This won't work (not compile)
  // --> this is not creating a thread of t1 instead we are declaring a function
  // --> with the function name t1. This function takes a single parameter
  // --> which is a pointer to another function, and Fuctor takes no parameter
  // --> and return a Functor, and a function t1 returns a thread

```c++

* C++ standard says whenever a statement can be interpreted as a function decoration, it will be treated as function declaration

### Question
What if I have a very complicated problem to solve, then ideally I would have to create as many number of threads as the number of calls that I have, which also means that I want to create threads not more than hardware can support
--> This is called **Oversubscription**

Of course, Oversubscription is bad because there are more threads running than available CPU cores, it will creates a lot of context switching and too many of context switching will degrade the performance

Solution to this,
``std::thread::hardware_concurrency(); // Indication``
This will guide for spliting tasks among the threads.


## Resource
[Youtube](https://www.youtube.com/watch?v=f2nMqNj7vxE)
