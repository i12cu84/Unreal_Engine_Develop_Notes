#include <boost/mp11.hpp>
#include <iostream>

int main() {
    namespace mp11 = boost::mp11;

    using types = mp11::mp_list<int, double, float>;

    static_assert(mp11::mp_size<types>::value == 3, "Size of list is not 3");

    using first_type = mp11::mp_at_c<types, 0>;
    static_assert(std::is_same<first_type, int>::value, "First type is not int");

    std::cout << "Type at index 1: " << mp11::mp_at_c<types, 1>::value << std::endl;
}
