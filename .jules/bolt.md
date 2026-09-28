## 2024-05-25 - C++ `std::vector` default initialization performance

**Learning:** When a `std::vector` is constructed with a size argument (e.g., `std::vector<std::array<T, N>>(size)`), its elements are automatically value-initialized (which zero-initializes scalar types). Explicitly looping to assign zeroed arrays using `make_array(0)` or aggregate initialization `{}` is redundant, causes runtime overhead by doing double initialization, and disables potential vector optimizations (like memset) under the hood.

**Action:** When creating a vector of value-initialized structs or arrays, rely on the vector's constructor rather than manually overwriting values with zeroed objects.
