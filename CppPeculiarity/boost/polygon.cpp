#include <boost/polygon/polygon.hpp>
#include <iostream>

int main() {
    typedef boost::polygon::point_data<int> point;
    typedef boost::polygon::polygon_set_data<int> polygon_set;

    polygon_set poly1, poly2;
    polygon_set result;

    poly1 += point(0, 0) + point(0, 2) + point(2, 2) + point(2, 0);
    poly2 += point(1, 1) + point(1, 3) + point(3, 3) + point(3, 1);

    boost::polygon::intersection(result, poly1, poly2);

    std::cout << "Intersection area: " << boost::polygon::area(result) << std::endl;
}