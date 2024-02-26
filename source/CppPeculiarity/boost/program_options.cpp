#include <boost/geometry.hpp>
#include <iostream>

int main() {
    typedef boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian> point;
    point p1(1.0, 2.0);
    point p2(4.0, 6.0);

    double distance = boost::geometry::distance(p1, p2);
    std::cout << "Distance between points: " << distance << std::endl;
}