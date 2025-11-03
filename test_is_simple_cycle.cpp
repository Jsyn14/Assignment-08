#include <iostream>
#include <vector>
#include <cassert>
#include "Graph.h"
#include "AdjListGraph.h"
#include "AdjMatrixGraph.h"
#include "is_simple_cycle.h"
using std::vector;

template <typename G>
void run_tests_for_graph(G& g, const char* label) {
    std::cout << "Running tests for " << label << "...\n";
    g.addEdge(1,2); g.addEdge(2,3); g.addEdge(3,1);
    assert(isSimpleCycle(g, vector<int>{1,2,3,1}));
    assert(!isSimpleCycle(g, vector<int>{1,2,1}));
    assert(!isSimpleCycle(g, vector<int>{1,2,3}));
    assert(!isSimpleCycle(g, vector<int>{1,2,3,2,1}));
    g.addNode(4);
    assert(!isSimpleCycle(g, vector<int>{1,2,3,4,1}));
    std::cout << "✅ Basic undirected tests passed for " << label << ".\n";
}
int main() {
    AdjacencyListGraph<int> listG(false);
    run_tests_for_graph(listG, "AdjacencyListGraph (undirected)");
    AdjacencyMatrixGraph<int> matG(false);
    run_tests_for_graph(matG, "AdjacencyMatrixGraph (undirected)");
    AdjacencyListGraph<int> dlist(true);
    dlist.addEdge(1,2); dlist.addEdge(2,3); dlist.addEdge(3,1);
    assert(isSimpleCycle(dlist, vector<int>{1,2,3,1}));
    assert(!isSimpleCycle(dlist, vector<int>{1,3,2,1}));
    std::cout << "🎉 All tests passed.\n";
    return 0;
}
