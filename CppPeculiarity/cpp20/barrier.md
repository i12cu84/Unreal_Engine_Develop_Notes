```
#include <barrier>
#include <iostream>
#include <thread>
std::barrier my_barrier{3};
void my_function()
{
    my_barrier.arrive_and_wait();
}
int main()
{
    std::thread t1(my_function);
    std::thread t2(my_function);
    std::thread t3(my_function);
    t1.join();
    t2.join();
    t3.join();
    std::cout << "All threads have finished\n";
    return 0;
}
```
std::barrier是C++20中引入的一个同步原语，它用于协调多个线程在执行共同任务时的同步。
它的工作方式是作为一个屏障，所有的线程必须到达这个屏障，然后程序才能继续执行。
以下是std::barrier的一些主要特性：
可重用：与std::latch不同，一旦一组到达的线程被解除阻塞，std::barrier就可以被重用。
回调函数：std::barrier允许用户指定一个在屏障解除后执行的回调函数。这个回调函数可以执行在屏障被越过后必须完成的额外任务。

创建了一个名为my_barrier的std::barrier实例，计数为3。
我们创建了三个线程，它们都调用了my_function()。
在屏障处，每个线程都调用了my_barrier.arrive_and_wait()来暂停执行，直到所有其他线程都到达屏障。
一旦所有线程都到达，屏障就会被解除，所有线程都可以恢复执行。
完成后，控制台会显示消息“All threads have finished.”1。