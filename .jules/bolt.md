## Bolt's Journal

## 2025-02-23 - Optimize array value-initialization
**Learning:** `std::vector<std::array<T, N>>` automatically value-initializes elements, and constructing explicit arrays with `make_array(0)` to fill it creates overhead. Value-initialization with `{}` for local arrays is also more performant than calling custom initialization wrappers.
**Action:** Use `std::vector<std::array<T, N>>(size)` without an explicit fill object when elements should be zeroed, and prefer aggregate initialization (`std::array<T, N> arr{};`) for local arrays.
