## 2024-08-10 - Avoid redundant zero-initialization of std::array
**Learning:** Constructing a std::vector of std::array using the size constructor triggers value-initialization of all elements, adding runtime overhead when the elements are immediately overwritten.
**Action:** Use std::vector::reserve and push_back with uninitialized local arrays for performance-critical loops where every element is guaranteed to be initialized before use.
