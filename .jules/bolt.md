## 2024-07-05 - Remove BSPLINE_ADD_TEST_CHECKS from examples
**Learning:** Adding test assertion macros to compile definitions in example code or production builds introduces severe runtime overhead.
**Action:** Always ensure that macros like `BSPLINE_ADD_TEST_CHECKS` which run intensive validity checks are limited strictly to test targets in `CMakeLists.txt`.
