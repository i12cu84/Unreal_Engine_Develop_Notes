#include <boost/histogram.hpp>
#include <iostream>

int main() {
    using namespace boost::histogram;

    auto h = make_histogram(axis::regular<>(10, -1.0, 1.0));
    h.fill(0.2);

    for (const auto& bin : indexed(h)) {
        std::cout << "Bin " << bin.index() << " has count " << bin.value() << std::endl;
    }
}
