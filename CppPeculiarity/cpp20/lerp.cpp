#include <iostream>
#include <cmath>
int main()
{
    float a = 0.0f;
    float b = 1.0f;
    float t = 0.5f;
    std::cout << "The midpoint of " << a << " and " << b << " is " << std::lerp(a, b, t) << '\n';
    return 0;
}
/*
std::lerp是C++20中引入的一个函数，它用于计算两个数值或指针之间的线性插值。
如果参数t在[0, 1]范围内，那么它计算的是a和b之间的线性插值（否则是线性外插），
即(a+t*(b−a))的结果，同时考虑了浮点计算的不精确性12。

首先定义了两个浮点数a和b，以及一个插值参数t。
然后，使用std::lerp(a, b, t)来计算它们的中点，并打印出结果。
*/