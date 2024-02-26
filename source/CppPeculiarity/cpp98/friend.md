当然，`friend`是C++98中的一个关键字，它用于声明一个类或函数为另一个类的友元。以下是一个使用`friend`的例子：

```cpp
#include <iostream>

class MyClass {
private:
    int value;

public:
    MyClass(int v) : value(v) {}

    // 声明友元函数
    friend void printValue(const MyClass& obj);
};

// 友元函数的定义
void printValue(const MyClass& obj) {
    std::cout << "Value: " << obj.value << std::endl;
}

int main() {
    MyClass obj(10);
    printValue(obj);  // 输出：Value: 10

    return 0;
}
```

在这个例子中，我们声明了一个名为`printValue`的友元函数，它可以访问`MyClass`的私有成员。然后我们在主函数中创建了一个`MyClass`对象，并使用`printValue`函数打印其私有成员`value`。这是C++98中引入的一种非常有用的特性。