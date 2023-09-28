```
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
```
在这个示例中，定义了一个基类 Base，它有一个虚拟函数 show()。然后，创建了一个派生类 Derived，它覆盖了基类的 show() 函数，并使用 override 关键字明确指出这是对基类函数的覆盖。
接下来，定义了一个名为 FinalDerived 的类，并使用 final 关键字表明它是最终的，不能再派生新的类。FinalDerived 类也覆盖了 show() 函数，并同样使用 override 关键字。
在 main 函数中，创建了一个 FinalDerived 对象的指针，然后通过基类指针调用虚拟函数 show()。由于派生类 FinalDerived 被标记为 final，因此不能再创建它的子类。试图创建 ErrorDerived 类作为 FinalDerived 的子类将导致编译错误。
这个示例演示了如何使用 final 和 override 关键字来管理派生类和虚拟函数，以确保正确的多态性和继承行为。