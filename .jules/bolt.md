## 2024-05-20 - Remove test checks from examples
**Learning:** The `BSPLINE_ADD_TEST_CHECKS` macro introduces severe runtime overhead by executing validity checks and should strictly be limited to test targets. It was incorrectly enabled in `examples/CMakeLists.txt`, causing significant slowdowns (e.g., `examples harmonic_oscillator` runtime dropped from ~0.46s to ~0.04s after removal).
**Action:** Always ensure testing/debugging macros like `BSPLINE_ADD_TEST_CHECKS` are excluded from example or production build configurations.
