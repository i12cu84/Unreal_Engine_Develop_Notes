thread c++11 通用多线程
1.std::thread介绍及示例
首先说明一下，对于以前的编译器， 若要使用C++11的特性，编译时要设定参数如下：

-std=c++11

这里先写一个简单的线程示例程序。

```
#include <iostream>
#include <thread>
#include <string>

using namespace std;

void thread_one()
{
    puts("hello");
}

void thread_two(int num, string& str)
{
    cout << "num:" << num << ",name:" << str << endl;
}

int main(int argc, char* argv[])
{
    thread tt(thread_one);
    tt.join();
    string str = "luckin";
    thread yy(thread_two, 88, ref(str));   //这里要注意是以引用的方式调用参数
    yy.detach();

system("pause");
return 0;
}
```
通过代码，我们创建了一个tt线程对象，其参数是函数thread_one，创建完成后被执行，tt.join()是等待子线程执行完成之后，主线程才继续执行，此时主线程会释放掉执行完成后的子线程的资源。

对于线程对象yy，我们传入了调用函数的两个参数，这里在线程yy执行时，主线程不想等待子线程，故使用了yy.detach()将子线程从主线程中分离出来，这样主线程就对子线程没有控制权了，子线程执行完成后会自己释放掉资源。

2.std::thread重要函数梳理
thread() noexcept：默认构造函数，创建一个空的thread执行对象；
explicit thread(Fn&&fn, Args&&...args)：初始化构造函数，创建一个带函数调用参数的thread，这个线程是可joinable的；
thread(const thread&) = delete：拷贝构造函数被禁用，意味着thread对象不可拷贝构造；
thread(thread&& x) noexcept：移动构造函数，调用成功之后，x不代表任何thread执行对象；
其构造函数的使用示例如下：
```
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void f1(int n)
{
    for (int i = 0; i < 5; ++i)
    {
	cout << "=====Thread:" << n << "======" << endl;
	this_thread::sleep_for(chrono::microseconds(10));
    }
}

void f2(int& n)
{
    for (int i = 0; i < 5; ++i)
    {
	cout << "thread two executing" << endl;
	++n;
	this_thread::sleep_for(chrono::microseconds(10));
    }
}

int main()
{
    int n = 0;
    thread t1;    //这是一个空的线程对象，还不是一个线程
    thread t2(f1, n + 1);
    thread t3(f2, ref(n));
    thread t4(move(t3));    //t3不再是一个线程
    t2.join();
    t4.join();
    cout << "the result n is:" << n << endl;

    system("pause");
    return 0;
}
```
3.thread中几个重要的成员函数
get_id()：获取线程的ID，它将返回一个类型为std::thread::id的对象。
joinable()：检查线程是否可被join。
对于join这里值得注意：

在任意一个时间点上，线程是可结合joinable或者可分离detached的。一个可结合线程是可以被其它线程回收资源和杀死结束的，而对于detached状态的线程，其资源不能被其它线程回收和杀死，只能等待线程结束才能由系统自动释放。由默认构造函数创建的线程是不能被join的；另外，若某个线程已执行完任务，但是没有被join的话，该线程依然会被认为是一个活动的执行线程，因此是可以被join的。

detach()：将当前线程对象所代表的执行实例与此线程对象分离，使得线程可以单独执行。
swap()：交换两个线程对象所代表的底层句柄，参数是两个线程对象；
std::this_thread::getid()：获取当前线程的ID；
std::this_thread::yield()：当前线程放弃执行，操作系统调度另一线程继续执行；
sleep_until()：线程休眠至某个指定的时刻，才被重新唤醒；
sleep_for()： 线程休眠某个指定的时间片，才被重新唤醒；
4.thread中的互斥量
在多个线程同时访问共享资源时，就需要对资源进行加锁互斥访问，thread提供了四种不同的互斥量：

独占式互斥量：std::mutex 。独占工互斥量加解锁是成对的，同一个线程内独占式互斥量在没有解锁的情况下，再次对其加锁是不正确的，会得到一个未定义的行为。
递归式互斥量：std::recursive_mutex。递归式互斥量是在同一个线程内互斥量没有解锁的情况下可以再次对其加锁，但其加解锁的次数需要保持一致。这种互斥量平时用得比较少。
允许超时的独占式互斥量：std::timed_mutex
允许超时的递归式互斥量：std::recursive_timed_mutex
下面的代码示例了独占式互斥量的用法：
```
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int g_num = 0;
mutex g_mutex;

void thread1()
{
    g_mutex.lock();
    g_num = 50;
    for (int i = 0; i < 10; ++i)
	cout << "thread1:" << g_num << endl;
    g_mutex.unlock();
}

void thread2()
{
    lock_guard<mutex>lg(g_mutex);   //用这种方式更安全
    g_num = 100;
    for (int j = 0; j < 10; ++j)
	cout << "thread2:" << g_num << endl;
}

int main(int argc, char* argv[])
{
    thread t1(thread1);
    thread t2(thread2);
    t1.join();
    t2.join();

    system("pause");
    return 0;
}
```
若线程1对共享资源的访问时间较长，这时线程2可能等不了那么久，故设定一个超时时间 ，在超时时间内若线程1中的互斥量还没有解锁，线程2就不等了，继续向下执行，这就是允许超时的互斥量。对于允许超时的互斥量，我们需要用unique_lock来包装。

下面代码示例了允许超时的互斥量的用法：
```
#include <iostream>
#include <thread>
#include <mutex>
#include <Windows.h>

using namespace std;

timed_mutex g_timed_mutex;
void thread1()
{
    unique_lock<timed_mutex> t1(g_timed_mutex);
    Sleep(200);
    cout << "thread1" << endl;
}

void thread2()
{
    unique_lock<timed_mutex> t1(g_timed_mutex, chrono::milliseconds(1000));//设置超时时间为1秒
    cout << "thread2" << endl;
}

int main(int argc, char* argv[])
{
    thread t1(thread1);
    Sleep(100);   //让线程1先启动
    thread t2(thread2);
    t1.join();
    t2.join();

    system("pause");
    return 0;
} 
```

参考资料
https://zhuanlan.zhihu.com/p/646832703