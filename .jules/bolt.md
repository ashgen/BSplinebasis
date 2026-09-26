## 2023-10-26 - Value Initialization for `std::vector` of `std::array`

**Learning:** When explicitly constructing `std::vector<std::array<T, N>>` with a secondary `value` parameter (like `std::vector<std::array<T, N>>(size, make_array(0))`), the `make_array` is evaluated and copied into each element. But `std::vector(size)` inherently value-initializes each element, and for scalar arrays, value-initialization zero-initializes them continuously using `memset`. This is much faster.

**Action:** Replace `std::vector<std::array<T, N>>(size, make_array(0))` with `std::vector<std::array<T, N>>(size)` and drop explicit assignment when initializing unassigned variables.

## 2023-10-26 - Constexpr mathematical functions

**Learning:** The methods `faculty`, `facultyRatio`, and `binomialCoefficient` in `include/bspline/internal/misc.h` are computationally heavy and used in template classes where the parameters (like polynomial order) are known at compile-time (e.g., `Position<n>::expandPower`). Marking them as `constexpr` allows the compiler to evaluate them during compilation, resulting in faster runtime execution.

**Action:** Add `constexpr` to `faculty`, `facultyRatio`, and `binomialCoefficient` in `misc.h`.
