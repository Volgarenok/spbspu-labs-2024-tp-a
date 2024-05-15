#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "Point.hpp"

namespace sazanov
{
  struct Polygon
  {
    std::vector< Point > points;

    bool operator==(const Polygon& rhs) const;
    double getArea() const;
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);

  struct PolygonAreaO
  {
    const Polygon& polygon;
  };
  std::ostream& operator<<(std::ostream& out, PolygonAreaO&& areaO);

  struct AccumulatePolygonAreaPart
  {
    Point p1;
    double operator()(double area, const Point& p2, const Point& p3);
  };
}

#endif
