## 2024-05-24 - Constexpr Math Utilities Performance
**Learning:** Pure mathematical utility functions (like factorials and binomial coefficients) used in template classes where order is known at compile-time must be marked `constexpr` in C++ to allow aggressive compiler constant folding, avoiding expensive loop/branch runtime overhead.
**Action:** Always mark pure functions operating on loop iterators or template sizes as `constexpr` when possible.
