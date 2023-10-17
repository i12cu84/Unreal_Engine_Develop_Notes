#include <iostream>
int main()
{
    constexpr auto lambda = [](int n)
    { return n * n; };
    // static_assert(lambda(3)!=9,"a");//error
    static_assert(lambda(3) == 9, "a");
}