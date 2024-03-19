#include <iostream>
template <int N>
struct PositiveIntegerCheck
{
    static_assert(N > 0, "Input integer must be positive.");
};
int main()
{
    constexpr int num = 42; // yes
    // constexpr int num = -5;  //error
    PositiveIntegerCheck<num> check_positive;
    return 0;
}
