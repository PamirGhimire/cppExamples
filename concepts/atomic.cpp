// Example program
#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <atomic>


int main()
{
  std::atomic<int> counter{0};
//   int counter{0};
  std::thread t1{
      [&counter](){
        for (size_t i= 0; i<10000; ++i)
        ++counter;
      }
      
  };
  std::thread t2{
      [&counter](){
        for (size_t i= 0; i<10000; ++i)
        ++counter;
      }
      
  };
  
  t1.join();
  t2.join();
  
  std::cout << "counter = " << counter << std::endl;
  return EXIT_SUCCESS;
}
