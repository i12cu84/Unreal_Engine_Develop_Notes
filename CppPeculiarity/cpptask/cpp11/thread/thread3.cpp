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