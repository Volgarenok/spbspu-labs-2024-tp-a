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

  struct AreaPartCalculator
  {
   public:
    explicit AreaPartCalculator(const Point & rhs);
    double operator()(const Point & p);

   private:
    Point prev_;
  };

  double get_area(const Polygon & rhs);
  size_t get_vertex(const Polygon & rhs);
}

#endif
