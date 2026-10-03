## 2024-05-01 - Init
**Learning:** Initialize journal.
**Action:** Always measure first.
## 2024-05-01 - Optimizing array value-initialization
**Learning:** In C++17, explicitly initializing an `std::array` with a zero-filled `make_array(0)` helper inside vectors, or relying on `make_array(0)` for zero-initialization causes overhead compared to using aggregate initialization (`std::array<T, N>{}`). Furthermore, when initializing a `std::vector` of `std::array`s with a size parameter, standard value-initialization already zeroes the arrays, meaning explicitly zeroing them afterwards with `make_array(0)` is completely redundant overhead.
**Action:** Replace `internal::make_array<T, SIZE>(static_cast<T>(0))` with aggregate initialization `std::array<T, SIZE>{}` in `include/bspline/Spline.h` and `include/bspline/operators/SplineOperator.h` where array construction or assignment happens, saving redundant construction overhead.
