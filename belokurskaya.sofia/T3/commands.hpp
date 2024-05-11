#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "polygon.hpp"

namespace belokurskaya
{
  namespace cmd
  {
    void area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);

    namespace subcmd
    {
      double getTriangleArea(const Point& point1, const Point& point2, const Point& point3);
      double getPolygonArea(const Polygon& polygon);
      double getPolygonAreaEvenOrOdd(const Polygon& polygon, const bool isEven);
      size_t getCountVertexes(const Polygon& polygon);
    }
  }
}

#endif
