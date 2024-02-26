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
