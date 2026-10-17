## 2024-10-17 - Optimize array resizing and math utilities
**Learning:** C++17 `std::array` value-initialization (`std::array<T, N> arr{};`) is faster than explicit function-based zero-filling, and constexpr mathematical utility functions permit constant folding reducing runtime overhead.
**Action:** When initializing arrays, prefer aggregate initialization. Mark pure math utilities as `constexpr` to allow compile-time evaluation.
