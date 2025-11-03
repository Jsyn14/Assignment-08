#pragma once
#include <vector>
#include <unordered_set>

template <class N, template<class> class G>
bool isSimpleCycle(G<N>& g, const std::vector<N>& path) {
    if (path.size() < 4) return false;
    if (path.front() != path.back()) return false;

    std::unordered_set<N> seen;
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        const N& u = path[i];
        const N& v = path[i + 1];
        if (seen.count(u)) return false;
        seen.insert(u);
        if (!g.adjacent(u, v)) return false;
    }
    return seen.size() >= 3;
}
