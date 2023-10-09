#include <iostream>
#include <tuple>
int main()
{
    int a = 1;
    double b = 3.14;
    std::string c = "Hello";
    auto myTuple = std::tie(a, b, c);//变成了tuple
    std::cout << "a: " << std::get<0>(myTuple) << std::endl; // 输出 42
    std::cout << "b: " << std::get<1>(myTuple) << std::endl; // 输出 2.718
    std::cout << "c: " << std::get<2>(myTuple) << std::endl; // 输出 "World"
    return 0;
}
