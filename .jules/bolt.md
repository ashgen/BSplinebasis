## 2024-12-04 - Initial Optimization
**Learning:** Found explicit array initialization via `make_array` in inner loops when computing spline operations, which introduces a measurable overhead compared to fast zero-initialization via std::vector default construction which inherently value-initializes the elements.
**Action:** When initializing arrays to zero in C++, prefer default value-initialization (`std::vector<std::array<T, N>>(size)`) over explicit construction using a custom `make_array` pattern, as the compiler is much better at optimizing default value-initialization.
