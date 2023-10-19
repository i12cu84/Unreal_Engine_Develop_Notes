#include <boost/histogram.hpp>
#include <iostream>

int main() {
    using namespace boost::histogram;
    auto hist = make_histogram(axis::regular<>(3, 0.0, 1.0));

    hist(0.2);
    hist(0.5);
    hist(0.7);

    std::cout << "Bin count in histogram: " << hist[0] << std::endl;
}
