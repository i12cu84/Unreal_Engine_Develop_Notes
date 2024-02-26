```
#include <iostream>
#include <optional>
std::optional<int> getOptionalValue(bool hasValue)
{
    if (hasValue)
        return 42;
    else
        return std::nullopt;
}
int main()
{
    std::optional<int> optionalWithValue = getOptionalValue(true);
    if (optionalWithValue.has_value())
        std::cout << "Optional with value: " << optionalWithValue.value() << std::endl;
    std::optional<int> optionalWithoutValue = getOptionalValue(false);
    if (!optionalWithoutValue.has_value())
        std::cout << "Optional without value." << std::endl;
    return 0;
}
```
std::optional 是 C++17 引入的一个模板类，用于表示可能有值或无值的情况，类似于可能为 null 的指针，但更加类型安全。