## 2024-11-20 - [Performance Optimization] C++ Uninitialized std::array performance
**Learning:** Initializing large collections of zero-filled `std::array` inside inner loops (like inside `operator+`, `operator=`) takes unnecessary cycles compared to uninitialized arrays or `.reserve()` & uninitialized variables `std::array<T, N> arr;` and loop assignment, provided all elements are strictly overwritten.
**Action:** Replace `internal::make_array` with uninitialized arrays (or value initialization/assignment inside) in highly accessed operators like `operator+` or `operator*` in `Spline.h`.
