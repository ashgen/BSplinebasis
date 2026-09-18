## 2024-05-18 - Optimize array initialization in C++ vector creation
**Learning:** In C++, explicitly passing a zero-filled `std::array` (like `internal::make_array`) as a prototype when instantiating a `std::vector<std::array<T, N>>` disables native fast-path zero-initialization (which reduces to highly optimized `memset`), causing overhead from explicit copy construction.
**Action:** When initializing an array-like container with zeroes, prefer simple value-initialization (`std::vector<std::array<T, N>> v(size);`) over explicit fill/prototype copying.
