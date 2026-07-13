## 2024-07-13 - Remove BSPLINE_ADD_TEST_CHECKS outside of tests
**Learning:** The `BSPLINE_ADD_TEST_CHECKS` macro enables validity checking that introduces severe runtime overhead (e.g. from 0.45s down to 0.03s for `harmonic_oscillator` example).
**Action:** Ensure `BSPLINE_ADD_TEST_CHECKS` is strictly limited to test targets and never used for production builds or examples.
