## 2024-05-23 - [C++ Array Value-Initialization]
**Learning:** In C++, `std::vector<std::array<T, N>>(size)` natively zeroes out elements continuously in memory and is significantly faster than using `make_array(0)` to build a prototype and copy it into the vector.
**Action:** Always prefer value-initialization for standard containers like arrays when zero-filling over manually generating and copying an explicitly zeroed array structure.
