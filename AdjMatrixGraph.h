//authored by: Dr. Lewis
// Modified by: Jayson Hamilton
// Assisted by: ChatGPT

#pragma once
#include "Graph.h"
#include <unordered_map>
#include <vector>

template <class N>
class AdjacencyMatrixGraph : public Graph<N> {
public:
    explicit AdjacencyMatrixGraph(bool directed = true)
        : directed_(directed) {}

    AdjacencyMatrixGraph(std::vector<N> nodes,
                         std::vector<std::pair<N,N>> edges,
                         bool directed = true)
        : directed_(directed)
    {
        for (const auto& v : nodes) addNode(v);
        for (const auto& e : edges) addEdge(e.first, e.second);
    }

    bool adjacent(N x, N y) override {
        int ix = idx(x), iy = idx(y);
        if (ix < 0 || iy < 0) return false;
        return matrix_[static_cast<size_t>(ix)][static_cast<size_t>(iy)];
    }

    // Returns a reference to an internal scratch vector reused on each call.
    // Consume it immediately; don't store it.
    std::vector<N>& neighbors(N x) override {
        scratch_.clear();
        int i = idx(x);
        if (i < 0) { addNode(x); i = idx(x); }
        for (size_t j = 0; j < nodes_.size(); ++j) {
            if (matrix_[static_cast<size_t>(i)][j]) scratch_.push_back(nodes_[j]);
        }
        return scratch_;
    }

    void addNode(N x) override {
        if (pos_.count(x)) return;
        pos_[x] = static_cast<int>(nodes_.size());
        nodes_.push_back(x);
        for (auto& row : matrix_) row.push_back(false);
        matrix_.push_back(std::vector<bool>(nodes_.size(), false));
    }

    void addEdge(N x, N y) override {
        addNode(x);
        addNode(y);
        size_t ix = static_cast<size_t>(pos_[x]);
        size_t iy = static_cast<size_t>(pos_[y]);
        matrix_[ix][iy] = true;
        if (!directed_) matrix_[iy][ix] = true;
    }

    void deleteEdge(N x, N y) override {
        auto fx = pos_.find(x);
        auto fy = pos_.find(y);
        if (fx == pos_.end() || fy == pos_.end()) return;
        size_t ix = static_cast<size_t>(fx->second);
        size_t iy = static_cast<size_t>(fy->second);
        matrix_[ix][iy] = false;
        if (!directed_) matrix_[iy][ix] = false;
    }

private:
    int idx(const N& x) const {
        auto it = pos_.find(x);
        return it == pos_.end() ? -1 : it->second;
    }

    bool directed_;
    std::vector<N> nodes_;
    std::unordered_map<N, int> pos_;
    std::vector<std::vector<bool>> matrix_;
    std::vector<N> scratch_;   // reused buffer for neighbors(x)
};
