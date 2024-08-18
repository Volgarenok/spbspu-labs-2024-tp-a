#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>

#include <Delimeter.hpp>

namespace kornienko
{
  struct Point
  {
    int x, y;
    bool operator==(const Point & other) const;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
  struct Triangle
  {
    Triangle() {}
    Triangle(const Polygon & polygon, size_t count)
    {
      first = polygon.points[0];
      second = polygon.points[count];
      third = polygon.points[count + 1];
    }
    Point first;
    Point second;
    Point third;
  };
  struct TriangleParser
  {
    TriangleParser() : count(0) {}
    Triangle operator()(const Polygon & polygon);
    size_t count;
  };

  double getArea(const Polygon & polygon);
  std::istream & operator>>(std::istream & in, Point & point);
  std::ostream & operator<<(std::ostream & out, const Point & point);
  std::istream & operator>>(std::istream & in, Polygon & polygon);
  std::ostream & operator<<(std::ostream & out, const Polygon & polygon);
}

#endif
