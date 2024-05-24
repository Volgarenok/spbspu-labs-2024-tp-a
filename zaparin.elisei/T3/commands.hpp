#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <exception>
#include <string>
#include "polygon.hpp"

namespace zaparin
{
  bool isEven(const Polygon& plg);
  bool isOdd(const Polygon& plg);
  bool isEqualVertexes(size_t numOfVertexes, const Polygon& plg);

  struct TriangleArea
  {
    Point p1;
    Point p2;
    double operator()(const Point& p3);
  };
  double getArea(const Polygon& plg);
  size_t getVertexes(const Polygon& plg);
  size_t isEqualCounter(const Polygon& plg, const std::vector< Point >& src, size_t& counter);
  bool isIntersected(const Polygon& plg, const std::vector< Point >& points);

  void cmdArea(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out);
  void cmdMax(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out);
  void cmdMin(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out);
  void cmdCount(std::vector< Polygon >& plgs, std::istream&, std::ostream& out);
  void cmdMaxSeq(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out);
  void cmdIntersections(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out);
}

#endif

