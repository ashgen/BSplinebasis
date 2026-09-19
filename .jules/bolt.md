## 2024-05-18 - [Optimize std::vector<std::array> initialization]
**Learning:** Using `make_array(0)` to explicitly construct prototype arrays for `std::vector<std::array<T, N>>` constructor is significantly slower because it copies the prototype array. Using the constructor `std::vector<std::array<T, N>>(size)` natively value-initializes elements (effectively zeroing memory) and often reduces to a highly optimized `memset`.
**Action:** Use value-initialization (`std::vector<std::array<T, N>>(size)`) for arrays instead of explicit filling when constructing vectors of zeroed arrays.
