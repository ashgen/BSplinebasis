## 2024-09-08 - Optimize Array Initialization
**Learning:** In C++, using `std::vector<std::array<T, N>>(size)` natively zeroes memory continuously and is significantly faster than explicitly constructing prototype arrays and copying (e.g., using `make_array(0)`).
**Action:** Always prefer value-initialization for arrays (`std::array<T, N> arr{};`) over explicit zero-filling, and utilize the vector size constructor for initializing vectors of arrays.
