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
