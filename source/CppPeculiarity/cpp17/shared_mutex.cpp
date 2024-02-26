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
