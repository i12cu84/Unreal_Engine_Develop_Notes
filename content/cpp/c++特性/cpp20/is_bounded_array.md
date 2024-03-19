```
#include <iostream>
#include <type_traits>
class A {};
int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_bounded_array_v<A> << '\n';     // 输出：false
    std::cout << std::is_bounded_array_v<A[]> << '\n';   // 输出：false
    std::cout << std::is_bounded_array_v<A[3]> << '\n';  // 输出：true
    std::cout << std::is_bounded_array_v<float> << '\n'; // 输出：false
    std::cout << std::is_bounded_array_v<int> << '\n';   // 输出：false
    std::cout << std::is_bounded_array_v<int[]> << '\n'; // 输出：false
}
```
std::is_bounded_array是C++20中引入的一个模板结构，它用于检查T是否是已知边界的数组类型。
如果T是已知边界的数组类型，那么成员常量value等于true，否则，value等于false。

在这个例子中，我们首先定义了一个类A。然后，我们使用std::is_bounded_array_v<T>来检查各种类型是否是已知边界的数组类型，并打印出结果。
请注意，这段代码需要C++20或更高版本的编译器才能运行。