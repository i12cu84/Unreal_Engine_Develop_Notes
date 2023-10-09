#include <iostream>
#include <any>
#include <vector>
int main()
{
    std::vector<std::any> values;
    values.push_back(42);
    values.push_back(3.14);
    values.push_back(std::string("Hello, Any!"));
    for (const std::any &val : values)
        if (val.type() == typeid(int))
            std::cout << "Int value in container: " << std::any_cast<int>(val) << std::endl;
        else if (val.type() == typeid(double))
            std::cout << "Double value in container: " << std::any_cast<double>(val) << std::endl;
        else if (val.type() == typeid(std::string))
            std::cout << "String value in container: " << std::any_cast<std::string>(val) << std::endl;
    return 0;
}
