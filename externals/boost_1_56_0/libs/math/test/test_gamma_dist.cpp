// Copyright John Maddock 2006.
// Copyright Paul A. Bristow 2007, 2010.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// test_gamma_dist.cpp

// http://en.wikipedia.org/wiki/Gamma_distribution
// http://www.itl.nist.gov/div898/handbook/eda/section3/eda366b.htm
// Also:
// Weisstein, Eric W. "Gamma Distribution."
// From MathWorld--A Wolfram Web Resource.
// http://mathworld.wolfram.com/GammaDistribution.html

#include <pch.hpp> // include directory libs/math/src/tr1/ is needed.

#include <boost/math/concepts/real_concept.hpp> // for real_concept
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp> // Boost.Test
#include <boost/test/floating_point_comparison.hpp>

#include <boost/math/distributions/gamma.hpp>
    using boost::math::gamma_distribution;
#include <boost/math/tools/test.hpp>
#include "test_out_of_range.hpp"

#include <iostream>
#include <iomanip>
   using std::cout;
   using std::endl;
   using std::setprecision;
#include <limits>
  using std::numeric_limits;

template <class RealType>
RealType NaivePDF(RealType shape, RealType scale, RealType x)
{
   // Deliberately naive PDF calculator again which
   // we'll compare our pdf function.  However some
   // published values to compare against would be better....
   using namespace std;
   RealType result = log(x) * (shape - 1) - x / scale - boost::math::lgamma(shape) - log(scale) * shape;
   return exp(result);
}

template <class RealType>
void check_gamma(RealType shape, RealType scale, RealType x, RealType p, RealType q, RealType tol)
{
   BOOST_CHECK_CLOSE(
      ::boost::math::cdf(
         gamma_distribution<RealType>(shape, scale),    // distribution.
         x),                                            // random variable.
         p,                                             // probability.
         tol);                                          // %tolerance.
   BOOST_CHECK_CLOSE(
      ::boost::math::cdf(
         complement(
            gamma_distribution<RealType>(shape, scale), // distribution.
            x)),                                        // random variable.
         q,                                             // probability complement.
         tol);                                          // %tolerance.
   if(p < 0.999)
   {
      BOOST_CHECK_CLOSE(
         ::boost::math::quantile(
            gamma_distribution<RealType>(shape, scale),    // distribution.
            p),                                            // probability.
            x,                                             // random variable.
            tol);                                          // %tolerance.
   }
   if(q < 0.999)
   {
      BOOST_CHECK_CLOSE(
         ::boost::math::quantile(
            complement(
               gamma_distribution<RealType>(shape, scale), // distribution.
               q)),                                        // probability complement.
            x,                                             // random variable.
            tol);                                          // %tolerance.
   }
   // PDF:
   BOOST_CHECK_CLOSE(
      boost::math::pdf(
         gamma_distribution<RealType>(shape, scale),    // distribution.
         x),                                            // random variable.
         NaivePDF(shape, scale, x),                     // PDF
         tol);                                          // %tolerance.
}

