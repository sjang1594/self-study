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

int main(){
  // Create Functor
  Fctor fct;
  std::thread t1(fct);

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
