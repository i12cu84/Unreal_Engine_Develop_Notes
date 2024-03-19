照例
```
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
```
有两个互斥锁 mtx1 和 mtx2，然后创建了两个线程 t1 和 t2，它们分别调用 threadFunction1 和 threadFunction2 函数。

在 threadFunction1 和 threadFunction2 函数中，使用 std::lock 函数同时锁定两个互斥锁，以避免死锁。然后，使用 std::lock_guard 来创建两个锁保护对象，并使用 std::adopt_lock 标志告诉它们这些锁已经被锁定，不需要再次锁定。这允许安全地在临界区内执行操作，然后在 std::lock_guard 超出范围时自动释放锁。

这个示例演示了如何使用 std::lock 来同时锁定多个互斥锁，以确保线程安全的操作，并使用 std::lock_guard 来管理锁的生命周期。