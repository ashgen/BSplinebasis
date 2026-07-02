## 2024-06-25 - Remove Test Checks from Production Examples
**Learning:** `BSPLINE_ADD_TEST_CHECKS` adds significant runtime overhead in example code (runtime dropped from ~0.45s to ~0.03s after removal). This macro should be strictly limited to test environments.
**Action:** When working on C++ macros, investigate their impact in non-test targets and ensure development/test assertion macros are excluded from examples and production binaries.
