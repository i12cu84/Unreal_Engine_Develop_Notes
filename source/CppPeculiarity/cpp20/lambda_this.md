```
#include <iostream>
using namespace std;
class MyClass {
public:
    void foo() {
        auto lambda = [this] () {
            cout << "The value of m_value is " << m_value << endl;
        };
        lambda();
    }
private:
    int m_value = 42;
};
int main() {
    MyClass instance;
    instance.foo();
    return 0;
}
```
在 C++20 中，Lambda 表达式可以使用 `this` 指针来访问当前对象的成员变量和成员函数。

这个例子定义了一个名为 `MyClass` 的类，其中包含一个名为 `m_value` 的私有成员变量。在 `foo()` 函数中，我们定义了一个 Lambda 表达式，使用 `this` 指针来捕获当前对象，并输出 `m_value` 的值。
在主函数中，我们创建了一个 `MyClass` 类型的对象 `instance`，并调用了它的 `foo()` 函数。
希望这个例子能帮助你更好地理解 C++20 中 Lambda 表达式捕获 `this` 指针的用法。