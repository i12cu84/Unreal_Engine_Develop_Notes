```
#include <iostream>
#include <vector>
#include <utility>
int main() {
    std::vector<int> myVector = {1, 2, 3, 4, 5};
    const std::vector<int>& readOnlyVector = std::as_const(myVector);// 创建一个只读引用，即使myVector是非const的
    // readOnlyVector.push_back(6);// 尝试修改只读引用，编译会失败
    for (int value : readOnlyVector) // 但可以访问只读引用的元素
        std::cout << value << " ";
    return 0;
}
```
std::as_const 是一个C++17引入的函数，用于创建一个只读（const）引用或指针，即使原始对象是非const的。这对于确保不会修改原始对象而只读取其值非常有用。

另外,

```
#include <iostream>
#include <utility>
void modifyValue(const int &value)
{
    // value = 42;// 尝试修改常量引用，会导致编译错误
    std::cout << "Inside modifyValue: " << value << std::endl;
}
void modifyValue2(int &value)
{
    value = 42;
    std::cout << "Inside modifyValue: " << value << std::endl;
}
int main()
{
    int num = 10;
    // 使用 std::as_const 创建常量引用
    const int &constNum = std::as_const(num);
    // 传递常量引用给函数，但无法修改原始对象
    modifyValue(constNum);
    // 原始对象的值没有改变
    std::cout << "Original value: " << num << std::endl;
    // 但若是想改的话...
    modifyValue2(const_cast<int &>(constNum));
    std::cout << "Original value: " << num << std::endl;
    return 0;
}
```