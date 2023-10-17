#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/parallel/algorithm.hpp>
#include <iostream>

int main() {
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;
    Graph g(5);

    // Add edges to the graph...

    // Perform parallel breadth-first search
    boost::graph::parallel::breadth_first_search(g, 0);
}