```cpp
#include <iostream>

// 使用字节对齐说明符指定结构体的内存对齐方式为8字节
struct alignas(8) MyAlignedStruct {
    int a;
    char b;
    double c;
};

int main() {
    MyAlignedStruct myStruct;

    // 使用alignof获取myStruct的实际对齐方式
    std::cout << "Alignment of MyAlignedStruct: " << alignof(MyAlignedStruct) << " bytes" << std::endl;

    // 使用offsetof获取成员的偏移量
    std::cout << "Offset of a: " << offsetof(MyAlignedStruct, a) << " bytes" << std::endl;
    std::cout << "Offset of b: " << offsetof(MyAlignedStruct, b) << " bytes" << std::endl;
    std::cout << "Offset of c: " << offsetof(MyAlignedStruct, c) << " bytes" << std::endl;

    return 0;
}

```


这段代码定义了一个名为`MyAlignedStruct`的结构体，其中包含三个成员变量：一个整型变量`a`，一个字符变量`b`和一个双精度浮点数变量`c`。使用字节对齐说明符`alignas(8)`指定了结构体的内存对齐方式为8字节。

在主函数中，我们创建了一个名为`myStruct`的结构体对象。然后，我们使用`alignof()`函数获取了该结构体的实际对齐方式，并使用`offsetof()`函数获取了每个成员变量的偏移量。最后，我们输出了这些信息。

这里是一些关于这些函数的重要信息：

- `alignof()`函数返回指定类型或对象的对齐要求。
- `offsetof()`函数返回指定成员在其所属结构体中的偏移量。

