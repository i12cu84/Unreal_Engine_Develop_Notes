#include <iostream>
#include <thread>
#include <mutex>
std::once_flag flag;
void initializeOnce()
{
    auto fun = []()
    {
        std::cout << "Initialization is done." << std::endl;
    };
    std::call_once(flag, fun);
}
int main()
{
    // 创建多个线程，但只有一个线程会调用 fun
    std::thread t1(initializeOnce);
    std::thread t2(initializeOnce);
    t1.join();
    t2.join();
    return 0;
}
