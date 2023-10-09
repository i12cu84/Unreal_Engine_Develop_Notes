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
