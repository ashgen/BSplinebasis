## 2023-11-20 - [Performance] Optimize Array Value-Initialization

**Learning:** Explicitly constructing prototype arrays (`make_array(0)`) and copying them into vectors (`std::vector<std::array<T, N>>(size, make_array(0))`) in C++ introduces significant overhead compared to simply using value-initialization (`std::vector<std::array<T, N>>(size)`). Value-initialization zeroes the memory continuously and natively, whereas `make_array` with `.fill(0)` operates at the object level and involves copying.
**Action:** Replace uses of `make_array<T, N>(static_cast<T>(0))` with value-initialized local arrays or vectors where a specific explicit fill isn't required and zeroing is sufficient.
