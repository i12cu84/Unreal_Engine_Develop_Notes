C++98的标准模板库（STL）是一种高效的C++程序库，包含了许多在计算机科学领域里常用的基本数据结构和基本算法³。以下是一些主要的STL组件以及相应的代码示例：

1. **容器（Containers）**：如`vector`、`list`、`deque`、`set`、`map`等，用于存储和管理数据²。

2. **算法（Algorithm）**：如`sort`、`find`、`count`等，用于处理容器中的数据²。

3. **迭代器（Iterators）**：提供了一种访问容器中元素的方式²。

4. **容器适配器（Container Adapters）**：如`stack`、`queue`、`priority_queue`等，它们是基于其他容器（如`deque`或`vector`）进行封装，提供了特定的接口¹。

5. **仿函数（Functors）**：也称为函数对象，它们是重载了函数调用运算符`()`的类的对象⁶。

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
int main() {
    std::vector<int> v;
    for (int i = 0; i < 5; i++) 
        v.push_back(i);
#if 1
    for (int i = 0; i < v.size(); i++) 
        std::cout << v[i] << " ";
#elif 1
    std::sort(v.begin(), v.end());
    for (int i : v) 
        std::cout << i << " ";
#elif 1
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) 
        std::cout << *it << " ";
#elif 1
    std::stack<int> s;
    for (int i = 0; i < 5; i++) 
        s.push(i);
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
#elif 1
struct Compare {
    bool operator()(int a, int b) {
        return a < b;
    }
};
    std::sort(v.begin(), v.end(), Compare());
    for (int i : v) {
        std::cout << i << " ";
    }
#endif
    return 0;
}
```