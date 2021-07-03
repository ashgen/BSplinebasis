#ifndef OKRUZ_BSPLINE_BSPLINEGENERATOR_H
#define OKRUZ_BSPLINE_BSPLINEGENERATOR_H
#include <algorithm>
#include <okruz/bspline/Spline.h>
#include <okruz/bspline/exceptions/BSplineException.h>

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
 *
 * [1] https://en.wikipedia.org/wiki/B-spline
 */

namespace okruz::bspline {
using namespace okruz::bspline::exceptions;

/*!
 * Generates the BSplines on a grid.
 *
 * @tparam T The datatype of the spline and grid.
 */
template <typename T> class BSplineGenerator {
private:
  Grid<T> _grid; /*! The global grid.*/
  std::vector<T>
      _knots; /*! The knots. Contrary to the grid, the knots vector may contain
                 the same elements multiple times (see e.g. [1]). */

  /*!
   * Generates a Grid<T> from a knots vector. Contrary to the knots vector, the
   * grid may not contain any element more than once. The number of times an
   * element is contained in the knots vector controls the continuity of the
   * Bsplines at this grid point (see e.g. [1]).
   *
   * @param knots The vector of knots.
   */
  Grid<T> generateGrid(std::vector<T> knots) {
    auto endIterator = std::unique(knots.begin(), knots.end());
    return Grid<T>(knots.begin(), endIterator);
  }

public:
  /*!
   * Constructor generating the grid from the knots vector.
   *
   * @param knots The knots, the BSplines shall be generatre on.
   */
  BSplineGenerator(std::vector<T> knots)
      : _grid(generateGrid(knots)), _knots(std::move(knots)){};

  BSplineGenerator(std::vector<T> knots, Grid<T> grid)
      : _grid(std::move(grid)), _knots(std::move(knots)) {
    // Check, whether the given knots vector and grid are consistent.
    Grid<T> secondGrid = generateGrid(_knots);
    if (_grid != secondGrid) {
      throw BSplineException(ErrorCode::INCONSISTENT_DATA);
    }
  };

  // Default constructors and operators generated by the compiler.
  BSplineGenerator() = default;
  BSplineGenerator(const BSplineGenerator &m) = default;
  BSplineGenerator(BSplineGenerator &&m) = default;
  virtual ~BSplineGenerator() = default;
  BSplineGenerator &operator=(const BSplineGenerator &m) = default;
  BSplineGenerator &operator=(BSplineGenerator &&m) = default;

  /*!
   * Returns the grid.
   */
  Grid<T> getGrid() const { return _grid; };

  /*!
   * Generates a Bspline of order k-1 at knot i relative to the grid given by
   * knots.
   *
   * @param i Index of the knot at which to generate the BSpline.
   * @tparam k Number of the coefficients per interval for the spline (i.e.
   * order of the spline plus one).
   */
  template <size_t k> Spline<T, k - 1> generateBSpline(size_t i) const {
    using Support = okruz::bspline::support::Support<T>;
    static_assert(k >= 1, "k has to be at least 1.");

    if constexpr (k == 1) {
      const T &xi = _knots.at(i);
      const T &xip1 = _knots.at(i + 1);

      if (xi >= xip1) {
        throw BSplineException(ErrorCode::UNDETERMINED);
      }

      std::vector<std::array<T, 1>> coefficients{{static_cast<T>(1)}};

      const size_t gridIndex = _grid.findElement(xi);

      return Spline<T, 0>(Support(_grid, gridIndex, gridIndex + 2),
                          std::move(coefficients));
    } else {
      Spline<T, k - 1> ret(_grid);

      const T &xi = _knots.at(i);
      const T &xipkm1 = _knots.at(i + k - 1);
      if (xipkm1 > xi) {
        const T prefac = static_cast<T>(1) / (xipkm1 - xi);
        const Spline<T, k - 2> spline1 = prefac * generateBSpline<k - 1>(i);
        ret += spline1.timesx() - xi * spline1;
      }

      const T &xip1 = _knots.at(i + 1);
      const T &xipk = _knots.at(i + k);
      if (xipk > xip1) {
        const T prefac = static_cast<T>(1) / (xipk - xip1);
        const Spline<T, k - 2> spline2 = prefac * generateBSpline<k - 1>(i + 1);
        ret += xipk * spline2 - spline2.timesx();
      }

      return ret;
    }
  }

  /*!
   * Generates all BSplines with respect to the knots vector.
   * @tparam k Number of the coefficients per interval for the spline (i.e.
   * order of the spline plus one).
   */
  template <size_t k> std::vector<Spline<T, k - 1>> generateBSplines() const {
    if (_knots.size() < k) {
      throw BSplineException(ErrorCode::UNDETERMINED,
                             "The knots vector contains too few elements to "
                             "generate BSplines of the requested order.");
    }

    std::vector<Spline<T, k - 1>> ret;
    ret.reserve(_knots.size() - k);
    for (size_t i = 0; i < _knots.size() - k; i++) {
      ret.push_back(generateBSpline<k>(i));
    }
    return ret;
  }
};

} // namespace okruz::bspline
#endif // OKRUZ_BSPLINE_BSPLINEGENERATOR_H
