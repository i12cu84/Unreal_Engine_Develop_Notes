`std::invoke`是C++17引入的一个功能，它可以调用任何类型的可调用对象，包括常规函数指针和成员函数指针。以下是一个简单的示例：

```cpp
#include <iostream>
#include <functional>

void func(int num) {
    std::cout << "Number: " << num << std::endl;
}

int main() {
    std::invoke(func, 5);
    return 0;
}
```

在这个例子中，我们定义了一个函数`func`，然后使用`std::invoke`来调用它。这是最基本的用法，但`std::invoke`的真正强大之处在于它可以处理更复杂的情况，例如成员函数指针和成员数据指针。

请注意，使用`std::invoke`需要包含头文件`<functional>`。此外，你可能需要更新你的编译器以支持C++17或更高版本的特性。