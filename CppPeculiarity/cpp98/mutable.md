当然，`mutable`是C++98中的一个关键字，它用于声明一个类成员变量可以在常量成员函数中被修改。以下是一个使用`mutable`的例子：

```cpp
#include <iostream>

class MyClass {
public:
    MyClass() : value(0) {}

    // 常量成员函数
    void add() const {
        // 尽管这是一个常量成员函数，但我们仍然可以修改value，因为它被声明为mutable
        value++;
    }

    void print() const {
        std::cout << "Value: " << value << std::endl;
    }

private:
    mutable int value;  // mutable成员变量
};

int main() {
    MyClass obj;
    obj.add();
    obj.print();  // 输出：Value: 1

    return 0;
}
```

在这个例子中，我们创建了一个名为`MyClass`的类，它有一个名为`value`的`mutable`成员变量。然后我们在一个常量成员函数`add`中修改了`value`的值。这是C++98中引入的一种非常有用的特性，它使得我们可以在常量成员函数中修改某些成员变量的值。这对于实现一些特殊的功能（如缓存）非常有用。