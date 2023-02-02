#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

// c++11 multithreading
using namespace std;

mutex mtx; // mutual exclusion

int main()
{
    auto work_func = [](const string& name)
    {
        for (int i = 0; i < 5; ++i)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(100));

            mtx.lock();
            cout << name << " " << std::this_thread::get_id() << "is working " << i << endl;
            mtx.unlock();
        }
    };

    /*work_func("jack");
    work_func("dash");*/

    std::thread t1 = std::thread(work_func, "Jack");
    std::thread t2 = std::thread(work_func, "dash");
    t1.join();
    t2.join();
    return 0;
}