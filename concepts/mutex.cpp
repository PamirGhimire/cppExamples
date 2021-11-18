/*
threads synchronization using mutex
author : Pamir Ghimire
*/

#include <iostream>
#include <mutex>
#include <thread>

std::mutex m;
int val(0);

void reset()
{
    using namespace std::literals;
    std::this_thread::sleep_for(1s);
    
    std::lock_guard<std::mutex> guard(m);
    val = 0;
}

void checkPeriodically()
{
    for (int i = 0; i < 20; ++i){
        {
            std::lock_guard<std::mutex> guard(m);
            std::cout << val << "  ";
            val++;
        }

        using namespace std::literals;
        std::this_thread::sleep_for(0.1s);
    }
    
    std::cout << std::endl;
}

int main()
{
    std::thread t1(reset);
    std::thread t2(checkPeriodically);
    
    t1.join();
    t2.join();
    return 0;   
}