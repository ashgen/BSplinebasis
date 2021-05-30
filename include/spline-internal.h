#ifndef MYSPLINE_INTERNAL_H
#define MYSPLINE_INTERNAL_H
#include <assert.h>
#include <memory>
#include <optional>
#include <vector>

/*
 * ########################################################################
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * ########################################################################
 */

namespace myspline::internal {

/*!
 * Represents a global grid.
 *
 * @tparam T The datatype of the grid elements.
 */
template <typename T> class grid {
private:
  size_t _size; /*! Number of elements of the global grid. */
  std::shared_ptr<const T[]> _data; /*! Shared pointer to the data. */

  /*!
   * Generates the shared pointer to an array from two iterators.
   *
   * @param begin The iterator referencing the first element to be copied into
   * the grid.
   * @param end The iterator referencing the element behind the last element to
   * be copied into the grid.
   * @returns A shared pointer to a dynamic array, holding the grid elements.
   */
  template <typename Iter>
  std::shared_ptr<const T[]> generateData(Iter begin, Iter end) {
    T *dat = new T[_size];
    for (size_t i = 0; i < _size; i++) {
      dat[i] = *(begin + i);
    }
    return std::shared_ptr<const T[]>(dat);
  }

public:
  /*!
   * Default constructor, constructing an empty grid.
   */
  grid() : _size(0){};

  /*!
   * Constructs a grid from two iterators. The first element of the grid will be
   * the element referenced by begin. The last element of the grid will be the
   * one before the element pointed to by end;
   *
   * @param begin The iterator referencing the first element to be copied into
   * the grid.
   * @param end The iterator referencing the element behind the last element to
   * be copied into the grid.
   * @tparam Iter The type of the two iterators.
   */
  template <typename Iter>
  grid(Iter begin, Iter end)
      : _size(std::distance(begin, end)), _data(generateData(begin, end)){};

  /*!
   * Constructs a grid from a std::vector. The elements of the vector are
   * copied, not moved.
   *
   * @param v The input vector.
   */
  grid(const std::vector<T> &v) : grid(v.begin(), v.end()){};

  /*!
   * Constructs a grid by setting its members.
   *
   * @param size The size of the grid.
   * @param data A shared pointer to the grid elements.
   */
  grid(size_t size, std::shared_ptr<const T[]> data)
      : _size(size), _data(std::move(data)){};

  grid(const grid &g) = default;
  grid(grid &&g) = default;
  grid &operator=(const grid &g) = default;
  grid &operator=(grid &&g) = default;

  /*!
   * Comparison operator.
   *
   * @param g The grid to compare this grid with.
   * @returns Returns true if the grids represent the same logical grid.
   */
  bool operator==(const grid &g) const {
    if (_data == g._data && _size == g._size)
      [[likely]] return true;
    else if (_size != g._size)
      return false;
    for (size_t i = 0; i < _size; i++)
      if (_data[i] != g._data[i])
        return false;
    return true;
  }

  /*!
   * Returns the number of elements of the grid.
   */
  size_t size() const { return _size; };

  /*!
   * Returns a shared pointer to the elements of this grid.
   */
  std::shared_ptr<const T[]> getData() const { return _data; };

  /*!
   * Checks whether this spline holds no elements.
   *
   * @returns Returns true if this grid holds no element.
   */
  bool empty() const { return _size == 0; };

  /*!
   * Returns a reference to the ith element of the grid. Performs no bounds
   * checks.
   *
   * @param i The index of the element to be returned.
   * @returns A reference to the ith element.
   */
  const T &operator[](size_t i) const { return _data[i]; };

  /*!
   * Returns a reference to the ith element of the grid. Checks the bounds.
   *
   * @param i The index of the element to be returned.
   * @returns A reference to the ith element.
   */
  const T &at(size_t i) const {
    assert(i < _size);
    return _data[i];
  };

  /*!
   * Returns a reference to the first element of the grid.
   *
   * @returns A reference to the first element.
   */
  const T &front() const {
    assert(_data && _size > 0);
    return _data[0];
  };

  /*!
   * Returns a reference to the last element of the grid.
   *
   * @returns A reference to the last element.
   */
  const T &back() const {
    assert(_data && _size > 0);
    return _data[_size - 1];
  };
};

/*!
 * Represents the support of a spline as a number of gridpoints.
 * It is hence essentially a view onto the global grid. The pointer to the
 * global grid allows for a speedy comparison whether splines are defined on the
 * same global grid and methods that assume they are can be used.
 *
 * @tparam T Datatype of the grid and spline.
 */
template <typename T> class support {
private:
  grid<T> _grid;      /*! Represents the global grid. */
  size_t _startIndex; /*! Represents the begin of the support. */
  size_t _endIndex; /*! Represents the end of the support. Points to the element
                       behind the last element of the support. */

public:
  /*!
   * Represents an interval relative to the global grid represented by _grid.
   */
  using AbsoluteIndex = size_t;

  /*!
   * Represents an interval relative to the intervals contained in this support.
   */
  using RelativeIndex = size_t;
  /*!
   * This enum allows to signal to some constructors whether
   * an empty support should be constructed or one representing the
   * whole grid.
   */
  enum class Construction { EMPTY, WHOLE_GRID };

  /*!
   * Constructs a support relative to the global grid grid.
   *
   * @param grid The global grid.
   * @param startIndex The index of the first grid point which is part of the
   * support.
   * @param endIndex The index of the element behind the last grid point which
   * is part of the support.
   */
  support(grid<T> grid, size_t startIndex, size_t endIndex)
      : _grid(std::move(grid)), _startIndex(startIndex), _endIndex(endIndex) {
    assert(_endIndex >= _startIndex && _endIndex <= _grid.size());
  };

  /*!
   * Constructs an empty support relative to the global grid grid.
   *
   * @param grid The global grid.
   * @param con The construction. If this parameter is not provided, an empty
   * support will be constructed, if it is set to Construction::WHOLE_GRID a
   * support representing the extend of the whole grid will be constructed.
   */
  support(grid<T> grid, Construction constr = Construction::EMPTY)
      : _grid(std::move(grid)), _startIndex(0),
        _endIndex((constr == Construction::EMPTY) ? 0 : _grid.size()){};

  // Default constructors and operators generated by the compiler.
  support() = default;
  support(const support &s) = default;
  support(support &&s) = default;
  ~support() = default;
  support &operator=(const support &s) = default;
  support &operator=(support &&s) = default;

  /*!
   * Returns the number of grid points contained in the support.
   */
  size_t size() const { return _endIndex - _startIndex; };

  /*!
   * Checks whether the number of grid points contained in the support is zero.
   */
  bool empty() const { return (_startIndex == _endIndex); };

  /*!
   * Checks whether the support contains any intervals. Returns true if the
   * support is empty or point-like. The number of intervals is the number of
   * grid points minus one (size() - 1).
   */
  bool containsIntervals() const { return (size() > 1); };

  /*!
   * Returns the index relative to the intervals of this support from an index
   * relative to the global grid. If the index refers to an interval outside
   * this support, std::nullopt is returned.
   *
   * @param index The AbsoluteIndex referring to an interval on the global grid.
   */
  std::optional<RelativeIndex> relativeFromAbsolute(AbsoluteIndex index) {
    if (index >= _startIndex && index < _endIndex)
      return index - _startIndex;
    else
      return std::nullopt;
  };

  /*!
   * Returns the index relative to the intervals of this support from an index
   * relative to the global grid. If the index refers to an interval outside
   * this support, std::nullopt is returned.
   *
   * @param index The AbsoluteIndex referring to an interval on the global grid.
   */
  AbsoluteIndex absoluteFromRelative(RelativeIndex index) {
    assert(index < size());
    return index + _startIndex;
  };

  /*!
   * Returns the number of intervals represented by this support.
   */
  size_t numberOfIntervals() const {
    size_t si = size();
    if (si == 0)
      return 0;
    else
      return si - 1;
  };

  /*!
   * Returns the global grid.
   */
  grid<T> getGrid() const { return _grid; };

  /*!
   * Returns the _startIndex.
   */
  size_t getStartIndex() const { return _startIndex; };

  /*!
   * Returns the _endIndex.
   */
  size_t getEndIndex() const { return _endIndex; }

  /*!
   * Allows access to the grid points contained in the support. Performs no
   * bounds checks.
   *
   * @param index Index of the element.
   */
  const T &operator[](size_t index) const {
    return _grid[_startIndex + index];
  };

  /*!
   * Allows access to the grid points contained in the support. Checks bounds
   * via an assert.
   *
   * @param index Index of the element.
   */
  const T &at(size_t index) const {
    assert(_startIndex + index < _endIndex);
    return _grid.at(_startIndex + index);
  };

  /*!
   * Returns a reference to the first grid point that is part of the support.
   */
  const T &front() const {
    assert(!empty());
    return _grid[_startIndex];
  };

  /*!
   * Returns a reference to the last grid point that is part of the support.
   */
  const T &back() const {
    assert(!empty());
    return _grid[_endIndex - 1];
  };

  /*!
   * Checks whether the global grids, the two supports are defined on, are
   * logically equivalent.
   *
   * @param s Support to check against.
   */
  bool hasSameGrid(const support &s) const { return _grid == s._grid; };

  /*!
   * Compares two supports for equality. For two supports two be equal, they
   * have to be defined on the same grid, must represent the same subset of the
   * number line.
   *
   * @param s Support to compare against.
   */
  bool operator==(const support &s) const {
    return hasSameGrid(s) &&
           ((_startIndex == s._startIndex && _endIndex == s._endIndex) ||
            (empty() && s.empty()));
  };

  /*!
   * Calculates the union of this support with the support s. This is not
   * strictly the set-theoretical union (if the two supports do not overlap),
   * but a support representing one contiguous bit of the number line containing
   * both supports.
   *
   * @param s The support to calculate the union with.
   */
  support calcUnion(const support &s) const {
    assert(hasSameGrid(s));
    const bool thisEmpty = empty();
    const bool sEmpty = s.empty();
    if (thisEmpty && sEmpty)
      return support(_grid); // Both supports are empty, return empty support
    else if (thisEmpty && !sEmpty)
      return s;
    else if (!thisEmpty && sEmpty)
      return *this;
    size_t newStartIndex = std::min(_startIndex, s._startIndex);
    size_t newEndIndex = std::max(_endIndex, s._endIndex);
    return support(_grid, newStartIndex, newEndIndex);
  };

  /*!
   * Calculates the intersection of the two supports.
   *
   * @param s The support to calculate the intersection with.
   */
  support calcIntersection(const support &s) const {
    assert(hasSameGrid(s));
    size_t newStartIndex = std::max(_startIndex, s._startIndex);
    size_t newEndIndex = std::min(_endIndex, s._endIndex);
    if (newStartIndex >= newEndIndex)
      return support(_grid); // no overlap, return empty support
    else
      return support(_grid, newStartIndex, newEndIndex);
  };

};     // end class support
};     // end namespace myspline::internal
#endif // MYSPLINE_INTERNAL_H
