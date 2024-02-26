Boost.Intrusive：用于设计高性能容器的库，允许对象的成员函数来控制容器操作。
示例：使用Boost.Intrusive创建一个双向链表。

```cpp
#include <boost/intrusive/list.hpp>
#include <iostream>

struct MyNode : public boost::intrusive::list_base_hook<> {
    int value;
};

typedef boost::intrusive::list<MyNode> NodeList;

int main() {
    NodeList list;
    MyNode node1, node2, node3;
    node1.value = 1;
    node2.value = 2;
    node3.value = 3;

    list.push_back(node1);
    list.push_back(node2);
    list.push_back(node3);

    for (const MyNode& node : list) {
        std::cout << "Value: " << node.value << std::endl;
    }
}
```