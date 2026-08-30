## 2024-08-30 - Native Value-Initialization over Prototype Arrays
**Learning:** In C++, explicitly zero-filling a vector of arrays using a constructed prototype array (e.g., `make_array(0)`) is less efficient than relying on native value-initialization (e.g., `std::vector<std::array<T, N>>(size)` or `std::array<T, N> arr{}`). Native value-initialization allows the compiler to natively and continuously zero out memory, which avoids overhead.
**Action:** Always prefer native value-initialization for arrays and vectors of arrays instead of explicitly constructing and copying a prototype array.
