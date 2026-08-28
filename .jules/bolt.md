## 2024-11-20 - Avoid copying prototype arrays for vector initialization
**Learning:** Initializing `std::vector<std::array<T, N>>` with a prototype array (e.g. `make_array<T, N>(0)`) incurs heavy memory overhead and copying penalties. C++ `std::vector(size)` naturally zero-initializes its elements continuously and is over 3x faster than explicit `array.fill()` construction.
**Action:** Always prefer native `{}` value-initialization and default constructor for standard library containers instead of creating helper functions to build array prototypes for element filling.
