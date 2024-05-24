#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iosfwd>
#include <algorithm>
#include <numeric>
#include "point.hpp"

namespace erohin
{
  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream & operator>>(std::istream & input, Polygon & polygon);
  std::ostream & operator<<(std::ostream & output, const Polygon & polygon);
  std::pair< Point, Point > getFrameRect(const Polygon & polygon);
  std::pair< Point, Point > getFrameRect(const std::vector< Polygon > & context);
  bool isVertexNumberEven(const Polygon & polygon);
  bool isVertexNumberOdd(const Polygon & polygon);
  bool isVertexNumber(const Polygon & polygon, size_t number);
  bool isLessByArea(const Polygon & lhs, const Polygon & rhs);
  bool isLessBySize(const Polygon & lhs, const Polygon & rhs);
  bool hasRightAngles(const Polygon & polygon);
  double getArea(const Polygon & polygon);
  double getArea(const std::vector< Polygon > & context);
}

#endif
