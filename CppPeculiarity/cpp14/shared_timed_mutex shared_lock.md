```
#include <iostream>
#include <thread>
#include <shared_mutex>
std::shared_timed_mutex mutex;
int sharedData = 0;
void readData(int threadId)
{
    std::shared_lock<std::shared_timed_mutex> lock(mutex);
    std::cout << "Thread " << threadId << " is reading sharedData: " << sharedData << std::endl;
}
void writeData(int threadId, int newValue)
{
    std::unique_lock<std::shared_timed_mutex> lock(mutex);
    sharedData = newValue;
    std::cout << "Thread " << threadId << " is writing sharedData: " << newValue << std::endl;
}
int main()
{
    std::thread reader1(readData, 1);
    std::thread reader2(readData, 2);
    std::thread writer(writeData, 3, 42);
    reader1.join();
    reader2.join();
    writer.join();
    return 0;
}
```
读写锁，保证多个线程可以同时读，但是写线程必须独立运行，写操作不可以同时和读操作一起进行