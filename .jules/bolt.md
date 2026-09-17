## 2024-05-13 - [Value initialization of arrays]
**Learning:** In C++, using value initialization `std::vector<std::array<T, N>>(size)` is significantly faster than filling a vector with copies of an explicitly constructed array `std::vector<std::array<T, N>>(size, internal::make_array<T, N>(static_cast<T>(0)))` since it can compile down to memset.
**Action:** Use value initialization instead of explicit construction when zero-initializing an array container, as long as it handles zeroing properly.
