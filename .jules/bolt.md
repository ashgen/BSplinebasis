## 2024-05-24 - [Remove BSPLINE_ADD_TEST_CHECKS from examples]
**Learning:** The `BSPLINE_ADD_TEST_CHECKS` macro enables runtime validity checks inside the main spline library code. If this macro is defined in production or example builds, it can cause severe performance overhead (nearly 10x slower for the harmonic oscillator example). It must strictly be limited to tests.
**Action:** Always check the CMake definitions for test-only flags (like `BSPLINE_ADD_TEST_CHECKS`) leaking into example or production targets.
