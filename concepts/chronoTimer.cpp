#include<chrono>
#include<iostream>

class Timer
{
public:
    explicit Timer(){
        begin_ = std::chrono::steady_clock::now();
    }
    
    ~Timer(){
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_time = end-begin_;

        std::cout << "duration = " << std::endl
                  << elapsed_time.count() << " seconds" << std::endl
                  << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count() << " milliseconds" << std::endl
                  << std::chrono::duration_cast<std::chrono::microseconds>(elapsed_time).count() << " microseconds" << std::endl
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_time).count() << " nanoseconds" << std::endl;

        using Clock = std::chrono::system_clock;
        using Duration = Clock::duration;
        std::cout << "Number of second's fractions per tick  is "
                  << Duration::period::num << " : " << std::scientific << double(Duration::period::den) << '\n';
    }
private:
    std::chrono::time_point<std::chrono::steady_clock> begin_;
};

int main()
{
    Timer t;
    for (int i = 0; i < 1e6; ++i){}
    return 0;
}