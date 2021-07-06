/*
unique_ptr
author : Pamir Ghimire
*/

#include <iostream>
#include <string>
#include <memory>

class Widget
{
public:
    void increment(){
        val_++;    
    }
    
    void decrement(){
        val_--;
    }
    
    void show() const{
        std::cout << val_ << std::endl;
    }
    
    ~Widget(){
        std::cout << "~Widget" << std::endl;
    }
private:
    int val_{0};
};

std::unique_ptr<Widget> increment(std::unique_ptr<Widget> w)
{
    w->increment();
    return std::move(w);
}

std::unique_ptr<Widget> decrement(std::unique_ptr<Widget> w)
{
    w->decrement();
    return std::move(w);
}


int main()
{
    auto w = std::make_unique<Widget>();
    w = increment(std::move(w));
    w = decrement(std::move(w));
    w->show();
    
    return 0;
}
