#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>
#include <functional>
#include "point.hpp"

namespace zaparin
{
  struct Polygon
  {
    std::vector< Point > points;
  };

  std::ostream& operator<<(std::ostream& out, const Polygon& plg);
  std::istream& operator>>(std::istream& in, Polygon& plg);

  bool operator==(const Polygon& plg1, const Polygon& plg2);











  struct MaxArea
  {
    double area = 0;
    void operator()(const Polygon& plg);
  };

  struct MaxVertexes
  {
    size_t vertexes = 0;
    void operator()(const Polygon& plg);
  };

  struct MinArea
  {
    double area;
    void operator()(const Polygon& plg);
  };

  struct MinVertexes
  {
    size_t vertexes;
    void operator()(const Polygon& plg);
  };

  struct Counter
  {
    size_t num;
    std::function< bool(const Polygon& plg) > func;
    void operator()(const Polygon& plg);
  };

  struct MaxSeq
  {
    Polygon MaxSeqplg;
    size_t counter = 0, maxCounter = 0;
    void operator()(const Polygon& plg);
  };

  struct Segment
  {
    Point p1, p2;
  };

  struct MakeSegment
  {
    Point prevPoint;
    Segment operator()(const Point& currPoint);
  };

  int vectorCrossProduct(const std::vector< int >& vec1, const std::vector< int >& vec2);
  bool isSegmentsIntersected(const Segment& ab, const Segment& cd);
  bool isPolygonsIntersected(const Polygon& plg1, const Polygon& plg2);

  struct IsIntersected
  {
    Polygon plg1;
    size_t intersectionsCount = 0;
    void operator()(const Polygon& plg2);
  };
}

#endif

