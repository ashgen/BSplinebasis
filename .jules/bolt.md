## 2024-05-24 - Pure mathematical utility functions as constexpr
**Learning:** Marking pure mathematical utility functions (e.g., factorials, binomial coefficients) as `constexpr` in a C++ codebase allows the compiler to perform constant folding at compile-time when parameters are known (like template arguments or fixed polynomial orders), significantly reducing runtime loop overhead.
**Action:** Always check if pure mathematical functions can be made `constexpr` in C++ codebases to enable compile-time optimizations.
