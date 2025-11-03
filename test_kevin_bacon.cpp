#include <iostream>
#include <vector>
#include <string>
#include "Graph.h"
#include "AdjListGraph.h"
#include "kevin_bacon.h"

using std::string;
using std::vector;

// Build a fixed social graph of 20 people (undirected)
template <class G>
void build_social_graph(G& g, vector<string>& nodes) {
    nodes = {
        "You",
        "Kevin Bacon",
        "Alice","Bob","Carol","Dave","Eve","Frank","Grace","Heidi",
        "Ivan","Judy","Mallory","Niaj","Olivia","Peggy","Rupert","Sybil","Trent","Uma"
    }; // 20 total

    for (auto& n : nodes) g.addNode(n);

    auto connect = [&](const string& a, const string& b) {
        g.addEdge(a, b); // undirected graph (we'll construct G with directed=false)
    };

    // Ensure a short path from You to Kevin Bacon
    connect("You","Alice");
    connect("Alice","Bob");
    connect("Bob","Carol");
    connect("Carol","Kevin Bacon"); // path length 4 nodes => KB number 3

    // Extra edges to make it realistic
    connect("You","Eve");
    connect("Eve","Frank");
    connect("Frank","Grace");
    connect("Grace","Heidi");
    connect("Heidi","Kevin Bacon");

    connect("Bob","Dave");
    connect("Dave","Eve");

    connect("Judy","Mallory");
    connect("Mallory","Niaj");
    connect("Niaj","Olivia");
    connect("Olivia","Peggy");
    connect("Peggy","Rupert");
    connect("Rupert","Sybil");
    connect("Sybil","Trent");
    connect("Trent","Uma");
    connect("Uma","Kevin Bacon");

    connect("Ivan","Judy");
    connect("Ivan","Grace");
    connect("Carol","Judy");
}

int main() {
    AdjacencyListGraph<string> social(false); // undirected
    vector<string> people;
    build_social_graph(social, people);

    vector<string> path;
    auto kbNumber = kevinBaconNumber(social, string("You"), people, path);

    if (!kbNumber.has_value()) {
        std::cout << "No connection to Kevin Bacon found.\n";
        return 0;
    }

    std::cout << "Path from You to Kevin Bacon:\n";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i + 1 < path.size()) std::cout << " -> ";
    }
    std::cout << "\nKevin Bacon number: " << *kbNumber << "\n";
    return 0;
}
