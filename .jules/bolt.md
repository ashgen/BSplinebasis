## 2026-08-02 - Array Value Initialization Overhead
**Learning:** In C++, using std::vector initialization with a default value (like make_array) introduces redundant zero-writes when elements are going to be overwritten immediately anyway, which yielded a ~9% slowdown in benchmarks compared to manual push_back.
**Action:** Use reserve+push_back with uninitialized local arrays for tight loops if it's guaranteed every element gets overwritten.
