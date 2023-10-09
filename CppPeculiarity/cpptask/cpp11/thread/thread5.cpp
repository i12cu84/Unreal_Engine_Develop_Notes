#include <iostream>
#include <thread>
#include <mutex>
#include <Windows.h>

using namespace std;

void thread1()
{
    for (int i = 0; i < 10000; i++)
        cout << "1";
}

void thread2()
{
    for (int i = 0; i < 10000; i++)
        cout << "2";
}

int main(int argc, char *argv[])
{
    thread t1(thread1);
    thread t2(thread2);
    t1.join();
    t2.join();

    return 0;
}