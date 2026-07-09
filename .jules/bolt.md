## 2024-05-18 - [Remove BSPLINE_ADD_TEST_CHECKS from Examples]
**Learning:** The `BSPLINE_ADD_TEST_CHECKS` macro introduces severe runtime overhead by executing validity checks and should strictly be limited to test targets, never examples or production builds.
**Action:** Remove `BSPLINE_ADD_TEST_CHECKS` from `examples/CMakeLists.txt` to improve performance.
