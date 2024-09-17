#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <vector>
#include "Polygon.hpp"

namespace stepanchenko
{
  double areaEven(const std::vector< Polygon >& polygons);
  double areaOdd(const std::vector< Polygon >& polygons);
  double areaMean(const std::vector< Polygon >& polygons);
  double areaNum(const std::vector< Polygon >& polygons, size_t nVertexes);
  double getArea(const Polygon& polygon);
  bool isEven(const Polygon& polygon);
  bool isOdd(const Polygon& polygon);
  bool isEven(const Polygon& polygon);
  int multiply_points(const Point& a, const Point& b);
  bool hasNumOfVertexes(const Polygon& polygon, const size_t& num);

  void maxArea(std::vector< Polygon >& polygons, std::ostream& out);
  void maxVertexes(std::vector< Polygon >& polygons, std::ostream& out);
  bool hasLessVertexes(const Polygon& left, const Polygon& right);

  void minArea(std::vector< Polygon >& polygons, std::ostream& out);
  void minVertexes(std::vector< Polygon >& polygons, std::ostream& out);

  size_t countEven(std::vector< Polygon > polygons);
  size_t countOdd(std::vector< Polygon > polygons);
  size_t countNum(std::vector< Polygon > polygons, const size_t& num);
  size_t maxSeq(std::vector< Polygon > polygons, const Polygon& given);

  struct SeqCounter
  {
    size_t count{ 0 };
    size_t operator()(const Polygon & polygon, const Polygon & given);
    bool operator>(const size_t& n);
  };

  struct EqualPolygons
  {
    const Polygon compared;
    bool operator()(const Polygon& compared, const Polygon& poly);
  };
  using rect = std::pair< Point, Point >;
  rect frame(rect& fr, const Polygon& poly);
  bool xComparator(const Point& lhs, const Point& rhs);
  bool yComparator(const Point& lhs, const Point& rhs);
  bool isInFrame(const rect & rect, const Polygon & poly);
  bool isPointInFrame(rect & rect, const Point& point);
}

#endif
