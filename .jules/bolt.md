
## 2024-10-24 - Optimized array value-initialization
**Learning:** In C++, native value-initialization of arrays and vectors of arrays is significantly faster than using custom functions like `make_array(0)` to initialize and copy, as it allows the compiler to continuously zero memory directly under the hood.
**Action:** Use value-initialization (e.g. `{}` or `std::vector<std::array<T, N>>(size)`) to zero-fill memory whenever possible instead of explicitly passing zero-filled objects to the constructor.
