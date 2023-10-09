#include <iostream>
#include <tuple>
#include <utility>
int sum()
{
    return 0;
}
template <typename... Args>
int sum(Args... args)
{
    std::tuple<Args...> argTuple(args...);
    return std::apply([](auto... values)
                      { return (values + ...); },
                      argTuple);
}
int main()
{
    int result = sum(1, 2, 3);
    std::cout << "Sum: " << result << std::endl;
    int result2 = sum(3, 4, 5, 6);
    std::cout << "Sum: " << result2 << std::endl;
    return 0;
}
