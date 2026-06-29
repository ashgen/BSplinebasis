## 2024-06-29 - Remove BSPLINE_ADD_TEST_CHECKS from Examples
**Learning:** The `BSPLINE_ADD_TEST_CHECKS` macro in `examples/CMakeLists.txt` introduces severe runtime overhead (from ~0.476s to ~0.038s in `harmonic_oscillator` example, an order of magnitude slower). It executes costly validity checks intended only for the test suite.
**Action:** Always ensure debug/test specific macros that add significant runtime assertions are excluded from production or example targets where performance is measured or demonstrated.
