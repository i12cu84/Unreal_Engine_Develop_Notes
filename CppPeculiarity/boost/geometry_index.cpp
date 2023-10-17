#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <iostream>

int main() {
    namespace bg = boost::geometry;
    namespace bgi = boost::geometry::index;

    typedef bg::model::point<float, 2, bg::cs::cartesian> point;
    typedef std::pair<point, int> value;

    bgi::rtree<value, bgi::quadratic<16>> rtree;

    rtree.insert(std::make_pair(point(1, 1), 1));
    rtree.insert(std::make_pair(point(2, 2), 2));
    rtree.insert(std::make_pair(point(3, 3), 3));

    bg::model::box<point> query_box(point(0, 0), point(4, 4));

    std::vector<value> result;
    rtree.query(bgi::intersects(query_box), std::back_inserter(result));

    for (const value& v : result) {
        std::cout << "Value: " << v.second << std::endl;
    }
}
