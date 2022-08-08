#include <iostream>
#include <thread>
#include <string>
#include <mutex>
using namespace std;

std::mutex mu;

void shared_print(string msg, int id)
{
  std::lock_guard<std::mutex> guard(mu); //RAII
  cout << msg << id << endl;
  mu.unlock();
}

void function_1(){
  for (int i=0; i>-100; i--)
      shared_print(string("From t1: "), i);
}

int main()
{
  std::thread t1(function_1);
  for (int i=0; i<100; i++)
      shared_print(string("From Main: "), i);


  t1.join();
  return 0;
}
