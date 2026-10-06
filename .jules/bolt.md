## 2024-05-24 - Initial Bolt Journal
**Learning:** Initializing journal to log critical learnings and insights for performance optimizations in this repository.
**Action:** Always consider codebase specific performance patterns when reviewing performance metrics.

## 2024-05-24 - Array Value-Initialization Optimization
**Learning:** In C++, explicit function-based zero-filling of arrays (like `make_array<T, N>(0)`) is no faster and often less optimal for compiler inlining than simple aggregate initialization (`std::array<T, N>{}`). Furthermore, when initializing a `std::vector` of `std::array`s, passing an explicitly zero-initialized array to the constructor (e.g., `std::vector<std::array<T, N>>(size, make_array(0))`) forces a copy-initialization loop, which is significantly slower than value-initialization via the size constructor alone (`std::vector<std::array<T, N>>(size)`). Value-initialization zeroes the memory optimally, often reducing to a fast continuous memory clear (like `memset`).
**Action:** Replace `make_array(0)` usages with value-initialization or aggregate initialization where applicable to improve allocation and initialization speeds, particularly for large vectors of arrays.
