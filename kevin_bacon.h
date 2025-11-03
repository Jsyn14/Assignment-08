#pragma once
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <optional>

// Works with any Graph G<N> that exposes: bool adjacent(const N& u, const N& v)
// Because we don't assume G can list neighbors, we accept the full node list.
template <class N, template<class> class G>
bool findPathTo(
    G<N>& g,
    const N& start,
    const N& goal,
    const std::vector<N>& all_nodes,
    std::vector<N>& out_path // filled with [start ... goal] if found, else cleared
) {
    out_path.clear();
    if (start == goal) { out_path = {start}; return true; }

    std::unordered_set<N> visited;
    std::unordered_map<N, N> parent;
    std::queue<N> q;

    visited.insert(start);
    q.push(start);

    while (!q.empty()) {
        N u = q.front(); q.pop();
        // Enumerate neighbors by scanning all nodes and testing adjacency
        for (const N& v : all_nodes) {
            if (visited.count(v)) continue;
            if (!g.adjacent(u, v)) continue;
            visited.insert(v);
            parent[v] = u;
            if (v == goal) {
                // Reconstruct path goal -> start
                std::vector<N> rev;
                for (N cur = goal; ; ) {
                    rev.push_back(cur);
                    if (cur == start) break;
                    cur = parent[cur];
                }
                // reverse
                out_path.assign(rev.rbegin(), rev.rend());
                return true;
            }
            q.push(v);
        }
    }
    return false;
}

// Convenience: your Kevin Bacon number = number of edges in the path
// (i.e., path length minus 1). Returns std::nullopt if no connection.
template <class N, template<class> class G>
std::optional<int> kevinBaconNumber(
    G<N>& g,
    const N& you,
    const std::vector<N>& all_nodes,
    std::vector<N>& out_path // also filled with the path if it exists
) {
    const N KB = N("Kevin Bacon");
    if (!findPathTo(g, you, KB, all_nodes, out_path)) return std::nullopt;
    return static_cast<int>(out_path.size()) - 1; // edges = nodes - 1
}
