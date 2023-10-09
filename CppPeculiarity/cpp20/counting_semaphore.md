```
#include <semaphore>
#include <iostream>
#include <thread>
using namespace std;
counting_semaphore<2> sem { 2 }; // 最大信号量为2，可用初始值为2
void my_function () {
    while (true) {
        sem.acquire();
        std::cout << "Thread ID: " << std::this_thread::get_id() << '\n';
    }
}
int main () {
    std::thread t1 (my_function);
    std::thread t2 (my_function);
    std::thread t3 (my_function);
    // t4用于不断 release 增加信号量
    std::thread t4 ([&] {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            sem.release();
        }
    });
    t1.join();
    t2.join();
    t3.join();
    t4.detach();
    return 0;
}
```
std::counting_semaphore是C++20中引入的一个同步原语，它是一个计数信号量，可以用于同步多个线程。
计数信号量内部维护了一个计数器，线程可以通过acquire操作来递减计数器，
如果计数器的值大于零，那么acquire操作会立即返回，否则线程会被阻塞。
当其他线程通过release操作递增计数器时，被阻塞的线程会被唤醒。

创建了一个名为sem的std::counting_semaphore实例，最大信号量为2，初始可用信号量也为2。
创建了三个线程，它们都调用了my_function()。
在函数中，每个线程都调用了sem.acquire()来尝试获取信号量。
如果信号量不足，则线程会被阻塞，直到其他线程通过调用sem.release()来释放信号量。