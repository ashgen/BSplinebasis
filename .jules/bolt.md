## 2024-05-14 - Redundant array value-initialization in vectors

**Learning:** When `std::vector<std::array<T, N>>` is constructed with a size argument (e.g. `std::vector<std::array<T, N>>(size)`), all its elements are natively and efficiently value-initialized (meaning scalar arrays are zero-initialized) automatically, often optimized into a `memset`. Code in this repository redundantly allocates and fills a vector by explicitly passing a zeroed array via `internal::make_array(0)` to the vector constructor: `std::vector<std::array<T, ARRAY_SIZE>> ncoefficients(size, internal::make_array<T, ARRAY_SIZE>(static_cast<T>(0)))`. This introduces significant, measurable overhead over just calling `std::vector<std::array<T, ARRAY_SIZE>> ncoefficients(size)`.

**Action:** Remove the explicit `internal::make_array` arguments when initializing zeroed vectors of arrays in `bspline::Spline`.
