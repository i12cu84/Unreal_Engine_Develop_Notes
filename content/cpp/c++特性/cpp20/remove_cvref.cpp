#include <type_traits>
#include <iostream>
template <typename T>
void print_type()
{
    if constexpr (std::is_same_v<T, std::remove_cvref_t<T>>)
        std::cout << "T is not const, volatile or reference\n";
    else
        std::cout << "T is const, volatile or reference\n";
}
int main()
{
    int a = 0;
    const int b = 0;
    print_type<decltype(a)>();
    print_type<decltype(b)>();
    print_type<decltype((b))>();
    return 0;
}
/*
std::remove_cvref是C++20中引入的一个类型特性，它用于移除类型的顶层const、volatile修饰符以及引用。
这个特性在模板元编程中非常有用，因为它可以帮助我们获取到原始的、未修饰的类型。

定义了一个模板函数print_type，它接受一个类型参数T。
然后，我们使用std::is_same_v和std::remove_cvref_t来检查T是否是const、volatile或引用。
如果T和移除了顶层const、volatile修饰符以及引用后的T相同，那么我们就打印"T is not const, volatile or reference"；
否则，我们打印"T is const, volatile or reference"。
*/