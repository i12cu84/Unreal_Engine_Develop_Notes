#include <iostream>
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef bg::model::point<double, 2, bg::cs::cartesian> point;
typedef bg::model::box<point> box;

int main() {
    bgi::rtree<box, bgi::quadratic<16>> rtree;

    box b1(point(0.0, 0.0), point(1.0, 1.0));
    box b2(point(1.0, 1.0), point(2.0, 2.0));

    rtree.insert(b1);
    rtree.insert(b2);

    std::vector<box> result_s;
    rtree.query(bgi::intersects(box(point(0.5, 0.5), point(1.5, 1.5))), std::back_inserter(result_s));

    for (const auto& r : result_s) {
        std::cout << bg::wkt(r) << std::endl;
    }

    return 0;
}
