## 2024-10-05 - Optimize array initialization in BSpline vectors

**Learning:** When generating large vectors of fixed-size C++ arrays (e.g., `std::vector<std::array<T, N>>(size, make_array(0))`), using a custom initialization function returning a zero-filled array prevents the standard library from leveraging `memset`-like optimizations. The `std::vector` constructor `std::vector<T>(size)` natively value-initializes all elements, which is significantly faster and inherently zeroes out scalar types. Furthermore, explicit reassignment inside a loop of a value-initialized vector using `make_array` adds significant overhead.

**Action:** Replace `internal::make_array(0)` inside `std::vector` constructors with default initialization, and replace reassignments inside loops with `std::array<T, N>{}` (aggregate initialization).
