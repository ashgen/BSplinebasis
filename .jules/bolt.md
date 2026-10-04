## 2024-05-24 - Initializing Journal
**Learning:** Initializing journal for Bolt optimization tasks.
**Action:** Always start by reading or creating this file.

## 2024-05-24 - Array Value-Initialization Optimization
**Learning:** In C++, `std::vector<std::array<T, N>>(size)` automatically value-initializes all elements continuously in memory (effectively a fast `memset`). Explicitly setting elements using an initialized `std::array` inside a loop (like using `make_array<T, N>(0)`) after vector allocation is completely redundant and causes a measurable ~2x performance degradation due to unneeded overwriting overhead.
**Action:** When a zero-initialized array vector is needed, simply construct the vector with `size` and omit loop-based explicit initialization. For local single arrays, prefer `std::array<T, N> arr{};` over explicit fill methods.
