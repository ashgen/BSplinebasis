#ifndef OKRUZ_BSPLINE_INTEGRATION_NUMERICAL_H
#define OKRUZ_BSPLINE_INTEGRATION_NUMERICAL_H
/*
 * This file contains an additional numerical integration routine for the
 * Splines based on the Gauss-Legendre routines in boost/math/quadrature.
 *
 * ########################################################################
 * The contents of this file is free and unencumbered software released into the
 * public domain. For more information, please refer to <http://unlicense.org/>
 * ########################################################################
 */

#include <okruz/bspline/Spline.h>
#include <okruz/bspline/exceptions/BSplineException.h>
#include <okruz/bspline/internal/misc.h>

#include <boost/math/quadrature/gauss.hpp>

namespace okruz::bspline::integration {
using namespace boost::math::quadrature;
using okruz::bspline::support::Support;
using namespace okruz::bspline::exceptions;

/*!
 * Calculates the 1D integral \f[I=\int\limits_{-\infty}^{\infty} \mathrm{d}x~
 * m_1(x)\, f(x)\, m_2(x).\f] The integral is evaluated numerically on each
 * interval using boost's Gauss-Legendre scheme of order ordergl.
 *
 * @param f Function f(x) to be multiplied to the integrand.
 * @param m1 First spline m1(x).
 * @param m2 Second spline m2(x).
 * @tparam ordergl Order of the Gauss-Legendre integration scheme provided by
 * the boost library.
 * @tparam T Datatype of the calculation.
 * @tparam order1 Order of the spline m1(x).
 * @tparam order2 Order of the spline m2(x).
 */
template <size_t ordergl, typename T, typename F, size_t order1, size_t order2>
T integrate(const F &f, const okruz::bspline::Spline<T, order1> &m1,
            const okruz::bspline::Spline<T, order2> &m2) {
  // Will also check whether the two grids are equivalent.
  const Support newSupport = m1.getSupport().calcIntersection(m2.getSupport());
  const size_t nintervals = newSupport.numberOfIntervals();

  T result = static_cast<T>(0);
  for (size_t interv = 0; interv < nintervals; interv++) {
    const auto ai = newSupport.absoluteFromRelative(interv);
    const auto m1Index = m1.getSupport().intervalIndexFromAbsolute(ai).value();
    const auto m2Index = m2.getSupport().intervalIndexFromAbsolute(ai).value();

    const T &xstart = m1.getSupport().at(m1Index);
    const T &xend = m1.getSupport().at(m1Index + 1);
    const T xm = (xstart + xend) / static_cast<T>(2);
    const auto &c1 = m1.getCoefficients().at(m1Index);
    const auto &c2 = m2.getCoefficients().at(m2Index);
    result += gauss<T, ordergl>::integrate(
        [&c1, &c2, &xm, &f](const T &x) {
          using namespace okruz::bspline::internal;
          return f(x) * evaluateInterval(x, c1, xm) *
                 evaluateInterval(x, c2, xm);
        },
        xstart, xend);
  }
  return result;
}
}  // namespace okruz::bspline::integration
#endif  // OKRUZ_BSPLINE_INTEGRATION_NUMERICAL_H
