## 2024-05-15 - Value-initialization of std::array inside std::vector
**Learning:** Using `std::vector<std::array<T, N>>(size)` natively value-initializes the elements and zeros memory directly, while explicitly passing `make_array(0)` to the vector constructor forces the construction of a temporary prototype and repeatedly copies it into each array, generating overhead.
**Action:** Prefer value-initialization over explicit copies of zeroed arrays.
