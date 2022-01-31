#ifndef OKRUZ_BSPLINE_BSPLINEGENERATOR_H
#define OKRUZ_BSPLINE_BSPLINEGENERATOR_H
#include <okruz/bspline/Spline.h>
#include <okruz/bspline/exceptions/BSplineException.h>
#include <okruz/bspline/operators/CompoundOperators.h>
#include <okruz/bspline/operators/Position.h>
#include <okruz/bspline/operators/ScalarOperators.h>

#include <algorithm>

/*
 * ########################################################################
 * The contents of this file is free and unencumbered software released into the
 * public domain. For more information, please refer to <http://unlicense.org/>
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
template <typename T>
class BSplineGenerator {
 private:
  /*! The global grid.*/
  Grid<T> _grid;

  /*! The knots. Contrary to the grid, the knots vector may contain the same
   * elements multiple times (see e.g. [1]). */
  std::vector<T> _knots;

  /*!
   * Generates a Grid<T> from a knots vector. Contrary to the knots vector, the
   * grid may not contain any element more than once. The number of times an
   * element is contained in the knots vector controls the continuity of the
   * Bsplines at this grid point (see e.g. [1]).
   *
   * @param knots The vector of knots.
   */
  Grid<T> generateGrid(std::vector<T> knots) {
    const auto endIterator = std::unique(knots.begin(), knots.end());
    knots.erase(endIterator, knots.end());
    return Grid<T>(std::move(knots));
  }

 public:
  /*!
   * Constructor generating the grid from the knots vector.
   *
   * @param knots The knots, the BSplines shall be generated on.
   */
  explicit BSplineGenerator(std::vector<T> knots)
      : _grid(generateGrid(knots)), _knots(std::move(knots)){};

  /*!
   * Constructor generating the grid from the knots vector.
   *
   * @param knots The knots, the BSplines shall be generated on.
   * @param grid The Grid instance to use. Must be logically equivalent to the
   * Grid generated from knots. If that is not the case, an exception is thrown.
   */
  BSplineGenerator(std::vector<T> knots, Grid<T> grid)
      : _grid(std::move(grid)), _knots(std::move(knots)) {
    // Check, whether the given knots vector and grid are consistent.
    Grid<T> secondGrid = generateGrid(_knots);
    if (_grid != secondGrid) {
      throw BSplineException(ErrorCode::INCONSISTENT_DATA);
    }
  };

  /*!
   * Returns the grid.
   */
  Grid<T> getGrid() const { return _grid; };

  /*!
   * Generates all BSplines with respect to the knots vector.
   * @tparam k Number of the coefficients per interval for the spline (i.e.
   * order of the spline plus one).
   */
  template <size_t k>
  std::vector<Spline<T, k - 1>> generateBSplines() const {
    static_assert(k >= 1, "k has to be at least 1.");
    if (_knots.size() < k) {
      throw BSplineException(ErrorCode::UNDETERMINED,
                             "The knots vector contains too few elements to "
                             "generate BSplines of the requested order.");
    }

    if constexpr (k == 1) {
      return generateZerothOrderSplines();
    } else {
      const auto nextLowerOrderSplines = generateBSplines<k - 1>();
      std::vector<Spline<T, k - 1>> ret;
      ret.reserve(_knots.size() - k);
      for (size_t i = 0; i < _knots.size() - k; i++) {
        ret.push_back(applyRecursionRelation<k>(
            i, nextLowerOrderSplines.at(i), nextLowerOrderSplines.at(i + 1)));
      }
      return ret;
    }
  }

 private:
  /*!
   * Generates a Bspline of order k-1 at knot i by application of the recursion
   * relation \f[B_{i,k}(x) = \frac{x - x_i}{x_{i + k -1} - x_i}\ B_{i, k-1}(x)
   * + \frac{x_{i+k}-x}{x_{i+k}-x_{i+1}}\,B_{i+1,k-1}(x)\f].
   *
   * @param i Index of the knot at which to generate the BSpline.
   * @param splinei The spline of the next lower order at index i.
   * @param splineip1 The spline of the next lower order at index i + 1.
   * @tparam k Number of the coefficients per interval for the spline (i.e.
   * order of the spline plus one).
   */
  template <size_t k>
  Spline<T, k - 1> applyRecursionRelation(
      size_t i, const Spline<T, k - 2> &splinei,
      const Spline<T, k - 2> &splineip1) const {
    static_assert(k >= 2, "k has to be at least 2.");

    Spline<T, k - 1> ret(_grid);

    const T &xi = _knots.at(i);
    const T &xipkm1 = _knots.at(i + k - 1);
    if (xipkm1 > xi) {
      const T prefac = static_cast<T>(1) / (xipkm1 - xi);
      const auto op = prefac * (operators::X<1>{} - xi);
      ret += op * splinei;
    }

    const T &xip1 = _knots.at(i + 1);
    const T &xipk = _knots.at(i + k);
    if (xipk > xip1) {
      const T prefac = static_cast<T>(1) / (xipk - xip1);
      const auto op = prefac * (xipk - operators::X<1>{});
      ret += op * splineip1;
    }

    return ret;
  }

  /*!
   * Generates all zeroth order splines.
   */
  std::vector<Spline<T, 0>> generateZerothOrderSplines() const {
    std::vector<Spline<T, 0>> ret;
    const size_t numberOfSplines = (_knots.empty()) ? 0 : _knots.size() - 1;
    ret.reserve(numberOfSplines);

    for (size_t i = 0; i < numberOfSplines; i++) {
      const T &xi = _knots.at(i);
      const T &xip1 = _knots.at(i + 1);

      if (xi > xip1) {
        throw BSplineException(ErrorCode::UNDETERMINED);
      } else if (xi == xip1) {
        ret.push_back(Spline<T, 0>{_grid});
      } else {
        std::vector<std::array<T, 1>> coefficients{{static_cast<T>(1)}};

        const size_t gridIndex = _grid.findElement(xi);

        ret.push_back(Spline<T, 0>{Support(_grid, gridIndex, gridIndex + 2),
                                   std::move(coefficients)});
      }
    }
    return ret;
  }
};

}  // namespace okruz::bspline
#endif  // OKRUZ_BSPLINE_BSPLINEGENERATOR_H
