## 2024-07-24 - Value-initialize std::array Instead of Explicit .fill(0)
**Learning:** In C++, value-initializing a `std::array` (e.g., `std::array<T, N> arr{};`) allows the compiler to optimize the zeroing out of memory more effectively than default-initializing and explicitly zero-filling it (e.g., `arr.fill(0)`).
**Action:** Prefer `std::array<T, N> arr{};` over explicit zero-filling when creating arrays that require zeroing out prior to operations.
