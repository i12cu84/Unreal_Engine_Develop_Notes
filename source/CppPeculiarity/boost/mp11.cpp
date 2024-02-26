#include <iostream>
#include <boost/mp11.hpp>

int main() {
    using L1 = boost::mp11::mp_list<int, float, int, float>;
    using L2 = boost::mp11::mp_unique<L1>;
    std::cout << boost::mp11::mp_size<L2>::value << std::endl;
    return 0;
}
