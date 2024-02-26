#include <iostream>
union MyUnion
{
    int intValue;
    double doubleValue;
    char charValue;
};
int main()
{
    MyUnion myUnion;
    myUnion.intValue = 42;
    std::cout << "Integer value: " << myUnion.intValue << std::endl;
    myUnion.doubleValue = 3.14;
    std::cout << "Double value: " << myUnion.doubleValue << std::endl;
    myUnion.charValue = 'A';
    std::cout << "Char value: " << myUnion.charValue << std::endl;
    return 0;
}
