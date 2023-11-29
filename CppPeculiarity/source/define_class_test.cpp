//用于测试define用法
#include <iostream>
using namespace std;

class text
{
public:
    text(){}
    text(int a) : _a(a) {}
    int _a;
    void _print()
    {
        cout << "_a:" << _a << endl;
    }
};

#define FUNC_RETVAL(func, classname, ret) \
class classname:public text { \
public: \
    classname(int _ret) : ret(_ret) {} \
    int ret; \
    void func() { _print();cout << ret << endl; } \
};

int main()
{
    FUNC_RETVAL(myFunction, MyClass, rep); // 示例化 MyClass
    MyClass myObject(123); // 创建 MyClass 对象
    myObject.myFunction();
    
    return 0;
}