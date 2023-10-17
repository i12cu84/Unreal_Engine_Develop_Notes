#include <boost/graph/graph_traits.hpp>
#include <boost/graph/clustering_coefficient.hpp>
#include <iostream>

int main() {
    using namespace boost;

    typedef adjacency_list<vecS, vecS, undirectedS> Graph;
    Graph g(4);

    add_edge(0, 1, g);
    add_edge(0, 2, g);
    add_edge(1, 2, g);
    add_edge(2, 3, g);

    float clustering_coeff = clustering_coefficient(g);
    std::cout << "Clustering Coefficient: " << clustering_coeff << std::endl;
}
