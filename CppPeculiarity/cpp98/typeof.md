在C++98中，`typeof`并不是一个有效的关键字。然而，你可以使用`typeid`关键字来获取一个表达式的类型。以下是一个使用`typeid`的例子：

```cpp
#include <iostream>
#include <typeinfo>

int main() {
    int i = 0;
    double d = 0.0;

    std::cout << "Type of i is " << typeid(i).name() << std::endl;
    std::cout << "Type of d is " << typeid(d).name() << std::endl;

    return 0;
}
```

在这个例子中，我们创建了两个变量`i`和`d`，然后使用`typeid`运算符获取并打印这些变量的类型。这是C++98中引入的一种非常有用的特性，它使得我们可以在运行时获取表达式的类型信息。

需要注意的是，虽然某些编译器（如GCC）提供了一个名为`typeof`的扩展，但这并不是C++标准的一部分。在标准C++中，你应该使用`typeid`或者模板来获取类型信息。如果你想要在编译时获取类型信息，你可以使用C++11引入的`decltype`关键字。