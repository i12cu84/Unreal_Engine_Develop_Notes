```
#include <iostream>
#include <utility>
template <typename T, T... Integers>
constexpr T sumOfIntegersInSequence(std::integer_sequence<T, Integers...>)
{
    return (Integers + ...);
}
int main()
{
    constexpr auto sequence = std::integer_sequence<int, 1, 2, 3, 4, 5>();
    constexpr int result = sumOfIntegersInSequence(sequence);
    std::cout << "Sum of integers in the sequence: " << result << std::endl;
    return 0;
}
```
展开模板参数包
std::integer_sequence 是C++标准库中的一个模板类，用于表示一个整数序列。它通常用于元编程，特别是在模板元编程中，以便在编译时生成整数序列，用于展开模板参数包。
std::integer_sequence 的定义如下：
```
template <typename T, T... Ints>
struct integer_sequence;
```
这个模板类接受一个整数类型 T 和一系列整数值 Ints 作为模板参数。这些整数值被用来表示一个整数序列。例如，std::integer_sequence<int, 0, 1, 2, 3> 表示整数序列 {0, 1, 2, 3}。
通常，std::integer_sequence 与变参模板函数一起使用，以在编译时生成参数包展开的索引序列。这对于实现泛型算法非常有用，因为它允许你以通用的方式处理不同数量的参数。
以下是一个示例，展示如何使用 std::integer_sequence 来生成参数包的索引序列：
```
template <typename... Args>
void MyFunction(Args... args) {
    // 生成参数包的索引序列
    constexpr std::size_t num_args = sizeof...(Args);
    using IndexSeq = std::make_index_sequence<num_args>;
    // 在这里可以使用 IndexSeq 来处理参数包 args
}
```
在这个示例中，std::make_index_sequence 用于生成一个整数序列，它包含了参数包 Args 的索引，然后可以在函数内部使用这个索引序列来处理参数包的元素。
总之，std::integer_sequence 是C++标准库中用于处理整数序列的强大工具，特别适用于模板元编程和泛型编程。