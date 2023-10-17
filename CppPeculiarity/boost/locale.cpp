#include <boost/locale.hpp>
#include <iostream>

int main() {
    boost::locale::generator gen;
    std::locale loc = gen("en_US.UTF-8");

    std::time_t now = std::time(nullptr);
    std::cout.imbue(loc);
    std::cout << boost::locale::as::date_time << now << std::endl;

    loc = gen("fr_FR.UTF-8");
    std::cout.imbue(loc);
    std::cout << boost::locale::as::date_time << now << std::endl;
}