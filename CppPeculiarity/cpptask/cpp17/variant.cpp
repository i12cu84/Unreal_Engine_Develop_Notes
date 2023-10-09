#include <iostream>
#include <variant>
class A{
    A(int i){}
};
int main()
{
    std::variant<int, std::string> myVariant;
    myVariant = 42;
    if (std::holds_alternative<int>(myVariant))
        std::cout << "The variant holds an int: " << std::get<int>(myVariant) << std::endl;
    myVariant = "Hello, Variant!";
    if (std::holds_alternative<std::string>(myVariant))
        std::cout << "The variant holds a string: " << std::get<std::string>(myVariant) << std::endl;
    std::variant<std::monostate,A> var;
    return 0;
}
