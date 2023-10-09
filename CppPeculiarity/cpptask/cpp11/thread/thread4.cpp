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