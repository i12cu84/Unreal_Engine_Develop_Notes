```
#include <iostream>
#include <thread>
#include <shared_mutex>
std::shared_mutex mutex;
int sharedData = 0;
void reader() {
    for (int i = 0; i < 3; ++i) {
        std::shared_lock<std::shared_mutex> lock(mutex); // 读锁定
        std::cout << "Reader " << i << " reads: " << sharedData << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
void writer() {
    for (int i = 0; i < 3; ++i) {
        std::unique_lock<std::shared_mutex> lock(mutex); // 写锁定
        ++sharedData;
        std::cout << "Writer " << i << " writes: " << sharedData << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
int main() {
    std::thread t1(reader);
    std::thread t2(writer);
    std::thread t3(reader);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
```
std::shared_mutex 是C++17引入的线程安全的读写锁（Shared Mutex），允许多个线程并发读取共享数据，但在写入时会排他锁定。
std::shared_mutex 允许多个读取线程并发地访问 sharedData，但一次只能允许一个写入线程修改它。这确保了线程安全的读取和写入共享数据。
在输出中，你可以看到读取和写入线程交替执行，而不会导致数据竞争。