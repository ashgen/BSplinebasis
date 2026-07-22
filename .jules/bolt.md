## 2024-07-22 - Optimizing array value-initialization
**Learning:** `std::array<T, size> arr; arr.fill(0)` compiles to more operations than value-initialization `std::array<T, size> arr{};` in standard arrays due to explicit loop assignments depending on optimization levels.
**Action:** Replace `std::array` zero-filling with value-initialization wherever applicable, while avoiding pessimization from initializing elements that will be completely overwritten shortly after.
