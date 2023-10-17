#include <boost/flyweight.hpp>
#include <string>
#include <iostream>

int main() {
    typedef boost::flyweight<std::string> flystring;
    flystring a = "Hello";
    flystring b = "Hello";

    std::cout << "a and b are the same object: " << (a.get() == b.get()) << std::endl;
}