## 2024-05-14 - Optimize array value-initialization

**Learning:** When explicitly constructing a `std::vector` of `std::array` elements in C++, specifying a zero-initialized array as the default value (`std::vector<std::array<T, N>>(size, make_array(0))`) forces the compiler to explicitly copy the prototype array for every element. However, using value-initialization by only passing the size (`std::vector<std::array<T, N>>(size)`) zeroes the memory continuously during allocation, which is significantly faster.

**Action:** Replace explicit zero-initialization (using `make_array`) with native value-initialization when initializing vectors of standard arrays in C++, provided the compiler's default value-initialization semantics (zero-filling for scalar types) are exactly what is needed.
