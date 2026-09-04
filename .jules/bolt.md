## 2024-05-24 - [Value initialization of std::vector of arrays vs explicit prototyping]
**Learning:** In C++, native value-initialization when sizing a std::vector of std::arrays is faster than constructing a zero-prototype explicitly via make_array to fill it. Additionally, value-initializing local arrays zeroes unassigned elements faster than a secondary manual assignment loop.
**Action:** Rely on `std::vector<T>(size)` for native zero-allocation instead of manual loop filling or prototyped initialization where `T` is an array.
