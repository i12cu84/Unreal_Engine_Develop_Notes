#include <iostream>
#include <thread>
#include <mutex>
std::mutex mtx1;
std::mutex mtx2;
void threadFunction1() {
    std::lock(mtx1, mtx2); // 锁定两个互斥锁
    std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);
    // 在这里执行互斥操作
    std::cout << "Thread 1 is inside the critical section." << std::endl;
    // 这里自动释放锁 其他线程安全操作
}
void threadFunction2() {
    std::lock(mtx1, mtx2); // 锁定两个互斥锁
    std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);
    // 在这里执行互斥操作
    std::cout << "Thread 2 is inside the critical section." << std::endl;
    // 这里自动释放锁 其他线程安全操作
}
int main() {
    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);
    t1.join();
    t2.join();
    return 0;
}
