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