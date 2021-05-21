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

/*! A shared pointer to a vector representing the global grid. A support
 * represents a subset of the interval represented by this grid.
 */
template <typename T> using grid = std::shared_ptr<const std::vector<T>>;

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
    assert(_endIndex >= _startIndex && _endIndex <= _grid->size());
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
        _endIndex((constr == Construction::EMPTY) ? 0 : _grid->size()){};

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
    return (*_grid)[_startIndex + index];
  };

  /*!
   * Allows access to the grid points contained in the support. Checks bounds
   * via an assert.
   *
   * @param index Index of the element.
   */
  const T &at(size_t index) const {
    assert(_startIndex + index < _endIndex);
    return _grid->at(_startIndex + index);
  };

  /*!
   * Returns a reference to the first grid point that is part of the support.
   */
  const T &front() const {
    assert(!empty());
    return (*_grid)[_startIndex];
  };

  /*!
   * Returns a reference to the last grid point that is part of the support.
   */
  const T &back() const {
    assert(!empty());
    return (*_grid)[_endIndex - 1];
  };

  /*!
   * Checks whether the global grids, the two supports are defined on, are
   * logically equivalent.
   *
   * @param s Support to check against.
   */
  bool hasSameGrid(const support &s) const {
    if (_grid == s._grid)
      [[likely]] return true;
    else if (_grid->size() != s._grid->size())
      return false;
    for (size_t i = 0; i < _grid->size(); i++)
      if ((*_grid)[i] != (*(s._grid))[i])
        return false;
    return true;
  };

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
