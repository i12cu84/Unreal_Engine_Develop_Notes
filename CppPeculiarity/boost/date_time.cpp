#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

int main() {
    boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
    std::cout << "Current time: " << now << std::endl;
}
