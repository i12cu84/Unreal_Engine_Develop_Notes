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