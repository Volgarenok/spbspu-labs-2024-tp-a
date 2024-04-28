#ifndef FIGURES_STRUCT_HPP
#define FIGURES_STRUCT_HPP

#include <istream>
#include <vector>

namespace nikitov
{
  struct Point
  {
    int x;
    int y;
    bool operator==(const Point& other) const;
  };

  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
  };

  struct AccumulateArea
  {
    Point first;
    Point second;
    double operator()(double result, const Point& third);
  };

  std::istream& operator>>(std::istream& input, Point& value);
  std::istream& operator>>(std::istream& input, Polygon& value);
}
#endif
