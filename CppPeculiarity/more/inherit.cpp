//继承
#include <iostream>
using namespace std;
class AClass
{
public:
    void fun1() { cout << "a-fun1" << endl; };
    virtual void fun2() { cout << "a-fun2" << endl; };
};
class BClass : public AClass
{
public:
    void fun1() { cout << "b-fun1" << endl; }
    void fun2() { cout << "b-fun2" << endl; }
};
int main()
{
    AClass *aac = new AClass();
    aac->fun1();
    aac->fun2();
    AClass *abc = new BClass();
    abc->fun1();
    abc->fun2();
    BClass *bbc = new BClass();
    bbc->fun1();
    bbc->fun2();
    return 0;
}
