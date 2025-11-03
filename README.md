# Graph ADT Headers

This archive contains three headers implementing a generic Graph interface,
plus list- and matrix-backed implementations.

Files:
- Graph.h — pure virtual interface.
- AdjListGraph.h — adjacency list implementation (unordered_map< N, vector<N> >).
- AdjMatrixGraph.h — adjacency matrix implementation (vector<vector<bool>>).

Usage:
```cpp
#include "Graph.h"
#include "AdjListGraph.h"
#include "AdjMatrixGraph.h"
```

Notes:
- Both implementations accept a `bool directed` flag (default: true).
- For the matrix version, `neighbors(x)` returns a reference to an internal
  scratch vector. Use it immediately; do not store the reference.
