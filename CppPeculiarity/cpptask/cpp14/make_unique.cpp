#include <iostream>
#include <memory>
int main()
{
    std::unique_ptr<int> myInt = std::make_unique<int>(42);
    std::cout << "Value:" << *myInt << std::endl;
    *myInt = 100;
    std::cout << "Update Value:" << *myInt << std::endl;
    return 0;
}