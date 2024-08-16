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

  class AreaPartCalculator
  {
   public:
    explicit AreaPartCalculator(const Point & rhs);
    double operator()(const Point & p);

   private:
    Point prev_;
  };

  class EqualCounter
  {
   public:
    explicit EqualCounter(const Polygon & rhs);
    size_t operator()(const Polygon & rhs);

   private:
    const Polygon & expected_;
    size_t count_;
  };

  double get_area(const Polygon & rhs);
  size_t get_vertex(const Polygon & rhs);
  bool is_even(const Polygon & rhs);
  bool is_odd(const Polygon & rhs);
  bool is_right_size(const Polygon & rhs, size_t expected);
  bool is_equal(const Polygon & pol, const Polygon & rhs);
  bool has_intersections(const Polygon & pol, const Polygon & rhs);
}

#endif
