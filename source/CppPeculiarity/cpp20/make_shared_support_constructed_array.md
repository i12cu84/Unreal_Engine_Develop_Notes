```
#include <memory>
#include <iostream>
int main() {
    // 创建一个包含10个int的数组
    std::shared_ptr<int[]> arr(new int[10]);
    // 初始化数组
    for (int i = 0; i < 10; ++i) 
        arr[i] = i;
    // 打印数组
    for (int i = 0; i < 10; ++i) 
        std::cout << arr[i] << ' ';
    std::cout << '\n';
    return 0;
}
```
make_shared支持构造数组
首先创建了一个包含10个int的数组，并使用std::shared_ptr<int[]>来管理它。然后，我们初始化并打印这个数组。