## 2024-09-09 - [Optimize Array Initialization]
**Learning:** Using explicit construction of prototype arrays for vector initialization (`std::vector<std::array<T, N>>(size, internal::make_array<T, N>(0))`) is much slower than utilizing `std::vector`'s default constructor (`std::vector<std::array<T, N>>(size)`) which natively zeroes the continuous memory chunk without copying a prototype object.
**Action:** Always prefer value-initialization `{}` or default constructor initialization for zeroing arrays and vector of arrays in C++ to rely on native contiguous memory initialization.
