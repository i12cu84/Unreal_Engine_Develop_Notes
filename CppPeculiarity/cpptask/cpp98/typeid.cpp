#include <iostream>
#include <typeinfo>
class MyClass {};
int main() {
    MyClass obj;
    std::cout << "Type of obj is " << typeid(obj).name() << std::endl;
    return 0;
}