#include <iostream>
#include <memory>
int main()
{
    int arr[4] = {1, 2, 3, 4};
    int *p1 = std::assume_aligned<16>(arr);
    // 使用p1，而不是arr，以确保从对齐假设中受益。
    // 但是，如果arr没有对齐，无论是否使用p1，程序都具有未定义行为。
    std::cout << *p1 << '\n';
    return 0;
}
/*
std::assume_aligned是C++20中引入的一个函数模板，它用于通知编译器，指针ptr指向的对象至少与N对齐。
编译器可以使用此信息来生成更有效的代码，但只有在通过assume_aligned的返回值访问对象时，它才可能做出此假设。N必须是2的幂。

首先创建了一个整数数组arr。
然后，我们使用std::assume_aligned<16>来假设这个数组至少与16字节对齐，并将返回的指针赋值给p1。然后我们通过p1来访问数组。
*/