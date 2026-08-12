## 2026-08-12 - [Optimize array initialization]
**Learning:** Found that `std::vector<std::array<T, N>> v(size)` performs redundant value-initialization of every array element, which introduces overhead if the elements are immediately overwritten.
**Action:** Use `reserve` and `push_back` with an uninitialized local `std::array` when all elements will be unconditionally overwritten, preventing undefined behavior while improving performance.
