## 2025-01-01 - [Fast Array Initialization]
**Learning:** Using explicit zero-filling `make_array<T, N>(0)` in `std::vector` constructors is significantly slower than relying on default value-initialization `std::vector<std::array<T, N>>(size)`. The latter resolves to an optimized memory allocation directly zeroing memory in C++.
**Action:** Use value-initialization for arrays instead of explicitly creating zero-filled arrays to pass as prototypes.
