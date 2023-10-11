C++98的标准模板库（STL）是一种高效的C++程序库，包含了许多在计算机科学领域里常用的基本数据结构和基本算法³。以下是一些主要的STL组件以及相应的代码示例：

1. **容器（Containers）**：如`vector`、`list`、`deque`、`set`、`map`等，用于存储和管理数据²。

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v;
    for (int i = 0; i < 5; i++) {
        v.push_back(i);
    }
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

2. **算法（Algorithm）**：如`sort`、`find`、`count`等，用于处理容器中的数据²。

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9};
    std::sort(v.begin(), v.end());

    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

3. **迭代器（Iterators）**：提供了一种访问容器中元素的方式²。

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};

    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

以上只是STL的一部分，还有许多其他组件如适配器（Adapters）、仿函数（Functors）等等。这些组件使得C++编程更加灵活和方便²³。

源: 与必应的对话， 2023/10/11
(1) C++ STL六大组件-简介_stl中六大组件-CSDN博客. https://blog.csdn.net/NXHYD/article/details/108072498.
(2) 【C++】标准模板库（STL）：超快入门！算法竞赛必看！ - 知乎. https://zhuanlan.zhihu.com/p/344558356.
(3) C++都有哪些官方标准？每个版本的标准相对于前一版本增加了哪些新特性？ - 知乎. https://www.zhihu.com/question/355400393.
(4) STL学习笔记（三）——C++98的经典语言特性 - CSDN博客. https://blog.csdn.net/qq_21950929/article/details/79006153.
(5) C++11新特性-智能指针 - 知乎 - 知乎专栏. https://zhuanlan.zhihu.com/p/115162878.