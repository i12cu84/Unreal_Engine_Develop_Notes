```
#include <iostream>
class MyClass
{
public:
    MyClass() = default;                // 使用 default 关键字来声明默认构造函数
    MyClass(int value) : data(value) {} // 自定义构造函数
    MyClass(const MyClass &) = default; // 使用 default 关键字来声明默认拷贝构造函数
    ~MyClass() = default;               // 使用 default 关键字来声明默认析构函数
    void printData()
    {
        std::cout << "Data: " << data << std::endl;
    }

private:
    int data = 0;
};
int main()
{
    MyClass obj1;        // 使用默认构造函数创建对象
    obj1.printData();    // 输出默认值 0
    MyClass obj2(42);    // 使用自定义构造函数创建对象
    obj2.printData();    // 输出 42
    MyClass obj3 = obj2; // 使用默认拷贝构造函数创建新对象
    obj3.printData();    // 输出 42
    return 0;
}
```
在这个示例中，定义了一个 MyClass 类，并使用 default 关键字来声明默认构造函数、默认拷贝构造函数和默认析构函数。这意味着编译器将自动生成这些特殊成员函数的默认实现。
还定义了一个自定义构造函数，以及一个成员变量 data，并在 main 函数中创建了多个 MyClass 对象，演示了默认构造函数、自定义构造函数以及默认拷贝构造函数的使用。
这个示例展示了如何使用 default 关键字来声明默认特殊成员函数，以减少手动编写这些函数的工作，同时仍然可以定义自定义的构造函数和其他类成员。