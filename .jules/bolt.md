## 2024-07-26 - [Use value-initialization for arrays instead of fill(0)]
**Learning:** In C++, prefer value-initialization (e.g., `std::array<T, N> arr{};`) over explicit zero-filling (`arr.fill(0)`), except when it causes redundant writes (like in array resizing/copying).
**Action:** Use value-initialization for zeroing out arrays when declaring them unless they are immediately completely overwritten.
