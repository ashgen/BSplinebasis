## 2024-11-05 - Precompute complex maths at compile time with constexpr and std::index_sequence
**Learning:** Mathematical functions like factorials and binomial coefficients, when dependent solely on template parameters, are computed at runtime if not marked `constexpr`.
**Action:** Mark math functions `constexpr` and use `std::index_sequence` alongside parameter packs to precompute unrolling structures like `std::array` at compile time, eliminating redundant calculation overheads during hot-loop invocations like the generic operator transforms.
