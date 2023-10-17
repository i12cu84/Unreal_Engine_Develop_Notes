#include <boost/circular_buffer.hpp>
#include <iostream>

int main() {
    boost::circular_buffer<int> buffer(5);
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);

    for (int value : buffer) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    buffer.push_back(4);
    buffer.push_back(5);

    for (int value : buffer) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}