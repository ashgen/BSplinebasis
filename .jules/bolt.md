## 2024-08-04 - [Optimize std::vector<std::array> initialization]
**Learning:** Default-initializing `std::vector<std::array<T, N>>` zeroes out all arrays, which creates redundant writes if every element is completely overwritten later.
**Action:** Use `.reserve()` and `.push_back()` with uninitialized local arrays (or directly computed results) to avoid the overhead of zero-filling memory that is immediately replaced.
