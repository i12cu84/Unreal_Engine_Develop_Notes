```
#include <iostream>
class MyClass {
public:
    explicit MyClass(int value) : data(value) {
    }
    void printData() {
        std::cout << "Data: " << data << std::endl;
    }
private:
    int data;
};
int main() {
    MyClass obj1(42); // 直接使用 int 构造 MyClass 对象
    obj1.printData();
    // 编译错误：不能进行隐式类型转换
    // MyClass obj2 = 10; 
    return 0;
}
```
在这个示例中，定义了一个 MyClass 类，它具有一个 explicit 构造函数，该构造函数接受一个整数参数。因为构造函数被标记为 explicit，所以不能通过隐式类型转换将整数直接赋值给 MyClass 对象，否则会导致编译错误。
在 main 函数中，首先创建了一个 MyClass 对象 obj1，通过直接调用构造函数并传递整数值 42 来初始化它。这是允许的，因为显式地调用了构造函数。
然后，尝试创建一个 MyClass 对象 obj2 并将整数 10 赋值给它，但由于构造函数是 explicit 的，这种隐式类型转换是不允许的，因此会导致编译错误。
通过使用 explicit 关键字，可以明确表示只有通过显式调用构造函数才能创建对象，以避免可能引发混淆或错误的隐式类型转换。