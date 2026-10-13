## 2024-10-13 - Value initialization over make_array wrapper
**Learning:** Initializing `std::vector<std::array<T, N>>` with a secondary `make_array(0)` wrapper causes performance overhead compared to relying on the default value-initialization of `std::vector` (which natively zeros out the memory rapidly).
**Action:** Always prefer default aggregate initialization (e.g. `std::array<T, N> arr{};`) and single-argument `std::vector` constructors to avoid redundant zeroing overhead.
