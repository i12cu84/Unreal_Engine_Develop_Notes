#include <boost/histogram2/histogram.hpp>
#include <iostream>

int main() {
    using namespace boost::histogram2;

    auto h = make_histogram(axis::regular<>(10, -1.0, 1.0), axis::regular<>(5, 0.0, 1.0));
    h(0.2, 0.5);

    for (const auto& bin : indexed(h)) {
        std::cout << "Bin " << bin.index() << " has count " << bin.value() << std::endl;
    }
}
