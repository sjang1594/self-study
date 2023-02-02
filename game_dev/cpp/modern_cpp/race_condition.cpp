#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>

using namespace std;
mutex mtx;
int main()
{
    atomic<int> shared_memory(0);
    auto const_func = [&]() {
        for (int i = 0; i < 1000; ++i)
        {
            this_thread::sleep_for(chrono::milliseconds(1));  // if this code is not there / this won't be multithreading
            // t1 finishes quickly / t2 finishes after
            // std::lock_guard --> prefered                 // this won't require mutex.unlock()
            // std::scoped_lock lock(mtx);                  // c++ 17 | more preferable!
            shared_memory++;
            //mtx.unlock();
            //shared_memory.fetch_add(1);
        }
    };

    thread t1 = thread(const_func);
    thread t2 = thread(const_func);
    t1.join();
    t2.join();
    
    cout << "After" << endl;
    cout << shared_memory << endl;
    return 0;
}