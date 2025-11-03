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

    // Build a triangle: 1-2, 2-3, 3-1
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    // Valid simple cycle
    assert(isSimpleCycle(g, vector<int>{1, 2, 3, 1}) && "Triangle should be a simple cycle");

    // Too short (not enough distinct vertices)
    assert(!isSimpleCycle(g, vector<int>{1, 2, 1}) && "Length-3 path cannot be a simple cycle");

    // Not closed
    assert(!isSimpleCycle(g, vector<int>{1, 2, 3}) && "Open path is not a cycle");

    // Repeats a node in the middle
    assert(!isSimpleCycle(g, vector<int>{1, 2, 3, 2, 1}) && "Repeat in middle invalidates simple cycle");

    // Uses a non-existent edge
    // Add node 4 isolated; try to step 3->4 (not an edge)
    g.addNode(4);
    assert(!isSimpleCycle(g, vector<int>{1, 2, 3, 4, 1}) && "Step on missing edge must fail");

    std::cout << "✅ Basic undirected tests passed for " << label << ".\n";
}

int main() {
    // Undirected list-backed
    AdjacencyListGraph<int> listG(/*directed=*/false);
    run_tests_for_graph(listG, "AdjacencyListGraph (undirected)");

    // Undirected matrix-backed
    AdjacencyMatrixGraph<int> matG(/*directed=*/false);
    run_tests_for_graph(matG, "AdjacencyMatrixGraph (undirected)");

    // Directed cycle check: 1->2->3->1
    AdjacencyListGraph<int> dlist(true);
    dlist.addEdge(1, 2);
    dlist.addEdge(2, 3);
    dlist.addEdge(3, 1);
    assert(isSimpleCycle(dlist, vector<int>{1, 2, 3, 1}) && "Directed cycle should be valid");

    // Direction matters: reverse edges break the path
    assert(!isSimpleCycle(dlist, vector<int>{1, 3, 2, 1}) && "Wrong direction should fail");

    std::cout << "🎉 All tests passed.\n";
    return 0;
}
