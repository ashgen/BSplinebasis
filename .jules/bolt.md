## 2024-05-18 - Avoid O(N) zeroing on overwritten POD arrays
**Learning:** For arrays of plain old data (POD) types that will be immediately and entirely overwritten, value initialization (`std::array<T, N> arr{};`) introduces an unnecessary O(N) zeroing step that degrades performance.
**Action:** Use default initialization (`std::array<T, N> arr;`) instead of value initialization, and ensure all elements are assigned. Also consider `constexpr` for pure math functions.
