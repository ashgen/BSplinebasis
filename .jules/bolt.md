## 2024-07-23 - Value-initialization for std::array
**Learning:** In C++, value-initializing an array (`std::array<T, N> arr{};`) can avoid the extra function call overhead of explicit zero-filling (`arr.fill(0)`) while maintaining correctness.
**Action:** Prefer value-initialization for `std::array` when the entire array needs to be zeroed out before being partially populated, but avoid it when the array will be immediately completely overwritten.
