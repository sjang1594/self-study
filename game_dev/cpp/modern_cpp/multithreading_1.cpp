#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

// c++11 multithreading
using namespace std;
int main()
{
    const int num_pro = std::thread::hardware_concurrency();

    // id of this programmign thread
    cout << std::this_thread::get_id() << endl;

    vector<std::thread> my_threads;
    my_threads.resize(num_pro);

    for (auto &e : my_threads)
        e = std::thread([]() {cout << std::this_thread::get_id() << endl; while (true) {}});
   /* std::thread t2 = std::thread([]() {cout << std::this_thread::get_id() << endl; while (true) {}});
    std::thread t3 = std::thread([]() {cout << std::this_thread::get_id() << endl; while (true) {}});
    std::thread t4 = std::thread([]() {cout << std::this_thread::get_id() << endl; while (true) {}});*/

    // wait till t1 finishes
    // t1.join();
    //t2.join();
    //t3.join();
    //t4.join();

    for (auto& e : my_threads)
        e.join();
    return 0;
}