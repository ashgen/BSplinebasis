## 2024-05-24 - [Value initialization of arrays]
**Learning:** In C++, `std::vector<std::array<T, N>>(size)` natively zeroes memory continuously and is significantly faster than explicitly constructing prototype arrays and copying (e.g., using `make_array(0)`), often reducing to a highly optimized `memset` under the hood.
**Action:** Prefer using `std::vector<std::array<T, N>>(size)` for value-initialization over explicit zero-filling.
