#include <boost/hana.hpp>
#include <iostream>

int main() {
    using namespace boost::hana;

    auto int_value = int_c<42>;
    auto double_value = to<double>(int_value);

    std::cout << double_value << std::endl;
}
