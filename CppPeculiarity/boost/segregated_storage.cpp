#include <boost/segregated_storage.hpp>
#include <iostream>

struct WidgetA {
    int value;
};

struct WidgetB {
    double value;
};

int main() {
    boost::segregated_storage storage;
    auto ptr1 = storage.construct<WidgetA>(42);
    auto ptr2 = storage.construct<WidgetB>(3.14);

    std::cout << "WidgetA value: " << ptr1->value << std::endl;
    std::cout << "WidgetB value: " << ptr2->value << std::endl;
}
