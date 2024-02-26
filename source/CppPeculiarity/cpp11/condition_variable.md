照例
```
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
```
在这个示例中，有一个生产者线程和一个消费者线程。生产者线程模拟生产数据，并在数据准备好后通知消费者线程。消费者线程等待数据准备的通知，然后处理数据。
使用 std::mutex 来保护共享变量 dataReady，并使用 std::condition_variable 来进行线程间的通信。cv.wait(lock, [] { return dataReady; }) 会在 dataReady 变为 true 之前阻塞线程，然后在收到通知后继续执行。
这个示例演示了如何使用 std::condition_variable 来进行线程同步，允许一个线程等待另一个线程发送通知，以实现协调和同步操作。