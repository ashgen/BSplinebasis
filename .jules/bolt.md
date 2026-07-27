## 2024-07-28 - [Array value-initialization]
**Learning:** In C++, value-initialization (`std::array<T, N> arr{};`) is faster than default initialization followed by `arr.fill(0)` because it avoids a double-initialization overhead and can be better optimized by the compiler.
**Action:** Always prefer value-initialization for std::array when a zeroed array is required.
