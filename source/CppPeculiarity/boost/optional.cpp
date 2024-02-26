#include <boost/optional.hpp>
#include <iostream>

int main() {
    boost::optional<int> maybeValue;
    if (maybeValue) {
        std::cout << "Value is present: " << *maybeValue << std::endl;
    } else {
        std::cout << "Value is empty." << std::endl;
    }

    maybeValue = 42;
    if (maybeValue) {
        std::cout << "Value is present: " << *maybeValue << std::endl;
    }
}
