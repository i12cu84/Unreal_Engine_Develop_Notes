#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/vector.hpp>
#include <iostream>
#include <string>

struct person {
    std::string name;
    int age;
};

BOOST_FUSION_ADAPT_STRUCT(person, (std::string, name)(int, age))

int main() {
    person p{"Alice", 30};
    std::cout << boost::fusion::at_c<0>(p) << ", " << boost::fusion::at_c<1>(p) << std::endl;
}
