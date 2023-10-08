```
#include <iostream>
using namespace std;
class MyClass
{
public:
    int x = 42;
    void printX()
    {
        auto lambda = [*this]()
        {
            std::cout << "x from MyClass: " << x << std::endl;
        };
        lambda();
    }
};
int main()
{
    MyClass obj;
    obj.printX();
    return 0;
}
```
lambda函数访问*this

当在Lambda表达式内部捕获*this时，它实际上是捕获当前对象的一个副本，而不仅仅是指向当前对象的指针。
这是C++中Lambda表达式捕获的一种特殊方式，通常称为捕获外部对象（Capturing the enclosing object）。
这种捕获方式的主要特点和用途包括：
捕获当前对象状态： 当Lambda表达式捕获*this时，它可以访问当前对象的所有成员变量和成员函数，并且可以修改它们（如果Lambda是可变的）。这允许Lambda访问和修改当前对象的状态。
延长当前对象的生命周期： 当Lambda捕获*this时，它实际上延长了当前对象的生命周期，因为Lambda可以在当前对象已经离开作用域的情况下继续存在并访问它。这可以避免悬垂引用错误。
方便的成员函数调用： 当Lambda捕获*this时，它可以方便地调用当前对象的成员函数，而不需要显式传递当前对象的指针或引用作为参数。
例如:
如果多线程情况下，函数的作用域超过了对象的作用域，对象已经被析构了，还访问了成员变量，就会有问题。
捕获*this，不持有this指针，而是持有对象的拷贝，这样生命周期就与对象的生命周期不相关了，可以避免悬垂引用的问题。