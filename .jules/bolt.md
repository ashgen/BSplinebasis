
## 2024-05-24 - Precomputing binomial coefficients at compile time
**Learning:** Pure mathematical utility functions like `binomialCoefficient` and `faculty` can be marked as `constexpr`. By combining this with an immediately-invoked lambda in C++17, we can precompute arrays of binomial coefficients at compile time rather than recalculating them repeatedly at runtime in tight loops.
**Action:** Always look for opportunities to mark stateless mathematical formulas as `constexpr`. For arrays, use a `constexpr auto arr = [](){ ... }()` pattern to populate and return the array at compile time.
