# Graph ADT Headers

This archive contains three headers implementing a generic Graph interface,
plus list- and matrix-backed implementations.

Files:
- Graph.h
- AdjListGraph.h
- AdjMatrixGraph.h

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
