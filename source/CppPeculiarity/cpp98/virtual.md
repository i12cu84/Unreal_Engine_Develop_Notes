**Covariant Return Types**: 允许在派生类中重写基类中的虚函数，同时改变返回类型为基类返回类型的派生类。

```cpp
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
```
