## 2024-07-01 - [Remove BSPLINE_ADD_TEST_CHECKS from production code]
**Learning:** The `BSPLINE_ADD_TEST_CHECKS` macro introduces severe runtime overhead by executing validity checks and should strictly be limited to test targets (e.g., `tests/CMakeLists.txt`), never examples or production builds.
**Action:** Always ensure test-only macros are scoped properly and not leaking into production builds or examples.
