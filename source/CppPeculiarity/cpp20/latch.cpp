#include <latch>
#include <iostream>
#include <thread>
std::latch my_latch{3};
void my_function()
{
    my_latch.arrive_and_wait();
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
/*
std::latch是C++20中引入的一个同步原语，它是一个下降计数器，可以用于同步线程。
计数器的值在创建时初始化。线程可以在锁存器上阻塞，直到计数器递减到零。

创建了一个名为my_latch的std::latch实例，计数为3。
我们创建了三个线程，它们都调用了my_function()。
在锁存器处，每个线程都调用了my_latch.arrive_and_wait()来暂停执行，直到所有其他线程都到达锁存器。
一旦所有线程都到达，锁存器就会被解除，所有线程都可以恢复执行。
完成后，控制台会显示消息“All threads have finished.”。
*/