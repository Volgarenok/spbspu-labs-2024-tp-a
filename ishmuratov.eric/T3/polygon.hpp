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
  };
  using point_it = std::vector< Point >::const_iterator;
  double get_area(const Polygon & poly);
  double calculate_area(point_it end, point_it p1, point_it p2, double curr);
  double calculate_pair(const Point & p1, const Point & p2);
  std::istream & operator>>(std::istream & input, Point & point);
  std::istream & operator>>(std::istream & input, Polygon & polygon);
  bool operator==(const Point & p1, const Point & p2);
  bool operator==(const Polygon & poly1, const Polygon & poly2);
}

#endif
