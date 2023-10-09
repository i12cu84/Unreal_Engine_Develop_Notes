```
#include <iostream>
#include <thread>
#include <semaphore>
std::counting_semaphore<5> sem(5);
void worker(int id)
{
    sem.acquire();
    std::cout << "Worker " << id << " acquired semaphore" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    sem.release();
    std::cout << "Worker " << id << " released semaphore" << std::endl;
}
int main()
{
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);
    t1.join();
    t2.join();
    t3.join();
}
```
C++20引入了信号量（semaphore）作为一种同步机制，用于控制对共享资源的并发访问。
以下是一个使用std::counting_semaphore的简单示例：

在这个示例中，我们创建了一个计数信号量sem，其计数器的初始值为5。
三个线程尝试获取信号量，但是由于计数器的初始值为5，只有前五个线程可以成功获取信号量。
当一个线程获取到信号量时，它会打印一条消息，并等待2秒钟。然后它会释放信号量并打印另一条消息。