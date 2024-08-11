#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iosfwd>
#include "point.hpp"

namespace isaychev
{
  struct Polygon
  {
    std::vector< Point > pnts;
  };

  std::istream & operator>>(std::istream & in, Polygon & p);
  std::ostream & operator<<(std::ostream & out, const Polygon & p);

  class polPartAreaAccumulator
  {
   public:
    double operator()(const Point & p);

   private:
    Point prev_;
  };

  double getArea(const Polygon & rhs);
}

#endif
