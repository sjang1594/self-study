#include <iostream>
#include <thread>
using namespace std;

void function_1(){
  std::cout << "Where there is a will, there is a way" << std::endl;
}

int main(){
  std::thread t1(function_1); // t1 starts running --> child thread
  //t1.join();              // the main threads waits for t1 to finish

  t1.detach(); // t1 will freely on its own -- daemon process

  //..
  // I miss my child t1
  // then, I did t1.join() --> crash
  // if (t1.joinable())
  //  t1.join();        --> This won't crash
  return 0;
}
