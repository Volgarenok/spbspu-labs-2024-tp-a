#ifndef UTILS_HPP
#define UTILS_HPP
#include <utility>
#include "figures.hpp"

namespace kozlov
{
  struct ShoelaceFormula
  {
    double operator()(double acc, const std::pair< Point, Point >& points) const;
  };

  double calcArea(const Polygon& poly);
  bool isEven(const Polygon& poly);
  bool isOdd(const Polygon& poly);
  double calcMeanArea(const Polygon& poly, size_t polyNums);
}
#endif
