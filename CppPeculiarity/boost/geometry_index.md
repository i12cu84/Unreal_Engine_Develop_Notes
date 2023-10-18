Boost.Geometry Index是一个C++库，它提供了一种轻量级的方式来管理空间索引。这个库提供了多种实现方式，包括R树、k-d树和四叉树等。

下面是一个简单的使用Boost.Geometry Index库的例子：

```
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
```

这个例子定义了一个名为rtree的R树对象，并插入了两个名为b1和b2的矩形。然后我们使用query()函数来查询与另一个矩形相交的所有矩形，并将结果写入标准输出。