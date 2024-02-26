#include <iostream>
int main()
{
    int value = 1;
    switch (value)
    {
    case 1:
        std::cout << "Case 1" << std::endl;
        [[fallthrough]]; // 允许控制流落入下一个 case
    default:
        std::cout << "Default Case" << std::endl;
        break;
    }
    return 0;
}