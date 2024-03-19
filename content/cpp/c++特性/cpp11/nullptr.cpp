#include <iostream>
using namespace std;
void func(void *ptr) 
{
    cout << "func ptr" << endl;
}
void func(int i) 
{
    cout << "func i" << endl;
}
int main() {
    int i=NULL;
    func(i);
    //func(NULL); // 编译失败，会产生二义性
    func(nullptr); // 输出func ptr
    return 0;
}
