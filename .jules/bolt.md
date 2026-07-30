## 2024-07-30 - [Array Value-Initialization]
**Learning:** Explicitly zero-filling arrays via `.fill(0)` adds unnecessary overhead and compiler burden over direct value-initialization `{}` for accumulators.
**Action:** Prefer `std::array<T, N> arr{};` when an array needs to be fully zero-initialized before accumulator operations.
