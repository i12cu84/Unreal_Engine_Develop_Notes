```
#include <iostream>
#include <span>
void print_elements(std::span<int> arr)
{
    for (const auto &elem : arr)
        std::cout << elem << ' ';
    std::cout << '\n';
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    print_elements(arr);
    return 0;
}
```
定义了一个print_elements函数，它接受一个std::span<int>参数。
然后，它遍历这个span中的所有元素并打印它们。
在main函数中，我们创建了一个整数数组，并将其传递给print_elements函数
C++20引入了std::span作为一种语法糖，用于表示连续内存范围。
它提供了一种轻量级的、非拥有式的、零开销的方式来引用数组或其他连续内存块。
std::span可以用于传递数组片段给函数，或者在函数内部对连续内存进行操作，而无需进行内存拷贝。
以下是一些主要的特性23：
非拥有引用：std::span不拥有它引用的数据。它只是对现有数据的一个包装。
轻量级：std::span设计得非常高效，占用的内存很小。通常，它只包含两个指针（开始和结束）和一个大小值。
连续序列：std::span只能与连续的数据结构（如数组、std::vector或std::array）一起使用。它不能与非连续的数据结构（如链表）一起使用。
安全措施：std::span包含边界检查，确保安全地访问底层数据。
