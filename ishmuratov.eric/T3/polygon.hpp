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
  using points_it = std::vector< Point >::const_iterator;
  double get_area(const Polygon & poly);
  double calculate_area(points_it end, points_it p1, points_it p2, double curr);
  double calculate_pair(const Point & p1, const Point & p2, double curr);
  std::istream & operator>>(std::istream & input, Point & point);
  std::istream & operator>>(std::istream & input, Polygon & polygon);
  bool operator==(const Point & p1, const Point & p2);
  bool operator==(const Polygon & poly1, const Polygon & poly2);
}

#endif
