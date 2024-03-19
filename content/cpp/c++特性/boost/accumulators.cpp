#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <iostream>

int main() {
    using namespace boost::accumulators;
    accumulator_set<double, stats<tag::mean, tag::variance>> acc;

    acc(1.1);
    acc(2.2);
    acc(3.3);

    std::cout << "Mean: " << mean(acc) << std::endl;
    std::cout << "Variance: " << variance(acc) << std::endl;
}