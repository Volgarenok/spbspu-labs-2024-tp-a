#ifndef GEOMETRIC_HPP
#define GEOMETRIC_HPP

#include <vector>
#include <iostream>

namespace prisyach
{
  struct Point
  {
    int x_;
    int y_;
  };

  bool operator==(const Point &, const Point &);
  bool operator!=(const Point &, const Point &);
  bool operator<(const Point &, const Point &);
  bool operator>(const Point &, const Point &);
  bool operator<=(const Point &, const Point &);
  bool operator>=(const Point &, const Point &);

  std::istream & operator>>(std::istream &, Point &);

  struct Polygon
  {
    std::vector< Point > points;
  };

  struct PolygonArea
  {
    Point first;
    double operator()(double area, const Point & second, const Point & third)
    {
      area += 0.5 * std::abs((third.y_ - first.y_) * (second.x_ - first.x_) - (third.x_ - first.x_) * (second.y_ - first.y_));
      first = second;
      return area;
    }
  };

  double getArea(const Polygon &);
  bool operator==(const Polygon &, const Polygon &);
  bool operator!=(const Polygon &, const Polygon &);

  std::istream & operator>>(std::istream &, Polygon &);
}

#endif
