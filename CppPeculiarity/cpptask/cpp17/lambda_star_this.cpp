#include <iostream>
using namespace std;
class MyClass
{
public:
    int x = 42;
    void printX()
    {
        auto lambda = [*this]()
        {
            std::cout << "x from MyClass: " << x << std::endl;
        };
        lambda();
    }
};
int main()
{
    MyClass obj;
    obj.printX();
    return 0;
}
