#include <iostream>
#include <thread>
thread_local int threadLocalValue = 0;
int threadCommonValue = 0;
void threadFunction()
{
    // 在每个线程中修改 Value
    threadLocalValue++;
    threadCommonValue++;
    std::cout << "Thread Local Value: " << threadLocalValue << std::endl;
    std::cout << "Thread Common Value: " << threadCommonValue << std::endl;
}
int main()
{
    // 创建多个线程，并在每个线程中执行 threadFunction
    std::thread t1(threadFunction);
    std::thread t2(threadFunction);
    t1.join();
    t2.join();
    return 0;
}
