## 2024-07-04 - [Remove BSPLINE_ADD_TEST_CHECKS from examples/CMakeLists.txt]
**Learning:** The `BSPLINE_ADD_TEST_CHECKS` macro adds validity checks meant only for tests, causing a severe 10x overhead when building examples (e.g. 0.463s vs 0.037s for the harmonic oscillator).
**Action:** When working on performance, watch out for test-only or debug-only macros in release builds or non-test targets.
