Boost.Graph：用于图算法和数据结构的库。
示例：创建一个简单的有向图并查找最短路径。

```cpp
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <iostream>

int main() {
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int>> Graph;
    Graph g;

    boost::add_edge(0, 1, 2, g);
    boost::add_edge(1, 2, 1, g);
    boost::add_edge(0, 2, 4, g);

    std::vector<int> distances(boost::num_vertices(g));
    boost::dijkstra_shortest_paths(g, 0, boost::distance_map(boost::make_iterator_property_map(distances.begin(), boost::get(boost::vertex_index, g)));

    for (std::size_t i = 0; i < distances.size(); ++i) {
        std::cout << "Shortest distance from vertex 0 to vertex " << i << ": " << distances[i] << std::endl;
    }
}
```