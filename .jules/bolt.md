## 2024-05-24 - Zero-initialization optimization
**Learning:** Value-initialization `std::array<T, N> retVal{};` can be noticeably faster than explicit `fill()` or looping over elements to zero them out, specifically because it gets optimized into `memset` or unrolled vector instructions more cleanly in many compilers for C++ local arrays.
**Action:** Prefer aggregate initialization (`std::array<T, N> arr{};`) when an array needs to be fully initialized to zero at creation.
