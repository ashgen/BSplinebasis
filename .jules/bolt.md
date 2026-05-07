## 2024-05-07 - Avoid unnecessary bounds checking in hot loops
**Learning:** In C++, accessing members through `intervalIndexFromAbsolute` or `absoluteFromRelative` which perform boundary checks using `DURING_TEST_CHECK_VALIDITY()` inside tight loops (like bilinear integration form evaluations) causes severe performance bottlenecks.
**Action:** When working in hot inner loops, compute bounds or start indices once before the loop and use direct array accesses (`grid[index]`) and pointer arithmetic rather than using safe-access wrappers that recalculate boundaries.
