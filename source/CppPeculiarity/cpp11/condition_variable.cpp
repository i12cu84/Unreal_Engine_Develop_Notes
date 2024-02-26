#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
std::mutex mtx;
std::condition_variable cv;
bool dataReady = false;
void producer()
{
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟生产数据
    {                                                     // 数据准备完毕
        std::lock_guard<std::mutex> lock(mtx);
        dataReady = true;
    }
    cv.notify_one(); // 通知等待的线程数据已准备好
}
void consumer()
{
    std::unique_lock<std::mutex> lock(mtx); // 等待数据准备
    cv.wait(lock, []
            { return dataReady; });
    std::cout << "Consumer: Data is ready." << std::endl; // 处理数据
}
int main()
{
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);
    producerThread.join();
    consumerThread.join();
    return 0;
}