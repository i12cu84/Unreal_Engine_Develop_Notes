#include <iostream>
#include <thread> // C++20中包含了jthread
void my_function(std::stop_token stoken)
{
    while (!stoken.stop_requested())
        std::cout << "do it" << std::endl;
}
int main()
{
    std::jthread jt(my_function);
    for (int i = 0; i < 10; ++i)
        std::cout << i << std::endl;
    jt.request_stop(); // 请求停止线程
    return 0;
}

/*
std::jthread是C++20新引入的线程类，与std::thread类似，但功能更强大。std::jthread的“j”实际上是“joining”的缩写。
以下是一些主要的特性：
自动加入：与std::thread不同，std::jthread在其生命周期结束时会自动调用join()，无需手动调用。
    如果线程在析构函数被调用时仍然可加入（即，还没有完成任务或被分离），那么程序会立即异常终止。
    这是因为未加入的线程在析构时会导致未定义行为。
可中断：std::jthread可以被请求停止。
    你可以通过调用成员函数request_stop()来请求停止线程。
    然后，线程可以通过检查由成员函数get_stop_token()返回的std::stop_token来响应停止请求。

创建了一个名为jt的std::jthread实例，并传入了一个函数。
这个函数接受一个std::stop_token参数，并在循环中检查是否有停止请求。
在主函数中，在需要停止线程时调用了jt.request_stop()。
*/