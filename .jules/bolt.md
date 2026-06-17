## 2024-06-12 - Spline evaluation bottleneck

**Learning:** For typical spline grid evaluation where `findInterval` is heavily utilized to locate the proper interval for evaluation, a linear search substantially outperforms binary search (`std::lower_bound`) when the grid / support size is small (<= 64). This is due to binary search suffering from branch prediction penalties and lack of memory prefetching on tiny arrays compared to linear scan.

**Action:** Whenever identifying elements in small bounded ordered arrays (typically under 64 elements), consider checking if a simple linear scan is faster than standard binary searches before assuming binary search is best.
