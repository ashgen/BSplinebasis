## 2024-05-24 - Optimization Context Setup
**Learning:** Initializing journal for tracking.
**Action:** Always start with profiling.

## 2024-05-24 - Remove `BSPLINE_ADD_TEST_CHECKS` from examples
**Learning:** `BSPLINE_ADD_TEST_CHECKS` adds significant runtime overhead (validity checks). It should never be enabled for performance builds or examples.
**Action:** When building examples or running in production, ensure `BSPLINE_ADD_TEST_CHECKS` is not in target definitions.
