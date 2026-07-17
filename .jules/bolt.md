## 2024-07-17 - Prefer value-initialization for std::array
**Learning:** In C++, value-initializing an array `std::array<T, N> arr{};` is more performant than default initialization followed by an explicit zero-filling `arr.fill(0)` when initializing arrays to 0.
**Action:** Always prefer value-initialization for arrays over default-initialization followed by `.fill(0)`.
