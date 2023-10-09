#include <iostream>
class Base
{
public:
    virtual void show()
    {
        std::cout << "Base::show()" << std::endl;
    }
};
class Derived : public Base
{
public:
    void show() override // 使用 override 关键字表明这是对基类虚拟函数的覆盖
    {
        std::cout << "Derived::show()" << std::endl;
    }
};
class FinalDerived final : public Derived // 使用 final 关键字表明不能再派生新的类
{
public:
    void show() override
    {
        std::cout << "FinalDerived::show()" << std::endl;
    }
};
// 错误示例，尝试派生 FinalDerived 的子类，会导致编译错误
/*
class ErrorDerived : public FinalDerived
{
public:
    void show() override
    {
        std::cout << "ErrorDerived::show()" << std::endl;
    }
};
*/
int main()
{
    Base *ptr = new FinalDerived;
    ptr->show();
    delete ptr;
    return 0;
}