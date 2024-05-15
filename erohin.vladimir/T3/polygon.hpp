#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iosfwd>

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
    bool isRightAngle(size_t vertex_index) const;
    bool countRightAngles() const;
  };

  std::istream & operator>>(std::istream & input, Point & point);
  std::ostream & operator<<(std::ostream & output, const Point & point);
  std::istream & operator>>(std::istream & input, Polygon & polygon);
  std::ostream & operator<<(std::ostream & output, const Polygon & polygon);
  double getArea(const Polygon & polygon);
}

#endif
