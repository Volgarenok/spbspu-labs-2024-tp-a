#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <vector>
#include <functional>

namespace kuznetsov
{
  struct Point
  {
    int x;
    int y;
  };

  std::istream& operator>>(std::istream& in, Point& point);

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Polygon& polygon);

  struct Triangle
  {
    Triangle()
    {}

    Triangle(const Point& a, const Point& b, const Point& c) :
      a(a),
      b(b),
      c(c)
    {}
    Point a;
    Point b;
    Point c;
  };

  double countArea(const Triangle& trinagle);

  struct TriangleProducer
  {
    TriangleProducer(const Polygon& newPolygon) :
      current(1),
      polygon(newPolygon)
    {}

    Triangle operator()();

    size_t current;
    const Polygon& polygon;
  };

  using Pred = std::function< bool(const Polygon& shape) >;
  double countAreaShape(const Polygon& polygon);
  double getAreaOddEven(std::vector< Polygon >& polygon, Pred func);
  double getAreaMean(std::vector< Polygon >& polygon, Pred func);
  size_t getVertexes(const Polygon& polygon);
  void getMinOrMaxArea(std::ostream& out, std::vector< Polygon >& polygon, std::function< bool() > func);
  void getMinOrMaxVertexes(std::ostream& out, std::vector< Polygon >& polygon, std::function< bool() > func);
  size_t countShapesWithEvenOrOddVertexes(std::vector< Polygon >& polygon, Pred func);
}

#endif
