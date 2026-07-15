## 2024-05-15 - Array value-initialization
**Learning:** In C++, prefer value-initialization for arrays (e.g., `std::array<T, N> arr{};`) over explicit zero-filling (e.g., `arr.fill(0)`). Value-initialization allows the compiler to optimally zero out memory, avoiding unnecessary loops or instructions in tight mathematical execution loops.
**Action:** Always use `{}` initialization for numeric `std::array`s when starting from a zeroed state.
