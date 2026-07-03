## 2026-07-03 - Remove debug overhead in examples
**Learning:** The `BSPLINE_ADD_TEST_CHECKS` macro introduces severe runtime overhead in production builds, executing validity checks that should be strictly limited to test environments.
**Action:** Always verify that test-specific definitions are not included in non-test targets like examples or production builds.
