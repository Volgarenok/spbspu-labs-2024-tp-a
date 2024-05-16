#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iosfwd>
#include <algorithm>
#include <numeric>

namespace erohin
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
    std::pair< Point, Point > getFrameRect() const;
  };

  std::istream & operator>>(std::istream & input, Point & point);
  std::ostream & operator<<(std::ostream & output, const Point & point);
  std::istream & operator>>(std::istream & input, Polygon & polygon);
  std::ostream & operator<<(std::ostream & output, const Polygon & polygon);
  std::pair< Point, Point > getFrameRect(const Polygon & polygon);
  std::pair< Point, Point > getFrameRect(const std::vector< Polygon > & context);
  bool hasRightAngles(const Polygon & polygon);
  double getArea(const Polygon & polygon);
  template< class UnaryPredicate >
  double getSumAreaIf(const std::vector< Polygon > & context, UnaryPredicate P)
  {
    std::vector< Polygon > selected;
    std::copy_if(context.cbegin(), context.cend(), std::back_inserter(selected), P);
    std::vector< double > area;
    std::transform(selected.cbegin(), selected.cend(), std::back_inserter(area), getArea);
    return std::accumulate(area.cbegin(), area.cend(), 0.0);
  }
}

#endif
