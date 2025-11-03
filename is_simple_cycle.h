#pragma once
#include <vector>
#include <unordered_set>

// Works with any Graph type G<N> that exposes: bool adjacent(const N& u, const N& v)
template <class N, template<class> class G>
bool isSimpleCycle(G<N>& g, const std::vector<N>& path) {
    // Need at least three distinct vertices and a closing repeat => length >= 4 (e.g., 1-2-3-1)
    if (path.size() < 4) return false;
    if (path.front() != path.back()) return false; // must be closed

    std::unordered_set<N> seen;

    // Check each hop is a valid edge and ensure each vertex (except the last == first) is unique
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        const N& u = path[i];
        const N& v = path[i + 1];

        if (seen.count(u)) return false;     // repeats in the middle are forbidden
        seen.insert(u);

        if (!g.adjacent(u, v)) return false; // invalid step
    }

    // Ensure the cycle actually used >=3 distinct vertices
    return seen.size() >= 3;
}
