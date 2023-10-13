#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <mutex>
#include <Windows.h>
using namespace std;
#if 1
void thread_one(){
    puts("hello");
}
void thread_two(int num, string& str){
    cout << "num:" << num << ",name:" << str << endl;
}
int main(int argc, char* argv[]){
    thread tt(thread_one);
    tt.join();
    string str = "luckin";
    thread yy(thread_two, 88, ref(str));   //这里要注意是以引用的方式调用参数
    yy.detach();
    system("pause");
    return 0;
}
#elif 1
static int RunNum=0;
void f1(int n){
    for (int i = 0; i < 5; ++i)    {
        cout << "=====Thread:" << n << "======" << endl;
        this_thread::sleep_for(chrono::microseconds(10));
        RunNum++;
    }
}
void f2(int& n){
    for (int i = 0; i < 5; ++i)    {
        cout << "thread two executing" << endl;
        ++n;
        this_thread::sleep_for(chrono::microseconds(10));
        RunNum++;
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
    cout << "the result n is:" << n << "run num:"<<RunNum<<endl;
    system("pause");
    return 0;
}
#elif 1
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
#elif 1
timed_mutex g_timed_mutex;
void thread1(){
    unique_lock<timed_mutex> t1(g_timed_mutex);
    Sleep(200);
    cout << "thread1" << endl;
}
void thread2(){
    unique_lock<timed_mutex> t1(g_timed_mutex, chrono::milliseconds(1000));//设置超时时间为1秒
    cout << "thread2" << endl;
}
int main(int argc, char* argv[]){
    thread t1(thread1);
    Sleep(100);   //让线程1先启动
    thread t2(thread2);
    t1.join();
    t2.join();
    system("pause");
    return 0;
} 
#elif 1
void thread1(){
    for (int i = 0; i < 10000; i++)
        cout << "1";
}
void thread2(){
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
#endif