/*
threads synchronization using mutex
author : Pamir Ghimire
*/
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

int global_int(0);
std::mutex global_mutex;
using namespace std::literals;

void increment1()
{
    {
        std::lock_guard<std::mutex> g(global_mutex);
        for (int i = 0; i < 3; ++i)
        {
            global_int++;
            std::cout << "increment1" << std::endl;
        }
    }
    
    std::this_thread::sleep_for(0.1s);
    
    {
        std::lock_guard<std::mutex> g(global_mutex);
        for (int i = 0; i < 3; ++i)
        {
            global_int++;
            std::cout << "*increment1" << std::endl;
        }
    }

}

void decrement1()
{
    {
        std::lock_guard<std::mutex> g(global_mutex);
        for (int i = 0; i < 3; ++i)
        {
            global_int--;
            std::cout << "decrement1" << std::endl;
        }
    }

    std::this_thread::sleep_for(0.1s);

    {
        std::lock_guard<std::mutex> g(global_mutex);
        for (int i = 0; i < 3; ++i)
        {
            global_int--;
            std::cout << "*decrement1" << std::endl;
        }
    }

}


int main()
{
    std::thread t1(increment1);
    std::thread t2(decrement1);
    
    t1.join();
    t2.join();
    
    std::cout << "global int = " << global_int << std::endl;
}
