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
