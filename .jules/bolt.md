## 2024-08-16 - [Optimize Array Initialization]
**Learning:** In C++, value-initializing a vector of arrays (`std::vector<std::array<T, N>>(size)`) zero-fills memory directly and is significantly faster than passing an explicitly zero-filled array (e.g. via `make_array(0)`) to the vector constructor, which forces repeated copies.
**Action:** Always prefer value-initialization (`std::vector<std::array<...>>(size)`) for zeroing large memory blocks over explicit manual array construction and copy.
