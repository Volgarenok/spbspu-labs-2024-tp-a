#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <functional>

#include "polygon.hpp"

namespace belokurskaya
{
  namespace cmd
  {
    void area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void rmecho(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void rects(const std::vector< Polygon >& polygons, std::ostream& out);

    namespace subcmd
    {
      double getTriangleArea(const Point& point1, const Point& point2, const Point& point3);
      double getPolygonArea(const Polygon& polygon);
      double getMaxPolygonArea(const std::vector< Polygon >& polygons);
      double getMinPolygonArea(const std::vector< Polygon >& polygons);
      size_t getMaxPolygonVertexes(const std::vector< Polygon >& polygons);
      size_t getMinPolygonVertexes(const std::vector< Polygon >& polygons);
    }
  }

  double calculateAreaBasedOnSizeEven(const Polygon& polygon);
  double calculateAreaBasedOnSizeOdd(const Polygon& polygon);
  double calculateMeanArea(const std::vector< Polygon >& polygons, const Polygon& polygon);
  double calculateAreaBasedOnVertexCount(const Polygon& polygon, size_t numVertexes);
  double sumPolygonAreas(const double sum, const Polygon& polygon, std::function< double(const Polygon&) > resultFunc);
  size_t compareNumVertexes(const Polygon& polygon, size_t numVertexes);
  double calcPolyCount(double sum, const Polygon& polygon, size_t(*resultFuncForCount)(const Polygon&));
  bool isIndentical(const Polygon& poly1, const Polygon& poly2, const Polygon& polyToCompare);
  size_t countEvenSizePolygons(const Polygon& polygon);
  size_t countOddSizePolygons(const Polygon& polygon);
  bool isRectangle(const Polygon& polygon);
  bool comparePolygonAreas(const Polygon& a, const Polygon& b);
  bool comparePolygons(const Polygon& a, const Polygon& b);

  struct RectVector
  {
    Point vertexes;
    RectVector(const Point& p1, const Point& p2);
    double operator*(const RectVector& p1);
    double getLength() const;
    double cos(const RectVector& p1);
  };
}

#endif
