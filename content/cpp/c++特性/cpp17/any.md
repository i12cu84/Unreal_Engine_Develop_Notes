```
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
```
std::any 是 C++17 中引入的一种通用值容器，可以用于存储任何类型的值，类似于 void*，但更加类型安全。
std::any 提供了一种灵活的方法，可以存储和操作各种不同类型的值，而无需事先知道其具体类型。
这在某些情况下非常有用，例如需要处理各种不同类型的配置选项或数据。