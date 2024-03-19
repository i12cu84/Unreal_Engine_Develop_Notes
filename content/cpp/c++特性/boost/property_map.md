Boost.PropertyMap：用于将数据关联到图形结构的库。
示例：使用Boost.PropertyMap创建一个顶点名称映射。

```cpp
#include <boost/property_map/property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <iostream>

int main() {
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::property<boost::vertex_name_t, std::string>> Graph;

    Graph g;
    auto vertex_name = boost::get(boost::vertex_name, g);

    boost::add_vertex(g);
    vertex_name[0] = "Vertex A";

    std::cout << "Name of Vertex 0: " << vertex_name[0] << std::endl;
}
```