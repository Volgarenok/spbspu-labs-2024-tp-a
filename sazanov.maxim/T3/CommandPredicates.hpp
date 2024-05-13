#ifndef COMMAND_PREDICATES_HPP
#define COMMAND_PREDICATES_HPP

#include <ostream>
#include "Polygon.hpp"

namespace sazanov
{
  double accumulateAreaWithParity(double area, const Polygon& polygon, bool isOdd);
  double accumulateAreaWithNumOfVertexes(double area, const Polygon& polygon, std::size_t numOfVertexes);
  double accumulateMeanArea(double area, const Polygon& polygon, std::size_t numOfPolygons);
  bool compareArea(const Polygon& lhs, const Polygon& rhs);
  bool compareVertex(const Polygon& lhs, const Polygon& rhs);
  void outputArea(const Polygon& polygon, std::ostream& out);
  void outputVertex(const Polygon& polygon, std::ostream& out);
  bool countWithParity(const Polygon& polygon, bool isOdd);
  bool countWithNumOfVertexes(const Polygon& polygon, std::size_t numOfVertexes);
  bool IsSamePolygons(const Polygon& lhs, const Polygon& rhs);
  bool IsEqualPointDiff(const Point& lhs, const Point& rhs, int xDiff, int yDiff);
  bool PointComparator(const Point& lhs, const Point& rhs);

  struct accumulatePolygonSequence
  {
    std::size_t curSeq = 0;
    std::size_t operator()(std::size_t maxSeq, const Polygon& polygon, const Polygon& commandPolygon);
  };
}

#endif
