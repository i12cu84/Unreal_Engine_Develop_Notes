Boost.Graph：提供了一种用于图形和图论算法的库。以下是一个简单的Boost.Graph程序示例，它创建了一个有向图并计算了从顶点0到顶点5的最短路径：

```
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace boost;

int main()
{
    typedef adjacency_list<vecS, vecS, directedS,
                            no_property, property<edge_weight_t, int> > Graph;
    const int num_nodes = 6;
    enum nodes { A, B, C, D, E, F };
    char name[] = "ABCDEF";
    Graph g(num_nodes);
    add_edge(A, B, 1, g);
    add_edge(A, C, 2, g);
    add_edge(B, D, 3, g);
    add_edge(B, C, 4, g);
    add_edge(C, D, 5, g);
    add_edge(E, F, 6, g);

    property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, g);

    std::vector<int> d(num_nodes);
    dijkstra_shortest_paths(g, A,
                            distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index,g)))
                            .weight_map(weightmap));

    for (int i = 0; i < num_nodes; ++i)
        std::cout << "distance(" << name[A] << ", " << name[i] << ") = " << d[i] << "\n";

    return 0;
}
```