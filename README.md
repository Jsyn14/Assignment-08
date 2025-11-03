# Simple Cycle Checker

This bundle adds a header-only function `isSimpleCycle` and a test program
that exercises it against both the adjacency-list and adjacency-matrix
graph implementations.

## Build & Run (CMake)
```bash
cd graph_cycle_check
cmake -S . -B build
cmake --build build
./build/test_cycle
```

## Quick Compile (no CMake)
```bash
g++ -std=c++17 test_is_simple_cycle.cpp -o test_cycle && ./test_cycle
```

## Function contract
```cpp
template <class N, template<class> class G>
bool isSimpleCycle(G<N>& g, const std::vector<N>& path);
```
*Returns true iff:*
- `path.size() >= 4`
- `path.front() == path.back()`
- Every hop `(path[i] -> path[i+1])` is an edge in `g`
- No node (except the final repeat of the start) appears more than once

The function is generic over node type `N` and works with both provided graph
implementations via their `adjacent(u,v)` method.
