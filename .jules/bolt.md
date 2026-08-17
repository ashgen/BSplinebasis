## 2024-05-24 - [Value initialization vs Explicit Fill in Vectors]
**Learning:** In C++, constructing a vector of arrays using an explicitly filled instance (like `std::vector<std::array<T, N>>(size, make_array(0))`) evaluates and copies the filled array, generating significant overhead. Using native value-initialization (`std::vector<std::array<T, N>>(size)`) natively zeros the memory continuously, which is demonstrably faster.
**Action:** Default to simple value-initialization when allocating zeroed arrays inside vectors to avoid explicit object copying.
