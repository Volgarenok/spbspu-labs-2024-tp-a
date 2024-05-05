#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace ishmuratov
{
  struct Point
  {
    int x;
    int y;
  };

  struct Polygon
  {
    std::vector< Point > points;
    double get_area();
  private:
    double calculate_area(std::vector< Point >::const_iterator p1, std::vector< Point >::const_iterator p2, double curr);
  };

  double calculate_pair(const Point & p1, const Point & p2, double curr);
  std::istream & operator>>(std::istream & input, Point & point);
  std::istream & operator>>(std::istream & input, Polygon & polygon);
}

#endif
