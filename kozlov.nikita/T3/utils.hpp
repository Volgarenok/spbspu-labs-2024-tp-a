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

  double calculateArea(const Polygon& poly);
}
#endif
