## 2024-06-25 - Avoid redundant vector default-initialization
**Learning:** Default initializing `std::vector<std::array<T, N>>` zeroes out all arrays, causing redundant writes if elements are immediately overwritten.
**Action:** Use `reserve()` and `push_back()` with uninitialized `std::array`s when completely filling vectors of arrays to improve performance.
