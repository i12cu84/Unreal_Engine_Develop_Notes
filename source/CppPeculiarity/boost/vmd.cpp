#include <boost/vmd/is_empty.hpp>
#include <iostream>

#define EMPTY_MACRO

int main() {
    std::cout << "Is EMPTY_MACRO empty? " << BOOST_VMD_IS_EMPTY(EMPTY_MACRO) << std::endl;
}