#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <istream>
#include <ostream>
#include <vector>

namespace zhakha
{
  struct Point
  {
    int x, y;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& out, const Point& point);
  bool operator==(const Point& lhs, const Point& rhs);

  struct Polygon
  {
    std::vector<Point> points;
  };

  std::istream& operator>>(std::istream& in, Polygon& polygon);
  bool operator==(const Polygon& lhs, const Polygon& rhs);
  int getDeterminantByPoint(const Polygon& polygon, const Point& point);
  double getArea(const Polygon& polygon);

}

#endif
