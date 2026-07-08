## 2024-06-25 - Remove BSPLINE_ADD_TEST_CHECKS overhead
**Learning:** The `BSPLINE_ADD_TEST_CHECKS` macro introduces severe runtime overhead by executing validity checks and should strictly be limited to test targets, never examples or production builds.
**Action:** When working on performance, watch out for test or debug macros creeping into production or example build flags.
