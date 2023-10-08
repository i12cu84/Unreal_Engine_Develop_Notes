```
#include <iostream>
#include <utility>
int main()
{
    int originalValue = 42;
    int newValue = 100;
    std::cout << "Original Value: " << originalValue << std::endl; // 输出 42
    std::cout << "New Value: " << newValue << std::endl;           // 输出 100
    
    int result = std::exchange(originalValue, newValue);
    std::cout << "Original Value: " << originalValue << std::endl; // 输出 100
    std::cout << "New Value: " << newValue << std::endl;           // 输出 100
    std::cout << "Result: " << result << std::endl;                // 输出 42
    return 0;
}
```
与swap相区别，exchange返回被交换的值，而不是交换的引用。