#include <iostream>
#include <thread>
#include <mutex>
std::mutex mtx; // 声明一个互斥锁
int sharedData = 0; // 共享资源
void incrementSharedData(int id) {
    for (int i = 0; i < 5; ++i) {
        mtx.lock();// 在访问共享资源前，锁定互斥锁
        ++sharedData;// 访问共享资源
        std::cout << "Thread " << id << ": Shared Data = " << sharedData << std::endl;
        mtx.unlock();// 在访问共享资源后，释放互斥锁
        std::this_thread::sleep_for(std::chrono::milliseconds(100));// 模拟其他工作
    }
}
int main() {
    // 创建两个线程来增加共享数据
    std::thread thread1(incrementSharedData, 1);
    std::thread thread2(incrementSharedData, 2);
    // 等待线程完成
    thread1.join();
    thread2.join();
    return 0;
}
