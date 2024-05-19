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
  template< class UnaryPredicate >
  double getSumAreaIf(const std::vector< Polygon > & context, UnaryPredicate P)
  {
    std::vector< Polygon > selected;
    std::copy_if(context.cbegin(), context.cend(), std::back_inserter(selected), P);
    return getArea(selected);
  }
  namespace detail
  {
    struct evaluateArea
    {
      Point start;
      Point prev;
      double operator()(const Point & point);
    };

    struct isRightAngle
    {
      Point prev;
      Point center;
      bool operator()(const Point & point);
    };

    struct getFrameRectLeftLower
    {
      Point operator()(const Polygon & polygon);
    };

    struct getFrameRectRightUpper
    {
      Point operator()(const Polygon & polygon);
    };
  }
}

#endif
