#ifndef COMMAND_PREDICATES_HPP
#define COMMAND_PREDICATES_HPP

#include <ostream>
#include "Polygon.hpp"

namespace sazanov
{
  double accumulateAreaWithParity(double area, const Polygon& polygon, bool isOdd);
  double accumulateAreaWithNumOfVertexes(double area, const Polygon& polygon, size_t numOfVertexes);
  double accumulateMeanArea(double area, const Polygon& polygon, size_t numOfPolygons);
  bool compareArea(const Polygon& lhs, const Polygon& rhs);
  bool compareVertex(const Polygon& lhs, const Polygon& rhs);
  void outputArea(const Polygon& polygon, std::ostream& out);
  void outputVertex(const Polygon& polygon, std::ostream& out);
  bool countWithParity(const Polygon& polygon, bool isOdd);
  bool countWithNumOfVertexes(const Polygon& polygon, size_t numOfVertexes);
  bool isSamePolygons(const Polygon& lhs, const Polygon& rhs);
  bool isEqualPointDiff(const Point& lhs, const Point& rhs, int xDiff, int yDiff);

  struct accumulatePolygonSequence
  {
    size_t curSeq = 0;
    size_t operator()(size_t maxSeq, const Polygon& polygon, const Polygon& commandPolygon);
  };
}

#endif
