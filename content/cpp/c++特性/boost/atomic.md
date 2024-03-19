```
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
```
我们使用了 Boost::atomic_int 类型来存储一个整数值。boost::atomic_int 提供了一个原子操作，可以安全地在多个线程中对整数进行递增和递减。
使用 Boost::atomic 的 C++程序示例。这个程序创建了一个线程安全的计数器，可以在多个线程中安全地递增和递减。