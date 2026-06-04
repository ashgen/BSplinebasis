## 2024-06-04 - [Optimized linearCombination inner loop]
**Learning:** Found significant overhead in the tight inner loop of `linearCombination` due to bounds-checking (`.at()`) and index translation methods (`absoluteFromRelative`, `intervalIndexFromAbsolute` which return std::optional) on numerical arrays.
**Action:** When operating on mathematical arrays where bounds are statically/logically guaranteed, prefer hoisting calculations and using direct index access (`[]`) to avoid C++ function call and boundary checking overhead in hot loops.
