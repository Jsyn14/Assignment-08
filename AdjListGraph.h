//authored by: Dr. Lewis
// Modified by: Jayson Hamilton
// Assisted by: ChatGPT

#pragma once
#include "Graph.h"
#include <unordered_map>
#include <vector>
#include <algorithm>

template <class N>
class AdjacencyListGraph : public Graph<N> {
public:
    explicit AdjacencyListGraph(bool directed = true)
        : directed_(directed) {}

    AdjacencyListGraph(std::vector<N> nodes,
                       std::vector<std::pair<N,N>> edges,
                       bool directed = true)
        : directed_(directed)
    {
        for (const auto& v : nodes) addNode(v);
        for (const auto& e : edges) addEdge(e.first, e.second);
    }

    bool adjacent(N x, N y) override {
        auto it = adj_.find(x);
        if (it == adj_.end()) return false;
        const auto& nbrs = it->second;
        return std::find(nbrs.begin(), nbrs.end(), y) != nbrs.end();
    }

    std::vector<N>& neighbors(N x) override {
        addNode(x);        // ensure key exists
        return adj_[x];    // returns the stored vector<N>&
    }

    void addNode(N x) override {
        if (!adj_.count(x)) {
            adj_[x] = {};
            nodes_.push_back(x);
        }
    }

    void addEdge(N x, N y) override {
        addNode(x);
        addNode(y);
        auto& a = adj_[x];
        if (std::find(a.begin(), a.end(), y) == a.end()) a.push_back(y);
        if (!directed_) {
            auto& b = adj_[y];
            if (std::find(b.begin(), b.end(), x) == b.end()) b.push_back(x);
        }
    }

    void deleteEdge(N x, N y) override {
        auto it = adj_.find(x);
        if (it != adj_.end()) {
            auto& a = it->second;
            a.erase(std::remove(a.begin(), a.end(), y), a.end());
        }
        if (!directed_) {
            auto jt = adj_.find(y);
            if (jt != adj_.end()) {
                auto& b = jt->second;
                b.erase(std::remove(b.begin(), b.end(), x), b.end());
            }
        }
    }

private:
    bool directed_;
    std::vector<N> nodes_;                          // optional: insertion order
    std::unordered_map<N, std::vector<N>> adj_;     // node -> neighbors
};