template <class RealType>
void test_spots(RealType)
{
   // Basic sanity checks
   //
   // 15 decimal places expressed as a persentage.
   // The first tests use values generated by MathCAD,
   // and should be accurate to around double precision.
   //
   RealType tolerance = (std::max)(RealType(5e-14f), std::numeric_limits<RealType>::epsilon() * 20) * 100;
   cout << "Tolerance for type " << typeid(RealType).name()  << " is " << tolerance << " %" << endl;

   check_gamma(
      static_cast<RealType>(0.5),
      static_cast<RealType>(1),
      static_cast<RealType>(0.5),
      static_cast<RealType>(0.682689492137085),
      static_cast<RealType>(1-0.682689492137085),
      tolerance);
   check_gamma(
      static_cast<RealType>(2),
      static_cast<RealType>(1),
      static_cast<RealType>(0.5),
      static_cast<RealType>(0.090204010431050),
      static_cast<RealType>(1-0.090204010431050),
      tolerance);
   check_gamma(
      static_cast<RealType>(40),
      static_cast<RealType>(1),
      static_cast<RealType>(10),
      static_cast<RealType>(7.34163631456064E-13),
      static_cast<RealType>(1-7.34163631456064E-13),
      tolerance);

   //
   // Some more test data generated by the online
   // calculator at http://espse.ed.psu.edu/edpsych/faculty/rhale/hale/507Mat/statlets/free/pdist.htm
   // This has the advantage of supporting the scale parameter as well
   // as shape, but has only a few digits accuracy, and produces
   // some deeply suspect values if the shape parameter is < 1
   // (it doesn't agree with MathCAD or this implementation).
   // To be fair the incomplete gamma is tricky to get right in this area...
   //
   tolerance = 1e-5f * 100; // 5 decimal places as a persentage
   cout << "Tolerance for type " << typeid(RealType).name()  << " is " << tolerance << " %" << endl;

   check_gamma(
      static_cast<RealType>(2),
      static_cast<RealType>(1)/5,
      static_cast<RealType>(0.1),
      static_cast<RealType>(0.090204),
      static_cast<RealType>(1-0.090204),
      tolerance);
   check_gamma(
      static_cast<RealType>(2),
      static_cast<RealType>(1)/5,
      static_cast<RealType>(0.5),
      static_cast<RealType>(1-0.287298),
      static_cast<RealType>(0.287298),
      tolerance);
   check_gamma(
      static_cast<RealType>(3),
      static_cast<RealType>(2),
      static_cast<RealType>(1),
      static_cast<RealType>(0.014388),
      static_cast<RealType>(1-0.014388),
      tolerance * 10); // one less decimal place in the test value
   check_gamma(
      static_cast<RealType>(3),
      static_cast<RealType>(2),
      static_cast<RealType>(5),
      static_cast<RealType>(0.456187),
      static_cast<RealType>(1-0.456187),
      tolerance);


    RealType tol2 = boost::math::tools::epsilon<RealType>() * 5 * 100;  // 5 eps as a persentage
    gamma_distribution<RealType> dist(8, 3);
    RealType x = static_cast<RealType>(0.125);
    using namespace std; // ADL of std names.
    // mean:
    BOOST_CHECK_CLOSE(
       mean(dist)
       , static_cast<RealType>(8*3), tol2);
    // variance:
    BOOST_CHECK_CLOSE(
       variance(dist)
       , static_cast<RealType>(8*3*3), tol2);
    // std deviation:
    BOOST_CHECK_CLOSE(
       standard_deviation(dist)
       , sqrt(static_cast<RealType>(8*3*3)), tol2);
    // hazard:
    BOOST_CHECK_CLOSE(
       hazard(dist, x)
       , pdf(dist, x) / cdf(complement(dist, x)), tol2);
    // cumulative hazard:
    BOOST_CHECK_CLOSE(
       chf(dist, x)
       , -log(cdf(complement(dist, x))), tol2);
    // coefficient_of_variation:
    BOOST_CHECK_CLOSE(
       coefficient_of_variation(dist)
       , standard_deviation(dist) / mean(dist), tol2);
    // mode:
    BOOST_CHECK_CLOSE(
       mode(dist)
       , static_cast<RealType>(7 * 3), tol2);
    // skewness:
    BOOST_CHECK_CLOSE(
       skewness(dist)
       , 2 / sqrt(static_cast<RealType>(8)), tol2);
    // kertosis:
    BOOST_CHECK_CLOSE(
       kurtosis(dist)
       , 3 + 6 / static_cast<RealType>(8), tol2);
    // kertosis excess:
    BOOST_CHECK_CLOSE(
       kurtosis_excess(dist)
       , 6 / static_cast<RealType>(8), tol2);

    BOOST_CHECK_CLOSE(
       median(dist), static_cast<RealType>(23.007748327502412), // double precision test value
       (std::max)(tol2, static_cast<RealType>(std::numeric_limits<double>::epsilon() * 2 * 100))); // 2 eps as persent
    // Rely on default definition in derived accessors.

   // error tests
   check_out_of_range<boost::math::gamma_distribution<RealType> >(1, 1);
   BOOST_CHECK_THROW(boost::math::gamma_distribution<RealType>(0, 1), std::domain_error);
   BOOST_CHECK_THROW(boost::math::gamma_distribution<RealType>(-1, 1), std::domain_error);
   BOOST_CHECK_THROW(boost::math::gamma_distribution<RealType>(1, 0), std::domain_error);
   BOOST_CHECK_THROW(boost::math::gamma_distribution<RealType>(1, -1), std::domain_error);

} // template <class RealType>void test_spots(RealType)

BOOST_AUTO_TEST_CASE( test_main )
{
   // Basic sanity-check spot values.
   // (Parameter value, arbitrarily zero, only communicates the floating point type).
  test_spots(0.0F); // Test float. OK at decdigits = 0 tolerance = 0.0001 %
  test_spots(0.0); // Test double. OK at decdigits 7, tolerance = 1e07 %
#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
  test_spots(0.0L); // Test long double.
#ifndef BOOST_MATH_NO_REAL_CONCEPT_TESTS
  test_spots(boost::math::concepts::real_concept(0.)); // Test real concept.
#endif
#else
   std::cout << "<note>The long double tests have been disabled on this platform "
      "either because the long double overloads of the usual math functions are "
      "not available at all, or because they are too inaccurate for these tests "
      "to pass.</note>" << std::cout;
#endif

   
} // BOOST_AUTO_TEST_CASE( test_main )


/*

Output:

Autorun "i:\boost-06-05-03-1300\libs\math\test\Math_test\debug\test_gamma_dist.exe"
Running 1 test case...
Tolerance for type float is 0.000238419 %
Tolerance for type float is 0.001 %
Tolerance for type double is 5e-012 %
Tolerance for type double is 0.001 %
Tolerance for type long double is 5e-012 %
Tolerance for type long double is 0.001 %
Tolerance for type class boost::math::concepts::real_concept is 5e-012 %
Tolerance for type class boost::math::concepts::real_concept is 0.001 %
*** No errors detected

*/


