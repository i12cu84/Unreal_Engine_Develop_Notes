#include <iostream>
#include <string>
#include <boost/variant.hpp>

typedef boost::variant<int, double, std::string> my_variant;

int main()
{
    my_variant v1 = 42;
    my_variant v2 = 3.14;
    my_variant v3 = "hello, world!";

    std::cout << boost::get<int>(v1) << "\n";
    std::cout << boost::get<double>(v2) << "\n";
    std::cout << boost::get<std::string>(v3) << "\n";

    return 0;
}
