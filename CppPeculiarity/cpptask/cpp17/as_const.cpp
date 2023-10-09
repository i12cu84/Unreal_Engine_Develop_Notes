#include <iostream>
#include <vector>
#include <utility>
int main() {
    std::vector<int> myVector = {1, 2, 3, 4, 5};
    // 创建一个只读引用，即使myVector是非const的
    const std::vector<int>& readOnlyVector = std::as_const(myVector);
    // 尝试修改只读引用，编译会失败
    // readOnlyVector.push_back(6);
    // 但可以访问只读引用的元素
    for (int value : readOnlyVector) 
        std::cout << value << " ";
    return 0;
}
