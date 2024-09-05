#ifndef FILTERS_HPP
#define FILTERS_HPP
#include <functional>

#include "figures.hpp"

namespace demin
{
  bool odd(const Polygon &p);
  bool even(const Polygon &p);
  bool checkVertexes(size_t count, const Polygon &p);
  bool compareAreas(const Polygon &p1, const Polygon &p2);
  bool compareVertexes(const Polygon &p1, const Polygon &p2);
  bool countAngle(Point &p1, Point &p2, const Point &p3);
  bool isRight(const Polygon &polygon);
  double getArea(const Polygon &points);
  std::pair< demin::Point, demin::Point > findFrame(const std::pair< Point, Point > &res, const Polygon &polygon);
  bool compareX(const Point &p1, const Point &p2);
  bool compareY(const Point &p1, const Point &p2);
  bool isInFrame(std::pair< Point, Point > frame, const Point &point);

  struct AccumulateArea
  {
    demin::Point p1;

    double operator()(double &res, const demin::Point &p2, const demin::Point &p3)
    {
      res += 0.5 * (std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y)));
      p1 = p2;
      return res;
    }
  };
}
#endif
