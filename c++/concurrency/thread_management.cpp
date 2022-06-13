#include <iostream>
#include <thread>
using namespace std;

void function_1(){
  std::cout << "Where there is a will, there is a way" << std::endl;
}

// Functor
class Fctor {
  public:
      void operator()() {
        for (int i=0; i>-100; i--){cout << "from t1 " << i <<endl;}
      }
};

// 2. What if I want to pass the parameter by value in functor
class Fuctor2 {
  public:
      void operator()(string msg){
        cout << "t1 says: "  << msg << endl;
      }
};

// 3. What if I want to pass the parameter by reference in functor
class Functor3{
  public:
      void operator()(string &msg){
        cout << "t1 says: " << msg <<endl;
      }
};

int main(){
  // Create Functor
  Fctor fct;
  std::thread t1(fct);

  // 1. what if I just want to create t1 with arguments of Functor()
  // std::thread t1(Fuctor()) --> This won't work (not compile)
  // --> this is not creating a thread of t1 instead we are declaring a function
  // --> with the function name t1. This function takes a single parameter
  // --> which is a pointer to another function, and Fuctor takes no parameter
  // --> and return a Functor, and a function t1 returns a thread
  // SOLUTION: use another pair parenthesis
  // std::thread t1((Fuctor()))
  // explicitly that this is constructing a functor and pass it as parameter to the constructor t1

  // 2. Passing the parameter through Functor (By value)
  // string s = "Where there is no trust, there is no love";
  // std::thread t1((Fctor2()), s)

  // 3. Passing the parameter by reference
  // if you pass the s to thread, it's always going to be 'pass-by-value'.
  // if you really want to pass the string as reference, then use below
  // std::thread t1((Fctor2()), std::ref(s))
  // --> This will create a reference wrapper for s

  // COMMENTS:
  // The parent thread and child thread shared memeory which is string s
  // Another way to achieve this, use the pointer
  // Suppose, I do not want to share memory among threads --> data wast problem
  // std::thread t1((Fctor()), std::move(s))
  // --> this will move the s from the main thread to the child thread
  // --> Efficient!!
  // What if I want to do this
  // Copy std::thread t2 = t1 --> Fail
  // Then what can you do ?? (Transfer the owndership of a thread t1 to t2)
  // std::thread t2 = std::move(t1);
  // t2.join();
  // --> Check thread
  // cout << std::this_thread::get_id() << endl; --> This will print out the parent thread's ID
  // cout <<t1.get_id() <<endl;

  /* */
  // std::thread t1(function_1); //t1 starts running
  // Alternative Approcah - using RAII
  // Wrapper w(t1); --> when w goes out of scope, it will automatically join the thread

  // Main Thread --> starts count (working)
  // then, it throws an exception
  try{
      for (int i = 0; i < 100; i++)
        cout << "from main: " << i <<endl;
  }catch(...){
    t1.join(); // --> Make sure t1 join
    throw;
  }

  // Thread object will be destroyed before joining
  t1.join();
  return 0;
}
