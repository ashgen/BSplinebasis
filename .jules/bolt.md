## 2024-05-13 - Exploration
**Learning:** Initializing exploration.
**Action:** Need to find optimizations.

## 2024-05-13 - Arrays of Plain Old Data (POD) Value-Initialization Overhead
**Learning:** Found that using explicit zero-initialization functions like `make_array<T, N>(0)` or even value-initialization `std::array<T, N> arr{}` introduces an O(N) zeroing overhead. When the entire array is subsequently explicitly populated with values in a loop (e.g. accumulating matrix products, polynomial coefficients, or summing arrays), this initial zeroing is completely redundant and slows down execution.
**Action:** Replace explicit zeroing (like `internal::make_array<T, N>(static_cast<T>(0))`) with uninitialized default-initialization (`std::array<T, N> arr;`) when *all* elements are unconditionally overwritten, or rely on `std::array<T, N> arr{};` directly in place of function wrappers for cleaner scalar zeroing if zeroing is truly required. For vectors of arrays, prefer `std::vector<std::array<T, N>> vec(size)` over filling with prototypes to let the allocator use optimized zeroing.
