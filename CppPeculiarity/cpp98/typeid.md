当然，`typeid`是C++98中的一个关键字，它用于在运行时获取对象的类型信息。以下是一个使用`typeid`的例子：

```cpp
#include <iostream>
#include <typeinfo>

class MyClass {};

int main() {
    MyClass obj;

    // 使用typeid获取对象的类型信息
    std::cout << "Type of obj is " << typeid(obj).name() << std::endl;

    return 0;
}
```

在这个例子中，我们创建了一个名为`MyClass`的类和一个名为`obj`的对象，然后使用`typeid`运算符获取并打印`obj`的类型信息。这是C++98中引入的一种非常有用的特性，它使得我们可以在运行时获取对象的类型信息。需要注意的是，`typeid`运算符返回的是一个`std::type_info`对象，我们可以使用其`name()`成员函数来获取类型的名称。但是，这个名称是编译器特定的，并不一定与源代码中的类型名称完全相同。在某些情况下，你可能需要使用C++的RTTI（运行时类型信息）功能来获取更详细或更准确的类型信息。