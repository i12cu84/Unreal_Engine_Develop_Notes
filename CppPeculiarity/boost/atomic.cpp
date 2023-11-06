#include <iostream>
using namespace std;
#include <boost/atomic.hpp>  
#include <thread>

void increment_counter() {  
    boost::atomic_int counter(0);
    std::cout << "Counter before increment: " << counter << std::endl;
    ++counter;
    std::cout << "Counter after increment: " << counter << std::endl;  
}

int main() {  
    std::thread t1(increment_counter);  
    std::thread t2(increment_counter);
    t1.join();  
    t2.join();
    return 0;  
}