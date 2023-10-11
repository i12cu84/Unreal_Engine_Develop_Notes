#include <iostream>
#include <typeinfo>
int main() {
    int i = 0;
    double d = 0.0;
    std::cout << "Type of i is " << typeid(i).name() << std::endl;
    std::cout << "Type of d is " << typeid(d).name() << std::endl;
    return 0;
}