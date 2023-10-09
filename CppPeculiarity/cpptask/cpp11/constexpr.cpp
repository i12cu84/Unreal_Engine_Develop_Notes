#include <iostream>
constexpr int factorial(int n)
{
    return (n <= 1) ? 1 : n * factorial(n - 1);
}
int main()
{
    constexpr int n = 5; // 编译时常量
    constexpr int result = factorial(n);
    std::cout << "Factorial of " << n << " is: " << result << std::endl;
    return 0;
}
