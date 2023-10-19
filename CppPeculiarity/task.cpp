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