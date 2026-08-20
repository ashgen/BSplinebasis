## 2024-05-24 - Optimize array zero-initialization
**Learning:** In C++, native value-initialization for arrays (`std::array<T, N> arr{};`) and native `std::vector` default zero-initialization (`std::vector<std::array<T, N>>(size)`) are significantly faster and generate less overhead than explicitly constructing prototype arrays and copying using functions like `make_array(0)`.
**Action:** When zero-initializing arrays or vectors of arrays, prefer native value-initialization `{}` over explicit fill copies to minimize runtime overhead.
