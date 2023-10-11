#include <iostream>
#include <typeinfo>
class Base { virtual void func() {} };
class Derived : public Base {};
int main() {
    Base* base = new Derived;
    if(Derived* derived = dynamic_cast<Derived*>(base)) {
        std::cout << "dynamic_cast successful" << std::endl;
    }
    std::cout << "Type of base: " << typeid(*base).name() << std::endl;
    return 0;
}