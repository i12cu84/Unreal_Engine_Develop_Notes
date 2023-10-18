#include <boost/type_index.hpp>
#include <iostream>

int main() {
    int value = 42;
    std::cout << "Type of value: " << boost::typeindex::type_id_runtime(value).pretty_name() << std::endl;
}
