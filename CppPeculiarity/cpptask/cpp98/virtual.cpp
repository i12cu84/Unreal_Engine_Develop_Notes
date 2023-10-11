#include <iostream>
class Base {
public:
    virtual void print() { 
        std::cout<<"Base::print()"<<std::endl;
    }
};
class Derived : public Base {
public:
    void print() override { 
        std::cout<<"Derived::print()"<<std::endl;
    }
};
int main()
{
    Base base;
    base.print();
    Derived derived;
    derived.print();
    return 0;
}