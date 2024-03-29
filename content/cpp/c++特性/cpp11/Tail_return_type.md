C++11引入了一种新的函数返回类型语法，称为尾部返回类型。在C++11之前，函数的返回类型通常在函数名之前指定。然而，在处理模板函数或带有decltype的函数时，表达复杂的返回类型可能会很具挑战性。

使用尾部返回类型语法，你可以在参数列表后使用auto关键字和尾随的->箭头来指定函数的返回类型。这允许你使用表达式和decltype来根据函数的实现推导出返回类型。

以下是一个尾部返回类型的例子：

```cpp
// C++程序来说明C++ 11中的尾部返回类型
#include <iostream>

// 使用auto和decltype的尾部返回类型
auto add (int a, int b) -> decltype(a + b) {
    return a + b;
}

int main () {
    int x = 5, y = 10;
    auto result = add (x, y);
    std::cout << "Result: " << result << std::endl; // 输出：Result: 15
    return 0;
}
```
在这个例子中，我们定义了一个名为`add`的函数，它使用了尾部返回类型来指定其返回类型。这种语法允许我们在函数实现中使用表达式和decltype来推导出函数的返回类型。

请注意，使用尾部返回类型需要C++11或更高版本的编译器支持。此外，你可能需要查阅你的编译器文档以获取更多信息。